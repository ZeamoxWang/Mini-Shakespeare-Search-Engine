#include "BPlusTree.h"

leaf::leaf(string n, node* par, btype status, int doc, int pos) :node(n, par, status)
{
	// We will finish the creation of terms in function SplitUpwards();
	if (par == NULL) {
		this->t[0] = new term(n, doc, pos);
	}
}

void node::print()
{
	deque<node*> d;
	d.push_back(this);
	node* temp;
	string lastnum = this->data[0];
	while (d.empty() != true) {
		temp = d.front();
		leaf* t = (leaf*)temp;
		// < or <=
		if (temp->data[0] < lastnum) {
			cout << endl;
		}
		lastnum = temp->data[0];
		switch (temp->status)
		{
		case inner1:
			cout << "[" << temp->data[0] << "]";
			d.push_back(temp->pt[0]); d.push_back(temp->pt[1]);
			break;
		case leaf1:
			cout << "[" << t->data[0] << ":" << t->t[0]->freq << "]";
			break;
		case inner2:
			cout << "[" << temp->data[0] << "," << temp->data[1] << "]";
			d.push_back(temp->pt[0]); d.push_back(temp->pt[1]); d.push_back(temp->pt[2]);
			break;
		case leaf2:
			cout << "[" << t->data[0] << ":" << t->t[0]->freq << "," << t->data[1] << ":" << t->t[1]->freq << "]";
			break;
		case leaf3:
			cout << "[" << t->data[0] << ":" << t->t[0]->freq << "," << t->data[1] << ":" << t->t[1]->freq << "," << t->data[2] << ":" << t->t[2]->freq << "]";
			break;
		}
		d.pop_front();
	}
	cout << endl;
}

node* node::getRoot()
{
	node* p = this;

	while (p->parent != NULL) {
		p = p->parent;
	}
	return p;
}

string node::getMin()
{
	node* p = this;
	while (p->status < 0) {
		p = p->pt[0];
	}
	return p->data[0];
}

node* node::insert2Node(node* newL)
{
	// Make sure its status;
	if (this->status > 0) {
		cout << "You cannot plug something onto a leaf!" << endl;
		return NULL;
	}
	// Find a proper position to insert the new leaf node;
	switch (this->status) {
	case inner1:
		if (newL->data[0] < this->pt[0]->data[0]) {
			this->pt[2] = this->pt[1];
			this->pt[1] = this->pt[0];
			this->pt[0] = newL;
			this->data[1] = this->data[0];
			this->data[0] = this->pt[1]->getMin();
		}
		else if (newL->data[0] > this->pt[0]->data[0] && newL->data[0] < this->pt[1]->data[0]) {
			this->pt[2] = this->pt[1];
			this->pt[1] = newL;
			this->data[1] = this->data[0];
			this->data[0] = this->pt[1]->getMin();
		}
		else if (newL->data[0] > this->pt[1]->data[0])
		{
			this->pt[2] = newL;
			this->data[1] = this->pt[2]->getMin();
		}
		this->status = inner2;
		return  NULL;
		break;

	case inner2:
		node* pop = NULL;
		if (newL->data[0] < this->pt[0]->data[0]) {
			pop = this->pt[2];
			this->pt[2] = this->pt[1];
			this->pt[1] = this->pt[0];
			this->pt[0] = newL;
		}
		else if (newL->data[0] > this->pt[0]->data[0] && newL->data[0] < this->pt[1]->data[0]) {
			pop = this->pt[2];
			this->pt[2] = this->pt[1];
			this->pt[1] = newL;
		}
		else if (newL->data[0] > this->pt[1]->data[0] && newL->data[0] < this->pt[2]->data[0]) {
			pop = this->pt[2];
			this->pt[2] = newL;
		}
		else if (newL->data[0] > this->pt[2]->data[0]) {
			pop = newL;
		}

		node* sibling = new node(pop->getMin(), this->parent, inner1);
		sibling->pt[0] = this->pt[2];
		sibling->pt[1] = pop;
		sibling->pt[0]->parent = sibling;
		sibling->pt[1]->parent = sibling;

		this->status = inner1;
		this->data[0] = this->pt[1]->getMin();
		return sibling;
		break;
	}
}

/// <summary>
/// 
/// </summary>
/// <param name="n">add data</param>
/// <param name="par">indicate its parents</param>
/// <param name="s">set its status (what it should be AFTER inserting n (& n1))</param>
/// <param name="n1">if its a leaf, there must be 2 int splited out</param>
node::node(string n, node* par, btype s)
{
	this->pt[0] = this->pt[1] = this->pt[2] = NULL;
	this->parent = par;
	this->data[0] = n;
	this->status = s;
	return;
}




/// <summary>
/// Return the leaf where it should live!
/// </summary>
/// <param name="n"></param>
/// <returns></returns>
node* node::search(string n)
{
	if (this->status > 0) {
		return this;
	}
	if (this->status == inner1) {
		if (n < data[0]) {
			return this->pt[0]->search(n);
		}
		else if (n >= data[0]) {
			return this->pt[1]->search(n);
		}
	}
	else if (this->status == inner2) {
		if (n < data[0]) {
			return this->pt[0]->search(n);
		}
		else if (n >= data[0] && n < data[1]) {
			return this->pt[1]->search(n);
		}
		else if (n >= data[1]) {
			return this->pt[2]->search(n);
		}
	}
}

/// <summary>
/// If found, return DUPLICATED;
/// If not found, insert the data, reconstruct the data in leaf, and pop out the biggest one! 
/// IF IT'S NOT A LEAF, RETURN ERROR!
/// </summary>
/// <param name="n"></param>
/// <returns></returns>
string leaf::insert2Leaf(string n, int doc, int pos)
{
	if (this->status < 0) {
		return ERROR;
	}

	if (n == this->data[0] || n == this->data[1] || n == this->data[2]) {
		return DUPLICATED;
	}

	switch (this->status)
	{
	case leaf1:
		if (n < data[0]) {
			data[1] = data[0];
			data[0] = n;
			t[1] = t[0];
			t[0] = new term(n, doc, pos);
		}
		else if (n > data[0]) {
			data[1] = n;
			t[1] = new term(n, doc, pos);
		}
		this->status = leaf2;
		return INSERTDONE;
		break;

	case leaf2:
		if (n < data[0]) {
			data[2] = data[1];
			data[1] = data[0];
			data[0] = n;
			t[2] = t[1];
			t[1] = t[0];
			t[0] = new term(n, doc, pos);
		}
		else if (n > data[0] && n < data[1]) {
			data[2] = data[1];
			data[1] = n;
			t[2] = t[1];
			t[1] = new term(n, doc, pos);
		}
		else if (n > data[1]) {
			data[2] = n;
			t[2] = new term(n, doc, pos);
		}
		this->status = leaf3;
		return INSERTDONE;
		break;

	case leaf3:
		// We don't create a new term at this time;
		string pop;
		if (n < data[0]) {
			pop = data[2];
			data[2] = data[1];
			data[1] = data[0];
			data[0] = n;

		}
		else if (n > data[0] && n < data[1]) {
			pop = data[2];
			data[2] = data[1];
			data[1] = n;
		}
		else if (n > data[1] && n < data[2]) {
			pop = data[2];
			data[2] = n;
		}
		else if (n > data[2]) {
			pop = n;
		}
		return pop;
		break;
	}

}

node* node::splitUpwards(string n, int doc, int pos)
{
	if (this->status != leaf3 || n < "") {
		cout << "What you want to split is not from a leaf!" << endl;
		return NULL;
	}
	node* oldRoot = this->getRoot();

	// Set a new leaf;
	leaf* originLeaf = (leaf*)this;
	leaf* newLeaf = new leaf(n, originLeaf->parent, leaf2, doc, pos);
	originLeaf->status = leaf2;

	// We should rearrange the data and terms of these leaves;
	newLeaf->data[1] = newLeaf->data[0];
	newLeaf->data[0] = originLeaf->data[2];
	int i;
	for (i = 0; i < 3; i++) {
		if (originLeaf->data[i] != originLeaf->t[i]->word) {
			break;
		}
	}

	switch (i) {
	case 3:
		// i == 3 means that the poped word is the biggest one and now it's in newLeaf->data[1];
		newLeaf->t[1] = new term(newLeaf->data[1], doc, pos);
		newLeaf->t[0] = originLeaf->t[2];
		break;
	case 2:
		newLeaf->t[1] = originLeaf->t[2];
		newLeaf->t[0] = new term(newLeaf->data[0], doc, pos);
		break;
	case 1:
		newLeaf->t[1] = originLeaf->t[2];
		newLeaf->t[0] = originLeaf->t[1];
		originLeaf->t[1] = new term(originLeaf->data[1], doc, pos);
		break;
	case 0:
		newLeaf->t[1] = originLeaf->t[2];
		newLeaf->t[0] = originLeaf->t[1];
		originLeaf->t[1] = originLeaf->t[0];
		originLeaf->t[0] = new term(originLeaf->data[0], doc, pos);
		break;
	}


	if (originLeaf->parent != NULL) {
		node* plugged = originLeaf->parent->insert2Node(newLeaf);
		while (plugged != NULL && plugged->parent != NULL) {
			plugged = plugged->parent->insert2Node(plugged);
		}
		if (plugged != NULL && plugged->parent == NULL) {
			node* newRoot = new node(plugged->getMin(), NULL, inner1);
			newRoot->pt[0] = oldRoot;
			newRoot->pt[0]->parent = newRoot;
			newRoot->pt[1] = plugged;
			newRoot->pt[1]->parent = newRoot;
			return newRoot;
		}
	}
	else if (originLeaf->parent == NULL) {
		node* newRoot = new node(newLeaf->getMin(), NULL, inner1);
		newRoot->pt[0] = originLeaf;
		newRoot->pt[0]->parent = newRoot;
		newRoot->pt[1] = newLeaf;
		newRoot->pt[1]->parent = newRoot;
		return newRoot;
	}


	return NULL;
}

node* node::insert(string n, int doc, int pos)
{
	leaf* target = (leaf*)this->search(n);
	string insertReturn = target->insert2Leaf(n, doc, pos);
	if (insertReturn != INSERTDONE && insertReturn != DUPLICATED) {
		node* temp = target->splitUpwards(insertReturn, doc, pos);
		if (temp != NULL) {
			return temp;
		}
	}
	else if (insertReturn == DUPLICATED) {
		if (n == target->data[0]) {
			target->t[0]->visit(doc, pos);
		}
		else if (n == target->data[1]) {
			target->t[1]->visit(doc, pos);
		}
		else if (n == target->data[2]) {
			target->t[2]->visit(doc, pos);
		}
	}
	return this;
}

