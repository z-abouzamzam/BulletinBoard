#include <iostream>
#include <sstream>
#include "Reply.h"
#include "Message.h"

using namespace std;

Reply::Reply()
: Message()
{ }

Reply::Reply(const string &athr, const string &sbjct, const string &body,
unsigned id)
: Message(athr, sbjct, body, id) // need to add re when declaring replies
{ }

bool Reply::is_reply() const
{
	return true;
}

string Reply::to_formatted_string() const
{
	// added space before subject and body
	// id is the child's id, used for outputting correct message and reply
	// cout << "REPLY" << endl;
	ostringstream oss;
	oss << "<begin_reply>" << endl;
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
	oss << ":body: " << body << flush; // changed endl to flush- good now
	oss << "<end>" << endl;
	return oss.str();
}

