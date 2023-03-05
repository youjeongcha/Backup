#pragma once
#include<iostream>
#include<string>
using namespace std;
class Quiz
{
public:
	void Quiz1(int inum1, int inum2);
	void Quiz1(char ch, int inum);
	void Quiz2(string str);
	void Quiz2(string str1, string str2);
	void Quiz3(int iarr[],int size);
	void Quiz3(char charr[],int size);
	Quiz();
	~Quiz();
};

