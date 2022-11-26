#ifndef  TABLE
#define TABLE

#include "filesys.h"
class Table : public Filesys
{
public:
	Table(string diskname, int numofblocks, int blocksize, string flatfile, string indexfile);
	int Build_Table(string input_file);
	int Search(string value);
private:
	string flatfile;
	string indexfile;
	int IndexSearch(string value);
};
#endif