#include<iostream>
#include<string>
using namespace std;

enum GENDER
{
	GENDER_MAN,
	GENDER_WOMAN
};

class Person
{
public: //
	string Name;
	int Age;
	GENDER Gender;
	void ShowPerson()
	{
		cout << "�̸� : " << Name << endl;
		cout << "���� : " << Age << endl;
		cout << "���� : ";
		switch (Gender)
		{
		case GENDER_MAN:
			cout << "����" << endl;
			break;
		case GENDER_WOMAN:
			cout << "����" << endl;
			break;
		}
	}
};

void main()
{
	Person P1 = { "������",35,GENDER_WOMAN }; //public�̶� �����ϴ�
	cout << "======" << P1.Name << "�� ����" << "======" << endl;
	P1.ShowPerson(); //
}