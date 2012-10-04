#ifndef __BF_PROC_H__
#define __BF_PROC_H__ 1

#include <stdio.h>
#include "type.h"

#define	SegSize		4096
#define	CodeAddr	4000
#define	DataAddr	4001
#define StackAddr	4002
#define BrkInit		1

class BF_Proc
{
public:
	BF_Proc(int id);
	~BF_Proc();

	int	*dataSeg;
	char	*codeSeg;

	char	brk[127];

	int	*dp;
	int	*pc;
	int	brk_dp;

	int	codeSegLen;
	int	pid;

public:
	char	Fetch();

	struct Variable	test;

};

#endif
