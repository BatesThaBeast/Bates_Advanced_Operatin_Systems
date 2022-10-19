#include "filesys.h"
#include <sstream>
Filesys::Filesys(string diskname, int number_of_blocks, int block_size)
{

}

int Filesys::fsclose()
{

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

}
int Filesys::addblock(string file, string block)
{

}
int Filesys::delblock(string file, int blocknumber)
{

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

}
int Filesys::buildfs()
{

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