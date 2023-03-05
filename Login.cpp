#include<iostream>
#include<string> //string �̿��Ҷ�
#include<map>
#include<Windows.h> //�̰� �ᵵ �Ǵ���
using namespace std;

#define FULLUSER 10
#define IDCOUNT 3
#define PWCOUNT 8

typedef struct User
{
	//string id; //Ŷ���� ����ü �� �ʿ�X
	string pw;
	string name;
	int age;
	int ph;
	int mleage = 1000;
}User;

//---------------------------------------------
//-----------------ȸ�� ����-------------------
int Select(map<string, User> UserMap)
{
	int input;
	cout << "=====Login=====(ȸ����[" << UserMap.size() << "��])" << endl;
	cout << "   1.ȸ�� ����" << endl;
	cout << "   2.�α���" << endl;
	cout << "   3.����" << endl;
	cout << "�Է� : ";
	cin >> input;

	return input;
}

bool AlphaNumFunc(string input)
{
	for (int i = 0; i < input.length(); i++)
	{
		if (!(input[i] >= '0' && input[i] <= '9') && //!�̰� ���� Not�����ϴ�
			!(input[i] >= 'A' && input[i] <= 'Z') &&
			!(input[i] >= 'a' && input[i] <= 'z'))
			return false;
	}
	return true;
}

string SetId(map<string, User> UserMap)
{
	string input;

	while (TRUE)
	{
		system("cls");
		cout << "���̵� �Է�([3���ڡ�] AND [�ѱ�X] : ";
		cin >> input;

		map<string, User>::iterator iter = UserMap.find(input);
		bool idCheck = AlphaNumFunc(input);

		if ((idCheck == false) || (input.length() < IDCOUNT) || (iter != UserMap.end()))
		{
			if (idCheck == false)
				cout << "id�� �����̳� ���ڰ� �ƴմϴ�." << endl;
			if (input.length() < IDCOUNT)
				cout << "id�� ������ ���� �Դϴ�." << endl;
			else if (iter != UserMap.end())
				cout << "������ ���̵� �����մϴ�." << endl;
		}
		else
			break;
		system("pause");
	}
	return input;
}

bool PwFunc(string input)
{
	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] >= '0' && input[i] <= '9')
			return true;
	}
	return false;
}

string SetPw()
{
	string pw;
	string pwRe;

	while (TRUE)
	{
		system("cls");
		cout << "��й�ȣ �Է�([8���ڡ�]AND[����]AND[���� ����]) : ";
		cin >> pw;
		cout << "��й�ȣ Ȯ�� : ";
		cin >> pwRe;

		bool pwCheck = AlphaNumFunc(pw);
		bool pwNumCheck = PwFunc(pw);

		if ((pwCheck == false) || pw.length() < PWCOUNT || (pwNumCheck == false) || pw != pwRe)
		{
			if (pwCheck == false)
				cout << "id�� �����̳� ���ڰ� �ƴմϴ�." << endl;
			if (pw.length() < PWCOUNT)
				cout << "Passowrd�� �������� �����Դϴ�." << endl;
			if (pwNumCheck == false)
				cout << "Passowrd�� ���ڰ� ���ԵǾ� ���� �ʽ��ϴ�." << endl;
			if (pw != pwRe)
				cout << "��й�ȣ�� ��ġ���� �ʽ��ϴ�." << endl;
			system("pause");
		}
		else
			return pw;
	}
}

User SetInfo()
{
	User user;

	user.pw = SetPw();
	system("cls");
	cout << "�г��� �Է� : ";
	cin >> user.name;
	cout << "���� �Է� : ";
	cin >> user.age;
	cout << "�޴��� ��ȣ �Է� : ";
	cin >> user.ph;
	cout << "ȸ������ ����!! ���ϸ��� 1000�� ���" << endl;
	return user;
}

//---------------------------------------
//----------------�α���-----------------

int Menu()
{
	int select;
	cout << "========Menu========" << endl;
	cout << "   1.ȸ�� ����" << endl;
	cout << "   2.ȸ�� ���� ����" << endl;
	cout << "   3.�α׾ƿ�" << endl;
	cout << "�Է� : ";
	cin >> select;
	return select;
}

void UserInfo(string id, User user)
{
	cout << "============ȸ�� ����============" << endl;
	cout << "ID : " << id << "   �г��� : " << user.name << endl;
	cout << "���� : " << user.age << "   �޴��� ��ȣ : " << user.ph << endl;
	cout << "���ϸ��� : " << user.mleage << "��" << endl;
}

int ChangeSelect()
{
	int select;
	cout << "==================================" << endl;
	cout << "1.�г��� ����" << endl;
	cout << "2.���� ����" << endl;
	cout << "3.�޴��� ��ȣ ����" << endl;
	cout << "4.���ư���" << endl;
	cout << "�Է� : ";
	cin >> select;
	return select;
}

User ChangeUserInfo(string id, User user)
{
	string sTemp;
	int iTemp;
	while (TRUE)
	{
		system("cls");
		UserInfo(id, user);
		switch (ChangeSelect())
		{
		case 1:
			cout << "���� �г��� : " << user.name << endl;
			cout << "������ �г��� �Է� : ";
			sTemp = user.name;
			cin >> user.name;
			cout << sTemp << " -> " << user.name << endl;
			system("pause");
			break;
		case 2:
			cout << "���� ���� : " << user.age << endl;
			cout << "������ ���� �Է� : ";
			iTemp = user.age;
			cin >> user.age;
			cout << iTemp << " -> " << user.age << endl;
			system("pause");
			break;
		case 3:
			cout << "���� �޴��� ��ȣ : " << user.ph << endl;
			cout << "������ ���� �Է� : ";
			iTemp = user.ph;
			cin >> user.ph;
			cout << iTemp << " -> " << user.ph << endl;
			system("pause");
			break;
		case 4:
			return user;
		}
	}
}

void Modify(map<string,User>::iterator iter)
{
	while (TRUE)
	{
		system("cls");
		switch (Menu())
		{
		case 1://ȸ�� ����
			system("cls");
			UserInfo(iter->first, iter->second);
			system("pause");
			break;
		case 2://ȸ�� ���� ����
			iter->second = ChangeUserInfo(iter->first, iter->second);
			break;
		case 3://�α׾ƿ�
			return;
		}
	}
}

void Login(string id, map<string, User> UserMap)
{
	string idCheck;
	string pwCheck;

	while (TRUE)
	{
		system("cls");
		cout << "���̵� �Է� : ";
		cin >> idCheck;
		cout << "��й�ȣ �Է� : ";
		cin >> pwCheck;

		map<string, User>::iterator iter = UserMap.find(id);

		if (iter->first != idCheck)//(iter == UserMap.end()) ���̵� ������ ������ ���
		{
			cout << "�ش� ���̵� �����ϴ�\n";
			system("pause");
		}
		else
		{
			if (iter->second.pw != pwCheck)
			{
				cout << "��й�ȣ�� Ʋ�Ƚ��ϴ�\n";
				system("pause");
			}
			else
			{
				system("cls");
				Modify(iter); //id�� ������ iter�� �ٷ� �����ǰ� �ֱ�
				break;
			}
		}
	}
}

void main()
{
	map<string, User> UserMap;
	string id;//Ŷ���� ����ü�� �� �ʿ�X

	while (TRUE)
	{
		system("cls");
		switch (Select(UserMap))
		{
		case 1://ȸ�� ����
			//if (UserMap.max_size() == 1) 
			// //UserMap.max_size()�� mapContainer�� ���� �� �ִ� element�� maximum size��ȯ
			if (UserMap.size() == FULLUSER)
			{
				system("cls");
				cout << "ȸ������ �ο����� �� á���ϴ�." << endl;
				system("pause");
				break;
			}
			id = SetId(UserMap);
			UserMap[id] = SetInfo();
			system("pause");
			break;
		case 2://�α���
			Login(id, UserMap);
			break;
		case 3://����
			return;
		}
	}
}