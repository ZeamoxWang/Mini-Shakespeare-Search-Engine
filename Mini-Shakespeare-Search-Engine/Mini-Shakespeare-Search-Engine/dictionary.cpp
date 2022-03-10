#include "dictionary.h"

void dictionary::query(int N)
{
	string word;
	term* tmp;
	for (int i = 0; i < N; i++) {

		cin >> word;

		/* The string needs to be stemmed there......*/

		// You can retrive this return value to do further analysis;
		tmp = this->searchSingleWord(word);
		if (tmp == NULL) {
			cout << "This word doesn't appear in anywhere!" << endl;

		/* Can we give some search suggestions here? */
		}
		else {
			tmp->print();
		}

	}

}

term* dictionary::searchSingleWord(const string& word)
{
	leaf* l = (leaf*)this->root->search(word);
	if (word == l->data[0]) {
		return l->t[0];
	}
	else if (word == l->data[1]) {
		return l->t[1];
	}
	else if (word == l->data[2]) {
		return l->t[2];
	}
	
	return NULL;
}

void dictionary::getDocAndScan(const string& in_name, const int& docCount)
{
	ifstream fin(in_name);
	if (!fin){
		cerr << "Open file error!" << endl;
		exit(-1);
	}
	string str;
	int wordsCount = 0;
	while (fin >> str) {

		/* The string needs to be stemmed there......*/

		wordsCount += 1;
		this->root = this->root->insert(str, docCount, wordsCount);
	}

}

dictionary::dictionary(const string& docPath)
{
	this->root = new leaf("Shakespeare", NULL, leaf1, -1, -1);
	struct _finddata_t fileinfo;
	string in_path = docPath;
	string in_name;
	int docCount = 0;
	string curr = in_path + "\\*.txt";
	long handle;
	if ((handle = _findfirst(curr.c_str(), &fileinfo)) == -1L)
	{
		cout << "There is no txt file!" << endl;
	}
	else
	{
		in_name = in_path + "\\" + fileinfo.name;
		getDocAndScan(in_name, docCount);
		while (!(_findnext(handle, &fileinfo)))
		{
			in_name = in_path + "\\" + fileinfo.name;
			docCount += 1;
			getDocAndScan(in_name, docCount);
		}
		_findclose(handle);
	}

	cout << "OK! Data has already been loaded! " << endl;

}
