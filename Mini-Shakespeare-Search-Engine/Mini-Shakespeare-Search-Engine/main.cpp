#include <iostream>
#include "dictionary.h"

int main(void)
{
	cout << "Start loading data..." << endl;

	stopDic stopWords("stopWords.txt");
	dictionary dic(".\\text", &stopWords);


	cout << "------Welcome to the SHAKESPEARE SEARCH ENGINE!------" << endl;
	cout << "Type a number N to have N times single word search..." << endl;
	cout << "Or, type in anything other string to make questions! " << endl;
	int N;
	cin >> N;
	double rate;
	// The good function helps to check if it's an int;
	if (cin.good()) {
		dic.singleWordQuery(N);
	}
	else {
		cout << "Before making questions, please input the threshold rate..." << endl;
		cin >> rate;
		/*
		* 待完成的工作还有：
		* 0.创建多个字典对象，创建多个文件夹，象征性地完成大文件管理的工作；
		*	我已经创建了Dics对象了（见dictionary.h），就用这个Dics管理下属的一串的dictionary[]我感觉就ok，
		*	然后下面这些操作都对Dics去查，查出来的结果汇总一下；
		* 1.根据句子，筛选某个rate下取and的结果；
		* 2.识别减号，把减号前后的结果求差集；
		* 3.在singleWordQuery中设计模糊查询；（搞不出来就算了）
		*/
	}

	return 0;
}