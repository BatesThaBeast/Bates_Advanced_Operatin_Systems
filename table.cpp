#include "table.h"
Table::Table(string diskname, int numberofblocks, int blocksize, string flatfile, string indexfile) :Filesys(diskname, numberofblocks, blocksize)
{
    //ifstream infile;
    //infile.open(diskname.c_str);
    // Create flatfile in filesys
    newfile(flatfile);
    this->flatfile = flatfile;
    // Create indexfile in filesys
    newfile(indexfile);
    this->indexfile = indexfile;
    cout << "Table created" << endl;
}
int Table::Build_Table(string input_file)
{
    newfile(indexfile), newfile(flatfile);
    ifstream infile;
    infile.open(input_file.c_str());
    ostringstream outstream;
    string rec;
    getline(infile, rec);
    while (infile.good())
    {
        string date = rec.substr(0, 5);
        vector<string> blocks = block(rec, getblocksize());
        int b = addblock(flatfile, blocks[0]);
        outstream << date << " " << b << " ";
        getline(infile, rec);
    }
    outstream << "88888" << 0 << " ";
    string buffer = outstream.str();
    vector<string> blocks = block(buffer, getblocksize());
    for (int i = 0; i < blocks.size(); i++)
    {
        addblock(indexfile, blocks[i]);
    }
    return 1;
}
int Table::Search(string value)
{
    int block = IndexSearch(value);
    if (block == 0)
    {
        cout << "record not found.";
        return 0;
    }
    else
    {
        string buffer;
        int error = readblock(flatfile, block, buffer);
        cout << buffer;
        return 1;
    }
}

int Table::IndexSearch(string value)
{
    string buffer;
    int block = getfirstblock(indexfile);
    while (block != 0)
    {
        string b;
        int error = readblock(indexfile, block, b);
        buffer += b;
        block = nextblock(indexfile, block);
    }
    istringstream instream;
    string s;
    int b;
    instream.str(buffer);
    instream >> s >> b;
    while (s != "88888")
    {
        if (s == value) 
        {
            return b;
            instream >> s >> b;
        }
    }
    return 0;
}