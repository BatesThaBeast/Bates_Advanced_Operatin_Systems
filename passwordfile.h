/*PasswordFile class. Will be used for handling the creation and deletion of users and their passwords. 
  1 constructor: PasswordFile(string file_name);
  6 mutators: void addpw(string newuser, string newpassword); bool delusr(string usr); void sync();
  void setfilename(string file_name); string encrypt(string s);
  3 accessors bool checkusr(string usr); void printusr(); bool checkpw(string usr, string passwd);*/


#ifndef PASSWORDFILE
#define PASSWORDFILE
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class PasswordFile
{
public:
    /// <summary>
    /// opens the file and reads the names/passwords into the vectors user and password. if there is no file to open, it will create the file
    /// </summary>
    /// <param name="filename"></param>
    PasswordFile(string file_name);
    /// <summary>
    /// this adds a new user/password to the vectors and writes the vectors to the file filename
    /// </summary>
    /// <param name="newuser"></param>
    /// <param name="newpassword"></param>
    void addpw(string newuser, string newpassword);    
    /// <summary>
    /// checks to see if a user already exists
    /// </summary>
    bool checkusr(string usr);
    /// <summary>
    /// will delete the user if they exists
    /// </summary>
    bool delusr(string usr);
    void printusr();
    static void newsalt(int ns);
private:
    static int salt;
    string filename; // the file that contains password information
    vector<string> user; // the list of usernames
    vector<string> password; // the list of passwords
    /// <summary>
    /// returns true if user exists and password matches
    /// </summary>
    /// <param name="usr"></param>
    /// <param name="passwd"></param>
    /// <returns></returns>
    bool checkpw(string usr, string passwd);
    /// <summary>
    /// writes the user/password vectors to the password file
    /// </summary>
    /// <param name="s"></param>
    /// <returns></returns>
    void sync();
    /// <summary>
    /// accessor that allows filename to be assigned
    /// </summary>
    /// <param name="file_name"></param>
    void setfilename(string file_name);
    /// <summary>
    /// alters the string so as to encrypt it. will be used to encrypt passwords
    /// </summary>
    string encrypt(string s);
};
#endif