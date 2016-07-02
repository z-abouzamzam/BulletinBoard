#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
using namespace std;
#include "BBoard.h"
#include "User.h"
#include "Message.h"
#include "Reply.h"
#include "Topic.h"

/*int main(int argc, char* argv[])
{
    string file = argv[argc - 1];
 	//   Message m;
	// m.display();
	// cout << endl;
	// Message m1("Zafir", "Great Subject", "THis is the body!!");
	// m1.display();
	
	BBoard board;
	board.setup(file);
	board.login();
    return 0;   
}*/

int main(int argc, char **argv)
{
    // check commandline arguments 
    if (argc != 3){
        cout << "ERROR: Invalid program call." << endl
            << "Usage: <program_name> userfile datafile" << endl;
        return 1;
    }
    string userfile(argv[1]);
    string datafile(argv[2]);
   
    BBoard bb("Bulletin Board");
   
    // load users from file
    if (!bb.load_users(userfile))
    {
        cout << "ERROR: Cannot load users from " << userfile << endl;
        return 1;
    }
   
    // load messages   
    if (!bb.load_messages(datafile))
    {
        cout << "ERROR: Cannot load messages from " << datafile << endl;
        return 1;
    }
   	
    bb.login();
    //bool a = bb.save_messages("out.txt");
    //a=a;
    bb.run();

    // save messages
    if (!bb.save_messages(datafile))
    {
        cout << "ERROR: Cannot save messages to " << datafile << endl;
        return 1;
    }
	// cout << "saved" << endl;
    return 0;
} 
