#pragma once
#ifndef SHELL
#define SHELL

#include "filesys.h"

using namespace std;
class Shell : public Filesys
{
public :
	Shell(string filename, int numberofblocks, int blocksize);
	/// <summary>
	/// lists all files
	/// </summary>
	/// <returns></returns>
	int dir();
	/// <summary>
	/// add a new file using buffer as data
	/// </summary>
	/// <param name="file"></param>
	/// <param name="buffer"></param>
	/// <returns></returns>
	int add(string file, string buffer);
	/// <summary>
	/// deletes file
	/// </summary>
	/// <param name="file"></param>
	/// <returns></returns>
	int del(string file);
	/// <summary>
	/// lists the contents of file
	/// </summary>
	/// <param name="file"></param>
	/// <returns></returns>
	int type(string file);
	/// <summary>
	/// copies file 1 to file 2
	/// </summary>
	/// <param name="file1"></param>
	/// <param name="file2"></param>
	/// <returns></returns>
	int copy(string file1, string file2);
	int append(string file);
};
#endif