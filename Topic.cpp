#include <iostream>
#include <sstream>
#include "Message.h"
#include "Topic.h"

using namespace std;

Topic::Topic()
: Message()
{ }

Topic::Topic(const string &athr, const string &sbjct, const string &body, 
unsigned id)
: Message(athr, sbjct, body, id)
{ }

bool Topic::is_reply() const
{
	return false;
}

string Topic::to_formatted_string() const
{
	// added space before subject and body
	// id is the child's id, used for outputting correct message and reply
	// cout << "TOPIC" << endl;
	ostringstream oss;
	oss << "<begin_topic>" << endl;
	oss << ":id: " << id << endl;
	oss << ":subject: " << subject << endl;
	oss << ":from: " << author << endl;
	for(unsigned i = 0; i < child_list.size(); i++) // first value is topic
	{
		if(i == 0)
			oss << ":children: ";
		oss << child_list.at(i)->get_id() << " ";
		if(i + 1 == child_list.size())
			oss << endl;
	}
	oss << ":body: " << body << flush;
	oss << "<end>" << endl;
	return oss.str();
	
}


