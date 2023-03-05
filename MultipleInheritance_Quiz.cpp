#include <iostream>
using namespace std;

class Person
{
private:
	const int iAge = 0;
	string sName;
	string sGender;
public:
	Person(int a) : iAge(a)
	{
		cout << "나이 입력 : ";
		//cin >> iAge;
		cout << "이름 입력 : ";
		cin >> sName;
		cout << "성별 입력 : ";
		cin >> sGender;
	 }

protected:
	void Print()
	{
		cout << "나이 : " << iAge << "\n";
		cout << "이름 : " << sName << "\n";
		cout << "성별 : " << sGender << "\n";
	}
};

class School
{
private:
	int iGrade;
	int iClass;
	int iNumber;
public:
	School()
	{
		cout << "학년 입력 : ";
		cin >> iGrade;
		cout << "반 입력 : ";
		cin >> iClass;
		cout << "학생 번호 입력 : ";
		cin >> iNumber;
	}
protected:
	void Print()
	{
		cout << iGrade << " 학년 " << iClass << " 반 " << iNumber << " 번 학생\n";
	}
};

class Student : protected School, protected Person
{
public:
	Student() : Person(9)
	{
		system("cls");
		School::Print();
		Person::Print();
	}
};

void main()
{
	Student stu;
}