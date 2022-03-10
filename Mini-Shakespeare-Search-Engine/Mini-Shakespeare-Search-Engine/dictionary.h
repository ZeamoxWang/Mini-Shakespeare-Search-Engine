#pragma once
#include "BPlusTree.h"
#include <iostream>
#include <string> 
#include <fstream> 
#include <io.h>
using namespace std;

class dictionary
{
public:
	node* root;
	dictionary(const string& docPath);
	void getDocAndScan(const string& in_name, const int& docCount);
	void query(int N);
	term* searchSingleWord(const string& word);
};

