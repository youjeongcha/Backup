#pragma once
#include"First.h"
#include"Second.h"
#include"Third.h"


void main()
{
	First first;
	int i1A;
	int i1B;
	char s1C;

	Second second;
	string s2A;
	string s2B;

	Third third;
	int i3A[5] = {};
	char c3B[5] = {};


	//1
	//1-1
	while (true)
	{
		cout << "1.정수 2개 입력 : ";
		cin >> i1A >> i1B;
		if (i1B >= 1)
			break;
		cout << i1B << "는 1보다 작습니다.\n";
	}
	//main.Get1();
	first.Test(i1A, i1B);
	//1-2
	while (true)
	{
		cout << "1.단일문자와 정수 입력 : ";
		cin >> s1C >> i1A;

		if ((s1C >= 'a' && s1C <= 'z') || (s1C >= 'A' && s1C <= 'Z'))
			break;
		cout << "영문자가 아닙니다.\n";
	}
	//main.Get2();
	first.Test(i1A, s1C);
	cout << "\n";


	//2
	//2-1
	cout << "2.문자열 하나 입력 : ";
	cin >> s2A;
	second.Test2(s2A);
	//2-2
	cout << "2.문자열 두 개 입력 : ";
	cin >> s2A >> s2B;
	second.Test2(s2A, s2B);
	cout << "\n";


	//3
	//3-1
	cout << "3.숫자 5개 입력 : ";
	for (int i = 0; i < 5; i++)
		cin >> i3A[i];
	third.Test3(i3A);
	//3-2
	cout << "3.단일문자 5개 입력 : ";
	for (int i = 0; i < 5; i++)
		cin >> c3B[i];
	third.Test3(c3B);
	cout << "\n";
}