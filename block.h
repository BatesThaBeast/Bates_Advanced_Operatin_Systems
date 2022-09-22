#pragma once
#ifndef BLOCK
#define BLOCK
#include <vector>
#include <string>

using namespace std;
class Block
{
	/// <summary>
	/// Blocks the buffer into a list of blocks of size b
	/// </summary>
	/// <param name="buffer"></param>
	/// <param name="b"></param>
	/// <returns></returns>
	vector<string> block(string buffer, int b);
};
#endif