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
	string word; // Store the word itself;
	int freq; // Store the whole frequency in all the files;
	vector<postingNode> postingList; // Store its posting list;
	bool visit(int doc, int pos);
	void print();
};

