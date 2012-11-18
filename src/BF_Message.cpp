#include "BF_Message.h"

msg_struct*	BF_Message::WriteLetter(int src, int dst, enum msg_type type, union msg_body body)
{
	struct msg_struct *msg = new struct msg_struct;
	msg->src = src;
	msg->dst = dst;
	msg->type = type;
	msg->msg = body;
	return msg;
}
