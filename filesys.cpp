#include "filesys.h"
#include <sstream>
#include <iomanip>
Filesys::Filesys(string diskname, int number_of_blocks, int block_size) : Sdisk(diskname, number_of_blocks, block_size)
{
	this->rootsize = this->getblocksize() / 12;
	int bytereq = this->numofblocks() * 6;
	this->fatsize = (bytereq / this->getblocksize()) + (bytereq % this->getblocksize() > 0);

	this->initroot();
	this->initfat();

	this->fssynch();
}

int Filesys::fsclose()
{
	return 1;
}
int Filesys::newfile(string file)
{
	if (this->getfirstblock(file) != -1)
	{
		return 0;
	}
	for (int i = 0; i < this->filename.size(); i++)
	{
		if (this->filename[i] == ".....")
		{
			this->filename[i] = file;
			this->firstblock[i] = 0;
			return this->fssynch();
		}
	}
	return 0;
}
int Filesys::rmfile(string file)
{
	// Parse through the filename vector to find the correct file.
	for (int i = 0; i < filename.size(); i++)
	{
		if (filename[i] == file)// if the file is found
		{
			if (firstblock[i] == 0)// 0 would indicate the end of a file in this case an empty file.
			{
				filename[i] = "XXXXXX";// simulating the removal of the file
				fssynch();// writing updates of the vectors to the system
				return 1;// return 1 for success of removal
			}			
		}
	}
	return 0;// if the file name was found, but it isn't an empty file
}
int Filesys::getfirstblock(string file)
{
	// Parse through the filename vector to find the correct file.	
	for (int i = 0; i < this->filename.size(); i++)
	{
		if (this->filename[i] == file)// If the file is found, return the same index of the vector firstblock.
			return this->firstblock[i];
	}
	// If there is no file to be found, then we return the error code of 0
	// which will be used to signify a failure.
	return -1;
}
int Filesys::addblock(string file, string block)
{
	// There Is No Free Blocks
	if (this->fat[0] == 0)
		return -1;
	// This is where the block will be added according to the FAT
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
	if (fbcheck(file, blocknumber))// check to see if file and block exist
	{

		if (this->fat[blocknumber] == 0)// check to see if block is end of file
		{
			return 0;
		}
		else return this->fat[blocknumber];// return what block the blocknumber is pointing to, aka the next block
	}
	else return -1;// either file not found or blocknumber not found
}
int Filesys::buildfs()
{
	//TODO - Write buildfs()
	return 0;
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
int Filesys::initroot()
{
	stringstream ssBuffer;
	// Setup Root With Default Values
	for (int i = 0; i < this->rootsize; i++)
	{
		ssBuffer << "....." << this->delimiter << "00000" << this->delimiter;
	}
	
	/*
	else { // FileSystem Previously Existed
		string temp;
		this->getblock(0, temp);
		ssBuffer << temp;
	}
	*/
	vector<string>vecRoot = block(ssBuffer.str(), this->getblocksize());
	ssBuffer.str(vecRoot[0]);

	{ // Local Scope
		int i;
		string entry;
		for (i = 0; i < (this->rootsize * 2) && getline(ssBuffer, entry,
			this->delimiter); i++)
		{
			if (i % 2 == 0)
				this->filename.push_back(entry);
			else
				this->firstblock.push_back(std::stoi(entry, nullptr, 10));
		}
	}

	return 1;
}
int Filesys::initfat()
{
	stringstream ssBuffer;
	int dataStart = 1 + this->fatsize;

		// Setup Fat With Default Variables
		ssBuffer << setw(5) << setfill('0') << dataStart << this->delimiter;
		for (int i = 1; i < dataStart; i++)
			ssBuffer << "00000" << this->delimiter;
		for (int i = dataStart; i < (this->numofblocks() - 1); i++)
			ssBuffer << setw(5) << setfill('0') << (i + 1) << this->delimiter;
		ssBuffer << "00000" << this->delimiter;
	
	/*
	else 
	{  // filesystem already exist
		string temp;
		for (int i = 1; i < dataStart; i++) {
			this->getblock(i, temp);
			ssBuffer << temp;
		}
	}
	*/
	vector<string> vecFAT = block(ssBuffer.str(), this->getblocksize());
	ssBuffer.str("");
	for (int i = 0; i < vecFAT.size(); i++)
		ssBuffer << vecFAT[i];

	{ // Local Scope
		int i;
		string entry;
		for (i = 0; i < this->numofblocks() && getline(ssBuffer, entry,
			this->delimiter); i++)
		{
			this->fat.push_back(std::stoi(entry, nullptr, 10));
		}
	}

	return 1;
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
vector<string> Filesys::ls()
{
	vector<string> flist;
	for (int i = 0; i < filename.size(); i++)
	{
		if (filename[i] != "XXXXX") 
		{
			flist.push_back(filename[i]);
		}
	}
	return flist;
}