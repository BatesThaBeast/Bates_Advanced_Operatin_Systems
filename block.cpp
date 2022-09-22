#include "block.h"

vector<string> Block::block(string buffer, int b)
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