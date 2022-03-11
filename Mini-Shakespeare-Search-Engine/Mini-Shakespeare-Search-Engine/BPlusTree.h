#pragma once
#include <iostream>
#include <deque>
#include "term.h"
#define ERROR "-ERROR-"
#define INSERTDONE "-INSERTDONE-"
#define DUPLICATED "-DUPLICATED-"
using namespace std;
/// <summary>
/// Set the type for every nodes;
/// </summary>
enum btype {
	inner2 = -2, inner1 = -1, leaf1 = 1, leaf2 = 2, leaf3 = 3
};

class node
{
private:
	friend class leaf;
	friend class dictionary;
	btype status; // Indicate the status of this node;
	string data[3]; // Store strings helping them sort out;
	node* pt[3]; // To its children;
	node* parent;

public:
	node(string n, node* par, btype status);
	node* search(string n);
	node* insert(string n, int doc, int pos);
	bool contain(const string& n);
	node* splitUpwards(string n, int doc, int pos);
	node* insert2Node(node* newL);
	string getMin();
	node* getRoot();
	void print();
};


/// <summary>
/// For any leaf, it should contain at leat one pointer to real data;
/// </summary>
class leaf : public node
{
public:
	leaf(string n, node* par, btype status, int doc, int pos);
	string insert2Leaf(string n, int doc, int pos);
	term* t[3]; // To real data (term);
};




