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
		cout << "이름 : " << Name << endl;
		cout << "나이 : " << Age << endl;
		cout << "성별 : ";
		switch (Gender)
		{
		case GENDER_MAN:
			cout << "남자" << endl;
			break;
		case GENDER_WOMAN:
			cout << "여자" << endl;
			break;
		}
	}
};

void main()
{
	Person P1 = { "아이유",35,GENDER_WOMAN }; //public이라서 가능하다
	cout << "======" << P1.Name << "의 정보" << "======" << endl;
	P1.ShowPerson(); //
}