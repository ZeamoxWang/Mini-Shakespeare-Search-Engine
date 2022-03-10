#pragma once
#include <vector>
#include <iostream>
using namespace std;
class postingNode
{
public:
	int doc;
	int count;
	vector<int> pos;
	postingNode(int doc, int p);
	void print();
};

