#ifndef TOPIC_H
#define TOPIC_H
#include <iostream>
#include "Message.h"

using namespace std;
class Topic : public Message
{
	public:
		Topic();
		Topic(const string &athr,
			  const string &sbjct,
			  const string &body,
			  unsigned id);
		virtual bool is_reply() const; // return false
		virtual string to_formatted_string() const;
};
#endif

