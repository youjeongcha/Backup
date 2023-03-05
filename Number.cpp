#include "Number.h"



Number::Number()
{
	string str;
	m_czNumber = NULL;
	while (1)
	{
		cout << "��ȭ��ȣ �Է� : ";
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
			cout << "��ȣ�� �߸� �Է��ϼ˽��ϴ�" << endl;
			system("pause");
		}
	}
}


void Number::SetNumber(int FirstBar, int SecondBar, string str)
{
	int i, j;
	if (m_czNumber != NULL) //������ġ. ���� �ڵ忡�� �����Ҵ��� ������ ������� �ʾƼ� �̿����� ������
		//Ȥ�ó� �����Ҵ� ������ �� �Ǿ��� ��츦 ���
		delete[] m_czNumber;
	m_czNumber = new char[str.length() + 3];//Null �ڸ����� ì����
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
	m_czNumber[i] = NULL;//�������� NULL
}

void Number::NumberDraw()
{
	cout << "�ϼ��� ��ȣ : " << m_czNumber << endl; //char �����Ҵ� ������ ȣ���ص� �� ��
}
Number::~Number()
{
	delete[] m_czNumber;
}
