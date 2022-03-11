#include "dictionary.h"

void dictionary::singleWordQuery(int N)
{
	string word;
	term* tmp;
	for (int i = 0; i < N; i++) {

		cin >> word;

		// Cut out the punctuations;
		Porter2Stemmer::trim(word);
		// Analysis the word's stem;
		Porter2Stemmer::stem(word);

		if (this->stopWords->contain(word)) {
			cout << "Please do not input a stop word!" << endl;
		}
		else {
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

		// Cut out the punctuations;
		Porter2Stemmer::trim(str);
		// Analysis the word's stem;
		Porter2Stemmer::stem(str);
		// Analysis for stop words!
		if (this->stopWords->contain(str)) {
			continue;
		}
		else {
			wordsCount += 1;
			this->root = this->root->insert(str, docCount, wordsCount);
		}

	}

}


dictionary::dictionary(const string& docPath, stopDic* stopW)
{
	this->stopWords = stopW;
	this->root = new leaf("", NULL, leaf1, -1, -1);
	struct _finddata_t fileinfo;
	string in_path = docPath;
	string in_name;
	int docCount = 0;
	string curr = in_path + "\\*.txt";
	long handle;
	// If we can't find any file;
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
			// We enumerate the files automatically;
			getDocAndScan(in_name, docCount);
		}
		_findclose(handle);
	}

	cout << "OK! All of data have already been loaded! " << endl;
	cout << "\n\n\n\n\n";

}

stopDic::stopDic(const string& docPath)
{
	this->root = new leaf("", NULL, leaf1, 0, 0);
	struct _finddata_t fileinfo;
	ifstream fin(docPath);
	if (!fin) {
		cerr << "Open stop words file error!" << endl;
		exit(-1);
	}
	string str;
	while (fin >> str) {
		this->root = this->root->insert(str, 0, 0);
	}

	cout << "Stop words have already been loaded! " << endl;
}

bool stopDic::contain(const string& word)
{
	return this->root->contain(word);
}