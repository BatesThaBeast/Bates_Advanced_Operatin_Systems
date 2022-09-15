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
/// creation of the disk with the "formatting" of the device. This is meant to replicate a disk drive.
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
/// accessor: finds out how many blocks are on the disk
/// </summary>
/// <returns></returns>
int getnumberofblocks();
/// <summary>
/// accessor: finds out the size of the blocks on disk
/// </summary>
/// <returns></returns>
int getblocksize();
vector<string> block(string buffer, int b);
private:
string thediskname;        // file name of software-disk
int thenumberofblocks;     // number of blocks on disk
int theblocksize;          // block size in bytes
vector<string>theblocks;	//the actual blocks on the disk
vector<int>blockposition;	//position of the block
};
#endif