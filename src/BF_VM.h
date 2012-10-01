#ifndef __BF_VM_H__
#define __BF_VM_H__ 1

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <queue>
#include "BF_Proc.h"

#define TickMax 	10

using namespace std;

class BF_VM
{
public:
	BF_VM();

	void	Init(string str);
	int	Run();

	void	Inc(BF_Proc &);
	void	Dec(BF_Proc &);
	void	Put(BF_Proc &);
	void	Get(BF_Proc &);
	void	BeginLoop(BF_Proc &);
	void	EndLoop(BF_Proc &);

	void	Ref(BF_Proc &);
	void	Halt();

private:
	BF_Proc* ContextSwitch();
	void	Terminate();

private:
	queue<BF_Proc *> proc;
	int	tick;

};

#endif