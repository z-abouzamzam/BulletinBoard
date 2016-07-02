#include <iostream>
using namespace std;
#include "User.h"

User::User()
: username(""), password("")
{ }
 
User::User(const string& uname, const string& pass)
: username(uname), password(pass)
{ }
 
string User::get_username() const
{
    return username;
}

bool User::check(const string &uname, const string &pass) const
{
    return (username == uname && password == pass && uname != "" && pass != "");
}

void User::set_password(const string& newpass)
{
    password = newpass;
}
