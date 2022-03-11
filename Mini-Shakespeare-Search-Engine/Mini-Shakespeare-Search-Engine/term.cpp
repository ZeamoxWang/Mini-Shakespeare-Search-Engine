#include "term.h"

term::term(string word, int doc, int pos):word(word), freq(1)
{
	this->postingList.push_back(postingNode(doc, pos));
}

void term::print()
{
	cout << "Word \"" << this->word << "\" appears in: ";
	for (int i = 0; i < this->postingList.size(); i++) {
		this->postingList[i].print();
	}
	cout << endl;
}

/// <summary>
/// If the doc has had this word, return true and change its posting list;
/// If the doc doesn't have this word, return false;
/// If this term appears at first time, it's posting list could be built;
/// </summary>
/// <param name="doc"></param>
/// <returns></returns>
bool term::visit(int doc, int pos)
{

	// We compare every node's doc index;
	int i;
	for (i = 0; i < postingList.size(); i++) {
		if (this->postingList[i].doc == doc) {
			this->postingList[i].count += 1;
			this->postingList[i].pos.push_back(pos);
			return true;
		}
	}
	if (i == postingList.size()) {
		this->postingList.push_back(postingNode(doc, pos));
	}
	return false;
}