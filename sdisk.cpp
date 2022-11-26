#include "sdisk.h"

Sdisk::Sdisk(string diskname, int numberofblocks, int blocksize)
{
	this->diskname = diskname;//initialize diskname
	this->numberofblocks = numberofblocks;//initialize numberofblocks
	this->blocksize = blocksize;//initialize blocksize
	ifstream indisk;//create variable to parse file
	indisk.open(diskname.c_str());
	if (indisk.fail())//if there is no file to open
	{
		indisk.close();
		ofstream outdisk;//variable that will create file
		outdisk.open(diskname.c_str());//create file
		
		for (size_t i = 0; i < numberofblocks; i++)//loop through up to the number of blocks
		{
			for (size_t j = 0; j < blocksize; j++)//loop through up to the block size
			{
				outdisk.put('#');//use # as a place holder for empty
			}
		}
	}	
	else
	{
		int count = 0;
		char c;
		indisk.get(c);
		while (indisk.good())
		{
			count++;
			indisk.get(c);
		}
		if (count = blocksize * numberofblocks)
		{
			cout << "Correct disk size." << endl;
			return;
		}
		else
		{
			cout << "Warning. Incorrect disk size." << endl;
			return;
		}
	}
}
int Sdisk::putblock(int blocknumber, string buffer)
{
	fstream iofile;
	iofile.open(this->diskname.c_str(), ios::in | ios::out);
	if (iofile.is_open())
	{
		if (blocknumber < 0 || blocknumber >= this->numberofblocks)
		{
			cout << "block doesn't exist.";
			return 0;
		}
		else
		{
			iofile.seekp(blocksize * blocknumber);
			for (int i = 0; i < buffer.size(); i++)
			{
				iofile.put(buffer[i]);
			}
			iofile.close();
		}
	}	
}
int Sdisk::getblock(int blocknumber, string& buffer)
{
	fstream iofile;
	iofile.open(this->diskname.c_str(), ios::in | ios::out);
	if (iofile.is_open())
	{
		if (blocknumber < 0 || blocknumber >= this->numberofblocks)
		{
			cout << "block doesn't exist.";
			return 0;
		}
		else
		{
			iofile.seekg(blocksize * blocknumber);
			buffer.clear();
			char c;
			for (int i = 0; i < blocksize; i++)
			{
				iofile.get(c);
				buffer.push_back(c);
			}
			iofile.close();
		}
	}
}
int Sdisk::numofblocks()
{
	return numberofblocks;
}
int Sdisk::getblocksize()
{
	return blocksize;
}
int Sdisk::getstatus()
{
	return 0;
}
