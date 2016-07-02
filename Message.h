//inclusion guards
#ifndef MESSAGE_H
#define MESSAGE_H
//includes
#include <iostream>
#include <vector>
using namespace std;
class Message
{
    protected:
        string author;
        string subject;
        string body;
    	unsigned id;
    	vector<Message*> child_list; // how message keeps track of replies
    public:
        //default constructor
        Message();
        
        //Constructor with parameters
        Message(const string &athr, 
              const string &sbjct, 
              const string &body,
              unsigned id);
    	virtual ~Message();
    	virtual bool is_reply() const = 0;
    	virtual string to_formatted_string() const = 0;
    	void print(unsigned indentation) const; // uses recursion, increase indentation at each "level"
    	const string & get_subject() const;
    	unsigned get_id() const;
    	void add_child(Message *child);
    
        //displays the message in the given format. See output specs.
        
    private:
    	string add_indents_to_body(const string& body, const string& indent) const;
};
    
    //end inc guards
#endif 

