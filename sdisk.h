#pragma once
#ifndef SDISK
#define SDISK
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;


class Sdisk
{
public:
Sdisk();
/// <summary>
/// constructor: creation of the disk with the "formatting" of the device. This is meant to replicate a disk drive.
/// </summary>
/// <param name="diskname"></param>
/// <param name="numberofblocks"></param>
/// <param name="blocksize"></param>
Sdisk(string diskname, int numberofblocks, int blocksize);
/// <summary>
/// accessor: will retrieve a specific block from the disk
/// </summary>
/// <param name="blocknumber"></param>
/// <param name="buffer"></param>
/// <returns></returns>
int getblock(int blocknumber, string& buffer);
/// <summary>
/// mutator: will add specific block to the disk
/// </summary>
/// <param name="blocknumber"></param>
/// <param name="buffer"></param>
/// <returns></returns>
int putblock(int blocknumber, string buffer);
/// <summary>
/// accessor: returns the number of blocks on the sdisk
/// </summary>
/// <returns></returns>
int numofblocks();
/// <summary>
/// returns the size of the blocks on the disk
/// </summary>
/// <returns></returns>
int getblocksize();
/// <summary>
/// accessor:returns the status of the filesystem.
/// </summary>
/// <returns></returns>
int getstatus();
private:
string diskname;        // file name of software-disk
int numberofblocks;     // number of blocks on disk
int blocksize;          // block size in bytes
int diskstatus;			// the status of the disk
};
#endif