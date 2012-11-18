#ifndef __BF_MESSAGE_H__
#define __BF_MESSAGE_H__ 1

#include <queue>
#include <string>

using namespace std;

enum msg_type {
	integer,
	text
};

union msg_body {
	int	value;
	string	*str;
};

struct msg_struct
{
	int	src;
	int	dst;
	enum msg_type type;
	union msg_body msg;
};

class BF_Message {
public:
	msg_struct*	WriteLetter(int, int, enum msg_type, union msg_body);
};


#endif