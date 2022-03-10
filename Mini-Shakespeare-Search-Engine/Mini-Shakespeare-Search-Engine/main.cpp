#include <iostream>
#include "dictionary.h"

int main(void)
{
	cout << "Start loading data..." << endl;
	dictionary dic(".\\text");
	cout << "Please type in the number of words in your query..." << endl;
	int N;
	cin >> N;
	dic.query(N);
	
}