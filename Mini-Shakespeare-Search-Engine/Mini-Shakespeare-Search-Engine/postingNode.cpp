#include "postingNode.h"

postingNode::postingNode(int doc, int p):doc(doc), count(1)
{
	this->pos.push_back(p);
}

void postingNode::print()
{
	cout << "doc." << this->doc << " for " << this->count << " time(s) at the position of";
	for (int i = 0; i < this->pos.size(); i++) {
		cout << " " << this->pos[i];
	}
	cout << "; ";
}