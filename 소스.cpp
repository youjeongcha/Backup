#include<iostream>
#include"Quiz.h"
using namespace std;

void main()
{
	Quiz Q1, Q2(100), Q3(5, 10);
	cout << "Q1() : " << Q1.GetSum() << endl;
	cout << "Q2(100) : " << Q2.GetSum() << endl;
	cout << "Q1(5,10) : " << Q3.GetSum() << endl;
}