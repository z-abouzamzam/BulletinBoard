#ifndef BBOARD_H
#define BBOARD_H
#include <vector>
#include <iostream>
using namespace std;
#include <fstream>
#include "User.h"
#include "Message.h"
#include <vector>

class BBoard
{
    private:
        string title;
        vector<User> user_list;
        const User* current_user;
        vector<Message*> message_list;
    public:
        BBoard();
        BBoard(const string &ttl);
        ~BBoard(); // deallocates messagelist one message at a time
        // void setup(const string &input_file); replaced with load_users
        bool load_users(const string &userfile);
        bool load_messages(const string &datafile); // new
        bool save_messages(const string &datafile); // new
        void login(); // big changes
        void run();
    private:
        void add_user( const string &name, const string &pass); // removed infile
        bool user_exists(const string &name, const string &pass) const; // not needed
        const User* get_user(const string &name) const; // major change
        void display() const;
        // void add_message(); unneeded- replaced with addtopic
        void add_topic();
        void add_reply();
        
};
#endif

