#pragma once
#include <vector>
#include <iostream>
using namespace std;
class postingNode
{
public:
	int doc; // Store its in what file;
	int count; // Store how many times it appears in this file;
	vector<int> pos; // Store its position in the file;
	postingNode(int doc, int p);
	void print();
};

