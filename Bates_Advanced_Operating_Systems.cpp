// Bates_Advanced_Operatin_Systems.cpp : Defines the entry point for the application.
//

#include "Bates_Advanced_Operating_Systems.h"
#include "passwordfile.h"
#include "sdisk.h"
#include "filesys.h"
#include "block.h"

using namespace std;

int main()
{
	/*//Testing PassWordFile********************************************
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
	passfile.printusr();//checking the vectors*/


	Sdisk disk1("test1", 16, 32);
	string block1, block2, block3, block4;
	for (int i = 1; i <= 32; i++) block1 = block1 + "1";
	for (int i = 1; i <= 32; i++) block2 = block2 + "2";
	disk1.putblock(4, block1);
	disk1.getblock(4, block3);
	cout << "Should be 32 1s : ";
	cout << block3 << endl;
	disk1.putblock(8, block2);
	disk1.getblock(8, block4);
	cout << "Should be 32 2s : ";
	cout << block4 << endl;;
	

	Sdisk disk3("disk1", 256, 128);
		Filesys fsys("disk1", 256, 128);
		fsys.newfile("file1");
		fsys.newfile("file2");
	

	string bfile1;
	string bfile2;

	for (int i = 1; i <= 1024; i++)
	{
		bfile1 += "1";
	}
	vector<string> blocks = fsys.block(bfile1, 128);

	int blocknumber = 0;

		for (int i = 0; i < blocks.size(); i++)
		{
			blocknumber = fsys.addblock("file1", blocks[i]);
		}

	fsys.delblock("file1", fsys.getfirstblock("file1"));

	for (int i = 1; i <= 2048; i++)
	{
		bfile2 += "2";
	}

	blocks = fsys.block(bfile2, 128);

	for (int i = 0; i < blocks.size(); i++)
	{
		blocknumber = fsys.addblock("file2", blocks[i]);
	}

	fsys.delblock("file2", blocknumber);
	return 0;
}

