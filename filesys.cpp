#include "filesys.h"
#include <sstream>
#include <iomanip>
Filesys::Filesys(string diskname, int number_of_blocks, int block_size) : Sdisk(diskname, number_of_blocks, block_size)
{
}

int Filesys::fsclose()
{
	return 1;
}
int Filesys::newfile(string file)
{
	for (int i = 0; i < filename.size(); i++)
	{
		if (filename[i] == file)
		{
			return -1;
		}
		if (filename[i] == "XXXXXX")
		{
			filename[i] = file;
			firstblock[i] = 0;
			fssynch();
			return 1;
		}
	}
	return 0;
}
int Filesys::rmfile(string file)
{
	for (int i = 0; i < filename.size(); i++)
	{
		if (filename[i] == file)
		{
			if (firstblock[i] == 0)
			{
				filename[i] = "XXXXXX";
				fssynch();
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
	return -1;
}
int Filesys::getfirstblock(string file)
{
	// Shorten filenames greater than 5 chars to 5
	if (file.length() > 5)
		file = file.substr(0, 5);

	for (int i = 0; i < this->filename.size(); i++)
		if (this->filename[i] == file)
			return this->firstblock[i];

	return -1;
}
int Filesys::addblock(string file, string block)
{
	// Shorten filenames greater than 5 chars to 5
	if (file.length() > 5)
		file = file.substr(0, 5);

	// There Is No Free Blocks
	if (this->fat[0] == 0)
		return 0;

	int alloc = this->fat[0];

	// Run Switch On First Block
	switch (this->getfirstblock(file))
	{
		// File Does Not Exit
	case -1:
		return 0;
		break;
		// File Is Currently Empty
	case 0:
		for (int i = 0; i < this->filename.size(); i++)
			if (this->filename[i] == file) 
			{
				this->firstblock[i] = alloc;
				this->fat[0] = this->fat[alloc];
				this->fat[alloc] = 0;

				// Write The Buffer To SDisk
				this->putblock(alloc, block);

				return this->fssynch();
			}
		break;
		// File Exists And Contains Blocks
	default:
		int curB = this->getfirstblock(file);
		while (this->fat[curB] != 0)
		{
			curB = this->fat[curB];
			this->fat[curB] = alloc;
			this->fat[0] = this->fat[alloc];
			this->fat[alloc] = 0;

			// Write The Buffer To SDisk
			this->putblock(alloc, block);

			break;
		}
	}

	return 1;
}
int Filesys::delblock(string file, int blocknumber)
{
	bool flag = fbcheck(file, blocknumber);// check to make sure the file and block number exist
	if (!flag) return 0;//if file or block number doesn't exist, return error
	int b = getfirstblock(file);
	if (b >= blocknumber)
	{
		for (int i = 0; i < filename.size(); i++)
		{
			if (filename[i] == file)
			{
				firstblock[i] = fat[firstblock[i]];
				break;
			}
		}
	}
	else
	{
		while (fat[b] != blocknumber)
		{
			b = fat[b];
		}
	}
	fat[blocknumber] = fat[0];
	fat[0] = blocknumber;
	return fssynch();
}
int Filesys::readblock(string file, int blocknumber, string& buffer)
{
	if (fbcheck(file, blocknumber))
	{
		getblock(blocknumber, buffer);
		return 1;
	}
	else return 0;
}
int Filesys::writeblock(string file, int blocknumber, string buffer)
{
	if (fbcheck(file, blocknumber))
	{
		putblock(blocknumber, buffer);
		return 1;
	}
	else return 0;
}
int Filesys::nextblock(string file, int blocknumber)
{
	//TODO - Write nextblock()
}
int Filesys::buildfs()
{
	//TODO - Write buildfs()
}
int Filesys::readfs()
{
	string bufferOne, bufferTwo;
	getblock(1, bufferOne);

	for (int i = 0; i < fatsize; i++)
	{
		string b;
		getblock(i + 2, b);
		bufferTwo += b;
	}
	istringstream instreamOne;
	istringstream instreamTwo;

	instreamOne.str(bufferOne);
	instreamTwo.str(bufferTwo);

	filename.clear();
	firstblock.clear();

	for (int i = 0; i < rootsize; i++)
	{
		string f;
		int b;
		instreamOne >> f >> b;
		filename.push_back(f);
		firstblock.push_back(b);
	}

	for (int i = 0; i < numofblocks(); i++)
	{
		int k;
		instreamTwo >> k;
		fat.push_back(k);
	}
	return 1;
}
int Filesys::fssynch()
{
	//TODO - Write fssynch()
	stringstream ssBuffer;

	//Write Root To SDisk
	for (int i = 0; i < this->rootsize; i++)
		ssBuffer << this->filename[i] << this->delimiter << setw(5) <<
		setfill('0') << this->firstblock[i] << this->delimiter;
	vector<string> vecRoot = block(ssBuffer.str(), this->getblocksize());
	this->putblock(0, vecRoot[0]);

	ssBuffer.str("");

	//Write fat To SDisk
	for (int i = 0; i < this->fat.size(); i++)
		ssBuffer << setw(5) << setfill('0') << fat[i] << this->delimiter;
	vector<string> vecFAT = block(ssBuffer.str(), this->getblocksize());
	for (int i = 0; i < vecFAT.size(); i++)
		this->putblock((1 + i), vecFAT[i]);

	return 1;
}
bool Filesys::fbcheck(string file, int blocknumber)
{
	int b = getfirstblock(file);
	while (b != 0)
	{
		if (b == blocknumber)
		{
			return true;
		}
		else
		{
			b = fat[b];
		}
	}
	return false;
}


vector<string> Filesys::block(string buffer, int b)
{
	vector<string> blocks;//will hold the buffer in blocks
	int numberofblocks = 0;

	if (buffer.length() % b == 0)//if all blocks are completely full
	{
		numberofblocks = buffer.length() / b;
	}
	else//if the ending block isn't full
	{
		numberofblocks = buffer.length() / b + 1;
	}

	string tempblock;//will hold the block to load into blocks
	for (int i = 0; i < numberofblocks; i++)
	{
		tempblock = buffer.substr(b * i, b);//parsing through each block
		blocks.push_back(tempblock);//loading block into vector
	}

	int lastblock = blocks.size() - 1;//set equal to the last block

	for (int i = blocks[lastblock].length(); i < b; i++)//if the last block is smaller than the block size, then # will be added until it is a full block
	{
		blocks[lastblock] += "#";
	}

	return blocks;
}