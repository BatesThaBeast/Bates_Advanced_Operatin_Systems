#include "sdisk.h"

Sdisk::Sdisk(string diskname, int numberofblocks, int blocksize)
{	
	ifstream infile;
	if (infile.good())
	{
		infile.open(diskname);//try to open up the file that contains the disk
		if (infile.is_open())//if the disk exist
		{
			thediskname = diskname;//set thediskname to diskname
			string b;//b is the block being read
			infile >> b;//read the first block
			thenumberofblocks++;//count the number of blocks that have been added
			theblocksize = b.size();//counts the size of the first block			
			while (infile.good())//while still reading from file
			{
				theblocks.push_back(b);//add block to the block vector
				thenumberofblocks++;//count the number of blocks that have been added
			}
		}
		else//if the disk does not exist
		{
			ofstream outfile;//create a variable to create a file
			outfile.open(diskname); //create a file named whatever was input as diskname
			thediskname = diskname;//set variable
			thenumberofblocks = numberofblocks;//set variable
			theblocksize = blocksize;//set variable
		}
	}
}

vector<string> Sdisk::block(string buffer, int b)
{
	vector<string> blocks;//make a container for the blocks
	int numberofblocks = 0;//initialize variable

	if (buffer.length() % b == 0)
	{
		numberofblocks = buffer.length() / b;
	}
	else
	{
		numberofblocks = buffer.length() / b + 1;
	}

	string tempblock;//used to increment through the blocks 
	for (int i = 0; i < numberofblocks; i++)
	{
		tempblock = buffer.substr(b * i, b);
		blocks.push_back(tempblock);
	}

	int lastblock = blocks.size() - 1;

	for (int i = blocks[lastblock].length(); i < b; i++)
	{
		blocks[lastblock] += "#";
	}

	return blocks;
}

int sdisk::getblock(int blocknumber, string buffer)
{
	fstream iofile;
	iofile.open(diskname.c.str(), ios::in);
	if(blocknumber < 0 || blocknumber >= numberofblocks)
	{
		cout << "block doesn't exist."
		return 0;
	}
}