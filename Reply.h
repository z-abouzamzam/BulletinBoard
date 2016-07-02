#ifndef REPLY_H
#define REPLY_H
#include <iostream>
#include "Message.h"
using namespace std;

class Reply : public Message
{
	public:	
		Reply();
		Reply(const string &athr,
			  const string &sbjct,
			  const string &body,
			  unsigned id);
		virtual bool is_reply() const; // return true
		virtual string to_formatted_string() const;
};
#endif

