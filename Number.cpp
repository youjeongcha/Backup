#include "Number.h"



Number::Number()
{
	string str;
	m_czNumber = NULL;
	while (1)
	{
		cout << "전화번호 입력 : ";
		cin >> str;
		if (str[1] == '1' && str.length() == 11)
		{
			SetNumber(3, 8, str);
			break;
		}
		else if (str[1] == '2' && str.length() == 9)
		{
			SetNumber(2, 6, str);
			break;
		}
		else if (str[1] >= '3' && str[1] <= '6' && str.length() == 10)
		{
			SetNumber(3, 7, str);
			break;
		}
		else
		{
			cout << "번호를 잘못 입력하셧습니다" << endl;
			system("pause");
		}
	}
}


void Number::SetNumber(int FirstBar, int SecondBar, string str)
{
	int i, j;
	if (m_czNumber != NULL) //안전장치. 현재 코드에는 동적할당을 여러번 사용하지 않아서 이용하지 않지만
		//혹시나 동적할당 해제가 안 되었을 경우를 대비
		delete[] m_czNumber;
	m_czNumber = new char[str.length() + 3];//Null 자리까지 챙겨줌
	for (i = 0, j = 0; j < str.length(); i++)
	{
		if (i == FirstBar || i == SecondBar)
			m_czNumber[i] = '-';
		else
		{
			m_czNumber[i] = str[j];
			j++;
		}
	}
	m_czNumber[i] = NULL;//마지막에 NULL
}

void Number::NumberDraw()
{
	cout << "완성된 번호 : " << m_czNumber << endl; //char 동적할당 변수명 호출해도 다 뜸
}
Number::~Number()
{
	delete[] m_czNumber;
}
