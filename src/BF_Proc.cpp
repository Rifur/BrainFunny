#include "BF_Proc.h"

BF_Proc::BF_Proc(int id)
{
	pid = id;
	dataSeg = new int [SegSize];
	codeSeg = new char [SegSize];

	pc = &dataSeg[CodeAddr];
	dp = &dataSeg[DataAddr];
	codeSegLen = 0;
	brk_dp = BrkInit;

	for(int i=0; i<127; ++i) {
		brk[i] = 1;
	}

	for(int i=0; i<SegSize; ++i) {
		dataSeg[i] = 0;
		codeSeg[i] = 0;
	}
}

char BF_Proc::Fetch()
{
	return codeSeg[*pc];
}

BF_Proc::~BF_Proc()
{
	delete [] dataSeg;
	delete [] codeSeg;
}
