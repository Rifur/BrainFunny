#include <cstdio>
#include <cstdlib>

#include "BF_Proc.h"
#include "BF_VM.h"


int main(int argc, char *argv[])
{
	BF_VM *bfVM = new BF_VM();

	for(int i=1; i<argc; ++i) {
		bfVM->Load(argv[i]);
	}

	bfVM->Run();

	return 0;
}
