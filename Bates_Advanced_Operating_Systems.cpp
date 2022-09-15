// Bates_Advanced_Operatin_Systems.cpp : Defines the entry point for the application.
//

#include "Bates_Advanced_Operating_Systems.h"
#include "passwordfile.h"
#include "sdisk.h"

using namespace std;

int main()
{
	PasswordFile passfile("password.txt");
	passfile.addpw("dbotting", "123qwe");//adding user
	passfile.printusr();//checking the vectors
	passfile.addpw("egomez", "qwerty");//adding user
	passfile.printusr();//checking the vectors
	passfile.addpw("tongyu", "liberty");//adding user
	passfile.printusr();//checking the vectors
	passfile.addpw("dbotting", "456ewq");//test to see if you can have 2 users with the same name
	passfile.printusr();//checking the vectors
	passfile.delusr("dbotting");
	passfile.printusr();//checking the vectors
	// write some lines to see if passwords match users
	return 0;
}
