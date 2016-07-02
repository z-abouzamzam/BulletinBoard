#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
using namespace std;
#include "BBoard.h"
#include "User.h"
#include "Message.h"
#include "Topic.h"
#include "Reply.h"
#include <vector>

BBoard::BBoard()
: title("Jack's Amazing Bulletin Board"), user_list(), current_user(0), 
message_list()
{ }

BBoard::BBoard(const string &ttl)
: title(ttl), user_list(), current_user(0), message_list()
{ }

BBoard::~BBoard()
{
	for(unsigned i = 0; i < message_list.size(); i++)
	{
		delete message_list.at(i);
	}
	current_user = 0;
}

/*void BBoard::setup(const string &input_file)
{
    ifstream fin;
    string data = "", uname, passwd;
    fin.open(input_file.c_str());
    while(true)
    {
        fin >> uname;
        if(uname == "end") break;
        fin >> passwd;
        if(passwd == "end") break;
        add_user(uname, passwd);
    }
}*/

bool BBoard::load_users(const string &user_file)
{
	ifstream fin;
    string data = "", uname, passwd;
    fin.open(user_file.c_str());
    if(!fin.is_open())
    {
    	return false;
    }
    while(true)
    {
        fin >> uname;
        if(uname == "end") break;
        fin >> passwd;
        if(passwd == "end") break;
        add_user(uname, passwd);
    }
    return true;
}

void BBoard::login()
{
    string uname, passwd;
    cout << "Welcome to " << title << endl;
    while(true)
    {
        cout << "Enter your username ('Q' or 'q' to quit): ";
        cin >> uname;
        if(uname == "Q" || uname == "q")
        {
            cout << "Bye!" << endl;
            return;
        }
        cout << "Enter your password: ";
        cin >> passwd;
        if(user_exists(uname, passwd))
        {
            cout << "Welcome back " << uname << "!" << endl << endl;
            current_user = get_user(uname);
            return;
        }
        else
        {
            cout << "Invalid Username or Password!" << endl << endl;
            continue; 
        }
    }
    
}
void BBoard::run()
{
	char choice;
	if(current_user == 0)
		return;
    while(true)
    {
    	cout << "Menu" << endl;
    	cout << " - Display Messages (\'D\' or \'d\')" << endl;
    	cout << " - Add New Topic (\'N\' or \'n\')" << endl;
    	cout << " - Add Reply to a Topic (\'R\' or \'r\')" << endl;
    	cout << " - Quit (\'Q\' or \'q\')" << endl;
    	cout << "Choose an action: ";
    	cin >> choice;
    	
    	if(choice == 'D' || choice == 'd')
    	{
    		cout << endl;
    		display();
    	}
    	else if(choice == 'N' || choice == 'n')
    	{
    		cout << endl;
    		add_topic();
    	}
    	else if(choice == 'R' || choice == 'r')
    	{
    		cout << endl;
    		add_reply();
    	}
    	else if(choice == 'Q' || choice == 'q')
    	{
    		cout << "Bye!" << endl;
    		// save_messages("out.txt");
    		return;
    	}
    	else
    	{
    		continue;
    	}
    	
    }
}

void BBoard::add_user(const string &name, const string &pass)
{
    user_list.push_back(User(name, pass));
}
// shouldn't be needed
bool BBoard::user_exists(const string &name, const string &pass) const
{
    for(unsigned i = 0; i < user_list.size(); i++)
    {
        if(user_list[i].check(name, pass))
            return true;
    }
    return false;
}

const User* BBoard::get_user(const string &name) const
{
    for(unsigned i = 0; i < user_list.size(); i++)
    {
        if(user_list.at(i).get_username() == name) //******* . to ->
            return &user_list.at(i);
    }
    return 0; // null
}

void BBoard::display() const // change first display topic
{
	if(message_list.size() == 0)
	{
	 	cout << "Nothing to Display." << endl << endl;
	 	return;
	}
	else
	{
	 	for(unsigned i = 0; i < message_list.size(); i++)
	 	{
	 		if(!message_list.at(i)->is_reply())
	 		{
	 			cout << "-------------------------------------------------------------------------------";
		 		message_list.at(i)->print(0); // same as (*message_list.at(i)).print();
	 		}
	 	}
	}
	cout << "-------------------------------------------------------------------------------" << endl;
	cout << endl;
    
}

bool BBoard::load_messages(const string& datafile)
{
	unsigned numMessages;
	unsigned id, children;
	string idstring, childrenstring;
	string data, messageType, junk, subject, author, body;
	ifstream fin;
	fin.open(datafile.c_str());
	if(!fin.is_open())
		return false;
	fin >> data; // number of messages
	istringstream iss(data);
	iss >> numMessages;
	// cout << numMessages << endl << endl << endl;
	vector<vector<unsigned> > childrenVec;
	for(unsigned i = 0; i < numMessages; i++)
	{
		vector<unsigned> idVec;
		string messageType;
		junk = "";
		fin >> messageType;
		// cout << messageType;
		fin >> junk;// id
		fin.ignore();
		// cout << junk << "junk" << endl;
		getline(fin, idstring);
		
		// cout << idstring << endl;
		
		fin >> junk; // subject
		getline(fin, subject);
		fin >> junk; // author
		fin >> author;
		// cout << author << endl;
		fin >> junk; // body or children
		if(junk == ":children:")
		{
			getline(fin, childrenstring);
			//add children to idVec
			istringstream chiliss(childrenstring);
			while(chiliss >> children)
			{
				idVec.push_back(children);
			}
			
			fin >> junk;
		}
		body = "";
		while(getline(fin, data))
		{
			if(data.find("<end>") != string::npos)
				break;
			body += data;
			body += "\n";
		}
		// cout << "body" << body << "body" << endl;
		childrenVec.push_back(idVec);
		istringstream is(idstring);
		is >> id;
		idstring = "";
		
		if(messageType == "<begin_topic>")
		{
			Topic *t = new Topic(author, subject, body, id);
			message_list.push_back(t);
		}
		else
		{
			Reply *r = new Reply(author, subject, body, id);
			message_list.push_back(r);
		}
	}
	
	fin.close();
	
	// then add children
	for(unsigned i = 0; i < childrenVec.size(); i++)
	{
		for(unsigned j = 0; j < childrenVec.at(i).size(); j++)
		{
			if(childrenVec.at(i).at(j) > 0)
			{
				// cout << childrenVec.at(i).at(j) << " " << i << j << " ";
				message_list.at(i)->add_child(message_list.at(childrenVec.at(i).at(j)-1));
				// cout << "message list 5 sub" << message_list.at(5)->to_formatted_string() << endl;
			}
		}
	
	}
	return true;
}
bool BBoard::save_messages(const string &datafile)
{
	ofstream fout;
	// cout << "saving messages" << endl;
	fout.open(datafile.c_str());
	if(!fout.is_open())
		return false;
	fout << message_list.size() << endl;
	message_list.at(0);
	// cout << "a" << endl;
	for(unsigned i = 0; i < message_list.size(); i++)
	{
		fout << message_list.at(i)->to_formatted_string();
		// cout << message_list.at(i)->to_formatted_string();
		// cout << i << endl;
		// cout << "aa" << endl;
		// cout << "loop" << endl;
	}
	fout.close();
	// cout << "closed" << endl;
	return true;
}

void BBoard::add_topic()
{
	string author = current_user->get_username(), subject = "", body = " "; // . to ->
	string data = "";
    cout << "Enter Subject: ";
    cin.ignore();
    getline(cin, subject);
    subject = " " + subject;
    cout << "Enter Body: ";
    while(getline(cin, data)) // may need to change if empty
    {
    	if(data == "")
    		break;
    	body += data;
    	body += "\n";
    }
    message_list.push_back(new Topic(author, subject, body, message_list.size() + 1));
    cout << "Message Recorded!" << endl << endl;
    
}

void BBoard::add_reply()
{
	int messId;
	string author = current_user->get_username(), body = " ";
	string data = "", subject = " Re:";
	while(true)
	{
		cout << "Enter Message ID (-1 for Menu): ";
		cin >> messId;
		if(messId == -1)
		{
			cout << endl;
			return;
		}
		else if(messId > 0 && messId <= static_cast<int>(message_list.size()))
		{
			cout << "Enter Body: ";
			cin.ignore();
			while(getline(cin, data)) // may need to change if empty
		    {
		    	if(data == "")
		    		break;
		    	body += data;
		    	body += "\n";
		    }
		    subject += message_list.at(messId - 1)->get_subject();
		    Reply* r = new Reply(author, subject, body, message_list.size() + 1);
		    message_list.at(messId - 1)->add_child(r);
		    message_list.push_back(r);
		    cout << "\033[F"; // go up one line in terminal
		    return;
		}
		else
		{
			cout << "Invalid Message ID!!" << endl << endl;
			continue;
		}
	}
}

