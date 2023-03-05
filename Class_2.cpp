#include<iostream>
#include<string>
using namespace std;
//구조체에서는 멤버변수
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
public: //캡슐화 //정보의 은닉이 전제가 되어야하고. 은닉한 저보를 사용하기 위한 방법
	void SetName(string _Name, int _Age, GENDER _Gender) //_ //변수명명법
	{//Class1에서는 변수가 어디서든지 접근 가능했다. > 이 함수를 통해서만 접근가능하게.
		//제한적인 상황을 만들어서 이 안에서만 관리할 수 있게끔(중단점 걸고 디버깅, 유지 보수 용이)
		Name = _Name;
		Age = _Age;
		Gender = _Gender;
	}
	string GetName()
	{//멤버 함수
		return Name;
	}
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
	Person P1;
	P1.SetName( "아이유", 35, GENDER_WOMAN);
	cout << "======" << P1.GetName() << "의 정보" << "======" << endl;
	//P1.Name이나 함수를 또 거치나 거기서 거기 같은데 왜? >> 위에 보시오
	P1.ShowPerson(); //
}