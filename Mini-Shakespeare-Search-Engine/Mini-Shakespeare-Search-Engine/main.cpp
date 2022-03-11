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
		* ����ɵĹ������У�
		* 0.��������ֵ���󣬴�������ļ��У������Ե���ɴ��ļ�����Ĺ�����
		*	���Ѿ�������Dics�����ˣ���dictionary.h�����������Dics����������һ����dictionary[]�Ҹо���ok��
		*	Ȼ��������Щ��������Dicsȥ�飬������Ľ������һ�£�
		* 1.���ݾ��ӣ�ɸѡĳ��rate��ȡand�Ľ����
		* 2.ʶ����ţ��Ѽ���ǰ��Ľ������
		* 3.��singleWordQuery�����ģ����ѯ�����㲻���������ˣ�
		*/
	}

	return 0;
}