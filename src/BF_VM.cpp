#include "BF_VM.h"
#include "windows.h"

BF_VM::BF_VM()
{
	tick = TickMax;
}

void	BF_VM::Init(BF_Proc & p)
{
	p.pid = proc.size();
	proc.push(&p);
}

void	BF_VM::Load(string str)
{
	ifstream fsrc;
	string	buf;

	fsrc.open(str.c_str(), ios::in);

	BF_Proc *pr = new BF_Proc(proc.size());
	proc.push(pr);
	BF_Proc &p = *pr;

	while(!fsrc.eof()) {
		getline(fsrc, buf);
		if(buf.c_str()[0] == '%') {
			*p.pc = p.codeSegLen = atoi(&buf.c_str()[1]);
			continue;
		}

		const char *s = buf.c_str();
		for(int i=0; i<(int)buf.length(); ++i) {
			p.codeSeg[p.codeSegLen] = s[i];

			switch(s[i]) {
			case '\t':
			case '\n':
				continue;
			}

			++p.codeSegLen;
		}
	}
}

int	BF_VM::Run()
{
	BF_Proc *p = proc.front();
	char ins;

	while(1) {
		ins = p->Fetch();

		printf("[%d] = %d \t@[%d] %c  \tloop [%d]=%d pid %d %d tick %d\n", *p->dp, p->dataSeg[*p->dp], *p->pc, p->codeSeg[*p->pc]=='\n'? ' ':p->codeSeg[*p->pc], p->brk_dp, p->brk[p->brk_dp], proc.front()->pid, proc.back()->pid, tick);
		Sleep(50);
		switch(ins)
		{
		case '>':
			Right(*p);
			break;

		case '<':
			Left(*p);
			break;

		case '+':
			Inc(*p);
			break;

		case '-':
			Dec(*p);
			break;

		case '.':
			Put(*p);
			break;

		case ',':
			Get(*p);
			break;

		case '[':
			BeginLoop(*p);
			break;

		case ']':
			EndLoop(*p);
			break;

		// new syntax
		/*
		*	a)	$2    moves the data pointer to position two.
		*	b)	If $2=5, $5=3, then $$2 is 3.
		*/
		case '$':	
			Ref(*p);
			break;

		case '=':
			Assign(*p);
			break;

		case '#':
			Jump(*p);
			break;

		case 'S':
			SystemCall(p);
			break;

		/*
		*	Halt the process.
		*/
		case '!':
		case '\0':
			Terminate();
			p = ContextSwitch();
			break;

		}

		++*p->pc;
		--tick;

		if(!tick) {
			p = ContextSwitch();
		}
	}

	return 0;
}

BF_Proc* BF_VM::ContextSwitch()
{
	tick = TickMax;

	if(proc.size() == 0) {
			printf("(Halt)\n");
			exit(0);
	}

	if(proc.size() > 1) {
		proc.push(proc.front());
		proc.pop();
	}

	return proc.front();
}

void	BF_VM::Terminate()
{
	proc.pop();
}

void	BF_VM::Left(BF_Proc & p)
{
	--*p.dp;
}

void	BF_VM::Right(BF_Proc & p)
{
	++*p.dp;
}

void	BF_VM::Inc(BF_Proc & p)
{
	int i = atoi(&p.codeSeg[*p.pc+1]);
	p.dataSeg[*p.dp] += (i || p.codeSeg[*p.pc+1]=='0' ? i : 1);
	p.dataSeg[*p.dp] %= 256;
}

void	BF_VM::Dec(BF_Proc & p)
{
	int i = atoi(&p.codeSeg[*p.pc+1]);
	p.dataSeg[*p.dp] -= (i || p.codeSeg[*p.pc+1]=='0' ? i : 1);
	p.dataSeg[*p.dp] %= 256;
}

void	BF_VM::Put(BF_Proc & p)
{
	//printf("%d\n", p.dataSeg[*p.dp]);
	putchar(p.dataSeg[*p.dp]);
}

void	BF_VM::Get(BF_Proc & p)
{
	p.dataSeg[*p.dp] = getchar();
}

void	BF_VM::BeginLoop(BF_Proc & p)
{
	if(p.dataSeg[*p.dp] == 0) {
		while(p.brk[p.brk_dp]) {
			++*p.pc;
			if(p.codeSeg[*p.pc] == '[') {
				++p.brk[p.brk_dp];
			}
			else if(p.codeSeg[*p.pc] == ']') {
				--p.brk[p.brk_dp];
			}
		}
		p.brk[p.brk_dp] = 1;
	}
	else {
		++p.brk_dp;
	}
}

void	BF_VM::EndLoop(BF_Proc & p)
{
	if(p.dataSeg[*p.dp]) {
		p.brk[p.brk_dp] = BrkInit;
		while(p.brk[p.brk_dp]) {
			--*p.pc;
			if(p.codeSeg[*p.pc] == '[') {
				--p.brk[p.brk_dp];
			}
			else if(p.codeSeg[*p.pc] == ']') {
				++p.brk[p.brk_dp];
			}
		}
		p.brk[p.brk_dp] = BrkInit;
	}
	else {
		--p.brk_dp;
	}
}

void	BF_VM::Ref(BF_Proc & p)
{
	int	m_num = 0;
	int	tmp = 0;
	while(p.codeSeg[*p.pc+m_num] == '$') {
		++m_num;
	}
	*p.pc += m_num - 1;
	tmp = atoi(&p.codeSeg[*p.pc + 1]);

	while(--m_num) {
		tmp = p.dataSeg[tmp];
	}

	*p.dp = tmp;
}

void	BF_VM::Jump(BF_Proc & p)
{
	*p.pc = atoi(&p.codeSeg[*p.pc+1]) - 1;
}

void	BF_VM::Assign(BF_Proc & p)
{
	char	*str = &p.codeSeg[*p.pc+1];
	int	tmp = atoi(str);

	if(tmp || str[0]=='0') {
		p.dataSeg[*p.dp] = tmp;
		return;
	}

	switch(str[0]) {
	case '"':
		{
			int i;
			string *s = new string;
			for(i=1; str[i]!='"'; ++i) {
				s->append(1, str[i]);
			}

			p.test.type = LIST_CHAR;
			p.test.value.listChar = s->c_str();
		}
		break;

	case '[':
		break;
	}
}

void	BF_VM::SystemCall(BF_Proc * p)
{
	char	*str = &p->codeSeg[*(p->pc) + 1];
	int	tmp = atoi(str);

	printf("SYSTEM CALL #%d by PID: %d\n", tmp, p->pid);

	switch(str[0]) {
	case '0':
		{
			printf("Print %d\n", p->dataSeg[*p->dp]);
		}
		break;
	case '1':
		{	
			int 	dst_pid = p->dataSeg[*p->dp];
			int 	value = p->dataSeg[(*p->dp) + 1];
			union	msg_body v;
			v.value = value;
			msg_pool.push( WriteLetter(p->pid, dst_pid, integer, v));

			printf("Send A Message to pid: %d, msg: %d\n", dst_pid, value);
		}
		break;

	case '2':
		{
			if(msg_pool.size() > 0 && (msg_pool.front()->dst == p->pid)) {
				msg_struct* s = msg_pool.front();

				p->dataSeg[*p->dp] = 0;
				p->dataSeg[(*p->dp) + 1] = s->msg.value;

				msg_pool.pop();

				printf("Get A Message from pid: %d, msg: %d\n", s->dst, s->msg.value);
			}
		}
		break;
	}

	puts("");
}
