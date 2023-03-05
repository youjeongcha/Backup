#include"PhoneNumber.h"

void PhoneNumber::AddDash(int first, int second)
{
	//string* tmp = new string;//[length]; //동적할당 
	//lenght를 지우면 0만 들어온다. > string이 char과 다를바 없이 쓰임
	//stirng으로 할 이유가 없다.
	//숫자 하나하나가 string으로 존재해서 string 배열인셈
	//동적할당도 할 이유가 없다.

	string tmp;
	int j = 0;

	for (int i = 0; ph.length() > i; i++)//j여기에 기입도 가능.
	{
		if (i + j == first || i + j == second)
		{
			tmp += "-";
			j++;
		}
		tmp += ph[i];
	}
	setDPh(tmp);
}

void PhoneNumber::Main()
{
	while (true)
	{
		cout << "전화번호 입력 : ";
		cin >> ph;
		if (ph.length() == EOUL_LEN || ph.length() == AREA_LEN || ph.length() == MPH_LEN)//9(서울)//10(지역)//11(휴대폰)
		{
			if ((ph.length() == EOUL_LEN) && (ph[1] == '2'))
			{
				AddDash(2, 6);
				return;
			}
			else if ((ph.length() == AREA_LEN) && (ph[1] == '3' || ph[1] == '4' || ph[1] == '5' || ph[1] == '6'))
			{
				AddDash(3, 7);
				return;
			}
			else if ((ph.length() == MPH_LEN) && (ph[1] == '1'))
			{
				AddDash(3, 8);
				return;
			} 
		}
		cout << "번호를 잘못 입력하셨습니다.\n";
		system("pause");
		system("cls");
	}
}
