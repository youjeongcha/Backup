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
		cout << "1.���� 2�� �Է� : ";
		cin >> i1A >> i1B;
		if (i1B >= 1)
			break;
		cout << i1B << "�� 1���� �۽��ϴ�.\n";
	}
	//main.Get1();
	first.Test(i1A, i1B);
	//1-2
	while (true)
	{
		cout << "1.���Ϲ��ڿ� ���� �Է� : ";
		cin >> s1C >> i1A;

		if ((s1C >= 'a' && s1C <= 'z') || (s1C >= 'A' && s1C <= 'Z'))
			break;
		cout << "�����ڰ� �ƴմϴ�.\n";
	}
	//main.Get2();
	first.Test(i1A, s1C);
	cout << "\n";


	//2
	//2-1
	cout << "2.���ڿ� �ϳ� �Է� : ";
	cin >> s2A;
	second.Test2(s2A);
	//2-2
	cout << "2.���ڿ� �� �� �Է� : ";
	cin >> s2A >> s2B;
	second.Test2(s2A, s2B);
	cout << "\n";


	//3
	//3-1
	cout << "3.���� 5�� �Է� : ";
	for (int i = 0; i < 5; i++)
		cin >> i3A[i];
	third.Test3(i3A);
	//3-2
	cout << "3.���Ϲ��� 5�� �Է� : ";
	for (int i = 0; i < 5; i++)
		cin >> c3B[i];
	third.Test3(c3B);
	cout << "\n";
}