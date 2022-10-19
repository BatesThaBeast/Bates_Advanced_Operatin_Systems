#pragma once
#ifndef FILESYS
#define FILESYS

#include "sdisk.h"

using namespace std;

class Filesys : public Sdisk
{
public:
/// <summary>
/// constructor: Creates an instance of Filesys.
/// </summary>
/// <param name="diskname"></param>
/// <param name="number_of_blocks"></param>
/// <param name="block_size"></param>
Filesys(string diskname, int number_of_blocks, int block_size);
/// <summary>
/// This module writes FAT and ROOT to the sdisk (closing the sdisk).
/// </summary>
/// <returns></returns>
int fsclose();
/// <summary>
/// This function adds an entry for the string file in ROOT with an initial first block of 0 (empty). It returns error codes of 1 if successful and 0 otherwise (no room or file already exists).
/// </summary>
/// <param name="file"></param>
/// <returns></returns>
int newfile(string file);
/// <summary>
/// This function removes the entry file from ROOT if the file is empty (first block is 0). It returns error codes of 1 if successful and 0 otherwise (not empty or file does not exist).
/// </summary>
/// <param name="file"></param>
/// <returns></returns>
int rmfile(string file);
/// <summary>
/// This function returns the block number of the first block in file. It returns the error code of 0 if the file does not exist.
/// </summary>
/// <param name="file"></param>
/// <returns></returns>
int getfirstblock(string file);
/// <summary>
/// This function adds a block of data stored in the string buffer to the end of file F and returns the block number. It returns error code 0 if the file does not exist, and returns -1 if there are no available blocks (file system is full!).
/// </summary>
/// <param name="file"></param>
/// <param name="block"></param>
/// <returns></returns>
int addblock(string file, string block);
/// <summary>
/// The function removes block numbered blocknumber from file and returns an error code of 1 if successful and 0 otherwise.
/// </summary>
/// <param name="file"></param>
/// <param name="blocknumber"></param>
/// <returns></returns>
int delblock(string file, int blocknumber);
/// <summary>
/// gets block numbered blocknumber from file and stores the data in the string buffer.
/// It returns an error code of 1 if successful and 0 otherwise.
/// </summary>
/// <param name="file"></param>
/// <param name="blocknumber"></param>
/// <param name="buffer"></param>
/// <returns></returns>
int readblock(string file, int blocknumber, string& buffer);
/// <summary>
/// writes the buffer to the block numbered blocknumber in file. It returns an appropriate error code.
/// </summary>
/// <param name="file"></param>
/// <param name="blocknumber"></param>
/// <param name="buffer"></param>
/// <returns></returns>
int writeblock(string file, int blocknumber, string buffer);
/// <summary>
/// returns the number of the block that follows blocknumber in file. 
/// It will return 0 if blocknumber is the last block and -1 if some other error has occurred 
/// (such as file is not in the root directory, or blocknumber is not a block in file.)
/// </summary>
/// <param name="file"></param>
/// <param name="blocknumber"></param>
/// <returns></returns>
int nextblock(string file, int blocknumber);
private:
int rootsize; // maximum number of entries in ROOT
int fatsize; // number of blocks occupied by FAT
vector<string> filename; // filenames in ROOT
vector<int> firstblock; // firstblocks in ROOT
vector<int> fat; //FAT
/// <summary>
/// builds the file system
/// </summary>
/// <returns></returns>
int buildfs();
/// <summary>
/// reads the file system
/// </summary>
/// <returns></returns>
int readfs();
/// <summary>
/// This module writes FAT and ROOT to the sdisk. It should be used every time FAT and ROOT are modified.
/// </summary>
/// <returns></returns>
int fssynch();
bool fbcheck(string file, int blocknumber);
};
#endif