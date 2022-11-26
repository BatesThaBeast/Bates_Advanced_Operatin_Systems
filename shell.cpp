#include "shell.h"
int Shell::dir()
{
	vector<string> flist = ls();
	for (int i = 0; i < flist.size(); i++)
	{
		cout << flist[i] << endl;
	}
    return 1;
}
// Main Constructor
Shell::Shell(string filename, int number_of_blocks, int block_size) : Filesys(filename, number_of_blocks, block_size){}
// Add File To FileSystem
int Shell::add(string file, string buffer)
{
    if (this->newfile(file))
    {
        cout << "Would You Like To Add Data (y/n): ";
        getline(cin, buffer);
        if (buffer == "y" || buffer == "Y")
            this->add(file, buffer);
    };
    return 1;
}
// Delete File From FileSystem
int Shell::del(string file)
{
    int curBlock = this->getfirstblock(file);

    // Return If File Does Not Exist
    if (curBlock == -1) 
    {
        cout << "Cannot Find File To Remove" << endl;
        return 0;
    }
    // Remove All Blocks From File
    while ((curBlock = this->getfirstblock(file)) > 0)
    {
        this->delblock(file, curBlock);
    }
    // Remove File From Root
    this->rmfile(file);

    return 1;
}
// Lists The Contents Of A File (Similiar To 'cat' On Linux)
int Shell::type(string file)
{
    string fileBuffer = "";
    string blockBuffer = "";

    for (int curBlock = getfirstblock(file); curBlock != 0; curBlock = this->nextblock(file, curBlock)) 
    {
        this->readblock(file, curBlock, blockBuffer);
        fileBuffer += blockBuffer;
    }
    fileBuffer = fileBuffer.substr(0, fileBuffer.find_first_of('#'));
    cout << fileBuffer << endl;
    return 1;
}

// Copies One File To Another File
int Shell::copy(string file1, string file2)
{
    if (this->getfirstblock(file1) == -1) 
    {
        cout << "Could Not Find Source File!" << endl;
        return -1;
    }
    else if (this->getfirstblock(file2) >= 0) 
    {
        cout << "Destination File Already Exists!" << endl;
        return -1;
    }
    if (this->newfile(file2) == 0) 
    {
        cout << "Could Not Create File" << endl;
        return -1;
    }
    string buffer = "";
    for (int curBlock = this->getfirstblock(file1); curBlock != 0; curBlock = this->nextblock(file1, curBlock)) 
    {
        this->readblock(file1, curBlock, buffer);
        this->addblock(file2, buffer);
    }
    return 1;
}

// Allows The Addition Of Data To A File
int Shell::append(string file)
{
    if (getfirstblock(file) == -1) {
        cout << "Could Not Find File" << endl;
        return 0;
    }
    int lastBlock;
    for (lastBlock = this->getfirstblock(file); lastBlock != 0 && this->nextblock(file, lastBlock) != 0; lastBlock = nextblock(file, lastBlock));

    string totalBuffer;
    if (lastBlock != 0) {
        this->readblock(file, lastBlock, totalBuffer);
        this->delblock(file, lastBlock);
        totalBuffer = totalBuffer.substr(0, totalBuffer.find_first_of('#'));
    }

    string buffer;
    cout << "Enter Data:" << endl;
    getline(cin, buffer);
    totalBuffer += buffer;

    vector<string> blocks = block(totalBuffer, this->getblocksize());

    for (int i = 0; i < blocks.size(); i++)
        this->addblock(file, blocks[i]);

    return 1;
}

// Splits A String Into A Vector (Splits On Spaces)
vector<string> splitString(string buffer)
{
    vector<string> split;

    size_t begin, end;
    begin = buffer.find_first_not_of(' ');
    end = buffer.find_first_of(' ', begin);

    while (begin != end) {
        split.push_back(buffer.substr(begin, end - begin));
        begin = buffer.find_first_not_of(' ', end);
        end = buffer.find_first_of(' ', begin);
    }

    return split;
}