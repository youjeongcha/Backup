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
private: //정보의 은닉
	string Name;
	int Age;
	GENDER Gender;
public: //캡슐화
	void SetName(string _Name, int _Age, GENDER _Gender); //
	string GetName(); //
	void ShowPerson(); //
};

//변수명명법
void Person::SetName(string _Name, int _Age, GENDER _Gender)
{//멤버함수 선언 person::
	Name = _Name;
	Age = _Age;
	Gender = _Gender;
}

string Person::GetName()
{
	return Name;
}

void Person::ShowPerson()
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

void main()
{
	Person P1;
	P1.SetName("아이유", 35, GENDER_WOMAN);
	cout << "======" << P1.GetName() << "의 정보" << "======" << endl;
	P1.ShowPerson();
}