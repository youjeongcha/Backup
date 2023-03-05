#include"Quiz.h"
#include<conio.h>

#define ARRMAX 5

void main()
{
	int num1, num2, iarr[ARRMAX];
	char ch, charr[ARRMAX];
	string str1, str2;
	Quiz quiz;
	cout << "1.정수 2개 입력 :";
	cin >> num1 >> num2;
	quiz.Quiz1(num1, num2);
	cout << "1.단일문자와 정수 입력 :";
	cin >> ch >> num1;
	quiz.Quiz1(ch, num1);
	cout << "2.문자열 하나 입력 : ";
	cin >> str1;
	quiz.Quiz2(str1);
	cout << "2.문자열 두개 입력 : ";
	cin >> str1 >> str2;
	quiz.Quiz2(str1, str2);
	cout << "3.숫자 5개 입력 : ";
	for (int i = 0; i < ARRMAX; i++)
		cin >> iarr[i];
	quiz.Quiz3(iarr,ARRMAX);
	cout << "3.단일문자 5개 입력 : ";
	for (int i = 0; i < ARRMAX; i++)
		cin >> charr[i];
	quiz.Quiz3(charr, ARRMAX);
	getch();
}