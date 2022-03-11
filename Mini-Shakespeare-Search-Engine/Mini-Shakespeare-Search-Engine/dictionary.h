#pragma once
#include "BPlusTree.h"
#include "porter2_stemmer.h"
#include <iostream>
#include <string> 
#include <fstream> 
#include <io.h>
using namespace std;

/// <summary>
/// This class is used for storing words;
/// </summary>
class dictionary
{
public:
	node* root;
	class stopDic* stopWords;
	dictionary() {};
	dictionary(const string& docPath, stopDic* stopWords);
	void getDocAndScan(const string& in_name, const int& docCount);
	void singleWordQuery(int N);
	term* searchSingleWord(const string& word);

};


class stopDic : public dictionary
{
public:
	stopDic(const string& docPath);
	bool contain(const string& word);
};

class Dics
{
public:
	int N;
	dictionary* d;
};
