#include <iostream>
#include <sstream>
using namespace std;
#include "Message.h"
#include <vector>

Message::Message()
: author(""), subject(""), body(""), id(0), child_list(vector<Message*>(0))
{ }

Message::Message(const string& athr, const string& sbjct, const string& body,
unsigned id)
: author(athr), subject(sbjct), body(body), id(id), child_list(vector<Message*>(0))
{ }

Message::~Message()
{
	
}

void Message::print(unsigned indentation) const
{
	// indentation = indentation;
	string indent = "";
	indent.assign(indentation * 2, ' ');
	cout << endl;
	cout << indent << "Message #" << id << ":" << subject << endl;
	cout << indent << "from " << author << flush;
	cout << ":" << add_indents_to_body(body, indent);
	if(child_list.size() == 0)
	 	return;
	for(unsigned i = 0; i < child_list.size(); i++)
	{
		child_list.at(i)->print(indentation + 1);
	}
}
string Message::add_indents_to_body(const string& body, const string& indent) const
{
	string data = "", in = "";
	istringstream iss(body);
	getline(iss, in);
	data = in;
	data += "\n";
	while(getline(iss, in))
	{	
		data += indent + in;
		data += "\n";
	}
	return data;
}

const string & Message::get_subject() const
{
	return subject;
}

unsigned Message::get_id() const
{
	return id;
}

void Message::add_child(Message* child)
{
	child_list.push_back(child);
}
