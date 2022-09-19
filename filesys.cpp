#include "filesys.h"

Filesys::Filesys(string diskname, int number_of_blocks, int block_size)
{

}

int Filesys::fsclose()
{

}
int Filesys::newfile(string file)
{

}
int Filesys::rmfile(string file)
{

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

}
int Filesys::writeblock(string file, int blocknumber, string buffer)
{

}
int Filesys::nextblock(string file, int blocknumber)
{

}
int Filesys::buildfs()
{

}
int Filesys::readfs()
{

}
int Filesys::fssynch()
{

}