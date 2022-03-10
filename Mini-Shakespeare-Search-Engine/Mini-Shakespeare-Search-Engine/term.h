#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "postingNode.h"
using namespace std;


/// <summary>
/// This class is the end of B+ tree and the beginning of a posting list;
/// </summary>
class term
{
public:
	term(string word, int doc, int pos);
	string word;
	int freq;
	vector<postingNode> postingList;
	bool visit(int doc, int pos);
	void print();
};

