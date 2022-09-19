#pragma once
#ifndef SDISK
#define SDISK
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


class Sdisk
{
public:
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
private:
string diskname;        // file name of software-disk
int numberofblocks;     // number of blocks on disk
int blocksize;          // block size in bytes
};
#endif