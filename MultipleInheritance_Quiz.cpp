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
		cout << "���� �Է� : ";
		//cin >> iAge;
		cout << "�̸� �Է� : ";
		cin >> sName;
		cout << "���� �Է� : ";
		cin >> sGender;
	 }

protected:
	void Print()
	{
		cout << "���� : " << iAge << "\n";
		cout << "�̸� : " << sName << "\n";
		cout << "���� : " << sGender << "\n";
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
		cout << "�г� �Է� : ";
		cin >> iGrade;
		cout << "�� �Է� : ";
		cin >> iClass;
		cout << "�л� ��ȣ �Է� : ";
		cin >> iNumber;
	}
protected:
	void Print()
	{
		cout << iGrade << " �г� " << iClass << " �� " << iNumber << " �� �л�\n";
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