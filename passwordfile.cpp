

#include "passwordfile.h"
int PasswordFile::salt = 1;
PasswordFile::PasswordFile(string file_name)
{
	setfilename(file_name);//setting filename to whatever the user has inputted
	ifstream infile;//creating the variable that will parse the file
	if (infile.good())//check to see if the file is able to be read
	{
		infile.open(file_name);//opens the file
		if (infile.is_open())//perform a check to see if a file has been opened.
		{
			string u, p;//will hold the user and password in a string
			infile >> u >> p;//read a line
			while (infile.good())
			{
				user.push_back(u);//loading the vector
				password.push_back(p);//loading the vector
				infile >> u >> p;//read the next line
			}
		}
		else//if no file exists, then it is created
		{
			ofstream outfile;//variable that will create the file
			outfile.open(file_name);//create the file and named based on user input
		}
	}	
}
void PasswordFile::addpw(string newuser, string newpassword)
{
	if (!PasswordFile::checkusr(newuser))//check to see if the user is already in the database
	{
		user.push_back(newuser);//add user to end of user vector
		password.push_back(PasswordFile::encrypt(newpassword));//add corresonding password to end of password vector
		sync();//write updated vectors to file
	}
}

bool PasswordFile::checkpw(string usr, string passwd)
{
	for (int i = 0; i < user.size(); i++)//cycle through user vector to see if the user exists
	{
		if (usr == user[i] && PasswordFile::encrypt(passwd) == password[i])//if there is a match
		{
			return true;//found user
		}
	}
	return false;//did not find user
}

bool PasswordFile::checkusr(string usr)
{
	for (int i = 0; i < user.size(); i++)//cycle through user vector to see if the user exists
	{
		if (usr == user[i])
		{
			return true;//found user
		}
	}
	return false;//did not find user
}
bool PasswordFile::delusr(string usr)
{
	int lastindex = user.size() - 1;//locating the last element in the vector
	if (user.size() == 0)
	{
		return false;//did not delete user because there is no users on file
	}
	else
	{
		for (int i = 0; i < user.size(); i++)
		{
			if (user[i] == usr)//if user is found in vector
			{
				user[i] = user[lastindex];// overwrite the element intended to be erased with the last element.
				password[i] = password[lastindex];// overwrite the element intended to be erased with the last element.
				user.pop_back();//deleting last element in vector since there is two copies
				password.pop_back();//deleting last element in vector since there is two copies

				sync();//write updated vectors to file
				return true;//show that we did delete user
			}
		}
		return false;//did not delete the user cause they were not found
	}
}
void PasswordFile::newsalt(int ns)//this is used to encrypt
{
	salt = ns;
}

string PasswordFile::encrypt(string s)//performs the encryption by adding the salt to the letters of the string(ASCII)
{
	for (int i = 0; i < s.size(); i++)
	{
		if ((s[i] + salt) <= 255)//if the input is still with the range of ASCII 
		{
			s[i] += salt;
		}
		else if ((s[i] + salt) > 255)//if the input exceeds the range of ASCII
		{
			s[i] += (salt % 255);
		}
	}
	return s;
}
void PasswordFile::sync()
{
	ofstream outfile;
	outfile.open(filename);
	for (int i = 0; i < user.size(); i++)
	{
		outfile << user[i] << " " << password[i] << endl;
	}
}
void PasswordFile::setfilename(string file_name)
{
	filename = file_name;
}

void PasswordFile::printusr()
{
	for (int i = 0; i < user.size(); i++)
	{
		std::cout << user[i] << " " << password[i] << endl;
	}
	std::cout << "printing complete." << endl;
}