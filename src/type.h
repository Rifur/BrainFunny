#ifndef __TYPE_H__
#define __TYPE_H__ 1

enum TypeEnum
{ 
	RAW,
	LIST_INT,
	LIST_CHAR
};

union Value {
		int 	rawVal;
		int *	listInt;
		const	char*	listChar;
};

struct Variable
{
	enum TypeEnum type;
	union Value value;
};

#endif