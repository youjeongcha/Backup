#include <iostream>
#include <string> //string �̿��Ҷ�
#include <Windows.h>
#include <list> //list �̿�
using namespace std;

#define IDLEN 3
#define PASSWORDLEN 8
#define IDMAX 10

struct Member //typedef struct Member �� �� �ϴ���
{//typedef�� c������ �ʿ��ߴ�.
	string Id;
	string Password;
	string Name;
	int Age;
	string PhonNumber;
	int Mileage;
};//Member ?


bool StringCheck(char Start, char End, char Check)
{//���Ǳ�� ����
	if (Check >= Start && Check <= End)
		return true;
	else return false;
}

string CreateID(list<Member> Member_List)
{
	bool EngCheck, IDCheck;
	string id;
	do
	{
		EngCheck = true;
		IDCheck = true;
		system("cls");
		cout << "���̵� �Է�([3���ڡ�] AND [�ѱ�X]) : ";
		cin >> id;
		for (int i = 0; i < id.length(); i++)
		{
			if (StringCheck('A', 'Z', id[i]) == false && StringCheck('a', 'z', id[i]) == false
				&& StringCheck('0', '9', id[i]) == false)
			{
				EngCheck = false;
				break;
			}
		}
		//auto i = 10.0f;�ϸ� i�� �Ǽ�
		for (auto iter = Member_List.begin(); iter != Member_List.end(); iter++)
			//auto�� �ڷ����� �ʱ⿡ ���� ������ �������ش�.
			//list<Member>::iterator iter�� �ϴ� �� �������� ����Ʈ
		{
			if (iter->Id == id)
				IDCheck = false;
		}
		if (IDCheck == false)
			cout << "������ ���̵� �����մϴ�." << endl;
		if (EngCheck == false)
			cout << "id�� ������ �ƴմϴ�." << endl;
		if (id.length() < IDLEN)
			cout << "id�� ������ ���� �Դϴ�." << endl;
		system("pause");
	} while (EngCheck == false || IDCheck == false || id.length() < IDLEN);
	return id;
}

string CreatePassword()
{
	string Password, ComparePassword;
	bool EngCheck, CompareCheck, IDCheck, NumberCheck; //IDCheck ?
	do
	{
		EngCheck = true;
		CompareCheck = true;
		NumberCheck = false;

		system("cls");
		cout << "��й�ȣ �Է�([8���ڡ�]AND[����]AND[���� ����]) : ";
		cin >> Password;
		for (int i = 0; i < Password.length(); i++)
		{//��� ��ȣ ���� üũ �ڵ��, ��й�ȣ Ȯ�� �ڵ��� ���� > ������ ����
			if (StringCheck('A', 'Z', Password[i]) == false && StringCheck('a', 'z', Password[i]) == false)
			{
				if (StringCheck('0', '9', Password[i]) == true)
					NumberCheck = true;
				else
					EngCheck = false;
			}
		}
		cout << "��й�ȣ Ȯ�� : ";
		cin >> ComparePassword;
		if (ComparePassword != Password)
			CompareCheck = false;

		if (EngCheck == false)
			cout << "password�� ������ �ƴմϴ�." << endl;
		if (Password.length() < PASSWORDLEN)
			cout << "Password�� �������� ���� �Դϴ�." << endl;
		if (NumberCheck == false)
			cout << "���ڰ� ���ԵǾ� ���� �ʽ��ϴ�." << endl;
		if (CompareCheck == false)
			cout << "��й�ȣ�� ��ġ���� �ʽ��ϴ�." << endl;
		system("pause");
	} while (EngCheck == false || CompareCheck == false || NumberCheck == false || Password.length() < PASSWORDLEN);
	return Password;
}

Member Join(list<Member> Member_List)
{
	bool EngCheck, CompareCheck, IDCheck; //?
	int CountNum = 0; //?
	string CheckPassword; //?
	Member member;
	member.Id = CreateID(Member_List);
	member.Password = CreatePassword();
	system("cls");
	cout << "�г��� �Է� : ";
	cin >> member.Name;
	cout << "���� �Է� :";
	cin >> member.Age;
	cout << "�޴��� ��ȣ �Է� : ";
	cin >> member.PhonNumber;
	cout << "ȸ������ ���� !! ���ϸ��� 1000�� ���" << endl;
	member.Mileage = 1000;
	system("pause");
	return member;
}

void SimpleShowID(Member member)
{
	cout << "============ȸ�� ����============" << endl;
	cout << "ID : " << member.Id << "   �г��� : " << member.Name << endl;
}

void ShowID(Member member)
{
	system("cls");
	SimpleShowID(member);
	cout << " ���� : " << member.Age << "��" << "   �޴��� ��ȣ : " << member.PhonNumber << endl;
	cout << "���ϸ��� : " << member.Mileage << "��" << endl;
}

void Setstring(string* str, string tmp)//����� ���� ����
{//����
	string tmpstr;
	tmpstr = *str;//���� //*str�� �ּҰ��ε� ���������� ó������. strcpy�� ������
	cout << "���� " << tmp << ": " << tmpstr << endl;
	cout << "������ " << tmp << "�Է� : ";
	cin >> *str;
	cout << tmpstr << " -> " << *str << endl;
	system("pause");
}

void Setint(int* num, string tmp)
{//����
	int tmpint;
	tmpint = *num;
	cout << "���� " << tmp << " : " << tmpint << endl;
	cout << "������ " << tmp << "�Է� : ";
	cin >> *num;
	cout << tmpint << " -> " << *num << endl;
	system("pause");
}

void SetID(list<Member>::iterator member)
{
	int Select;
	while (1)
	{
		ShowID(*member);
		cout << "===================" << endl;
		cout << "1.�г��� ����" << endl;
		cout << "2.���� ����" << endl;
		cout << "3.�޴��� ��ȣ ����" << endl;
		cout << "4.���ư���" << endl;
		cout << "�Է� : ";
		cin >> Select;
		switch (Select)
		{
		case 1:
			Setstring(&member->Name, "�г���");//���� //�ּ� ����? //"�г���"�� ���޵Ǵ� ���� ?
			break;
		case 2:
			Setint(&member->Age, "����");
			break;
		case 3:
			Setstring(&member->PhonNumber, "�޴��� ��ȣ");
			break;
		case 4:
			return;
		}
	}
}


void Display(list<Member>::iterator member)
{
	int Select;
	while (1)
	{
		system("cls");
		cout << "========Menu========" << endl;
		cout << "  1.ȸ�� ����" << endl;
		cout << "  2.ȸ�� ���� ����" << endl;
		cout << "  3.�α׾ƿ�" << endl;
		cout << "�Է� : ";
		cin >> Select;
		switch (Select)
		{
		case 1:
			ShowID(*member);
			system("pause");
			break;
		case 2:
			SetID(member);
			break;
		case 3:
			return;
		}
	}
}

void Login(list<Member>* MemberList)
{
	string tmpID, tmpPassword;
	system("cls");
	cout << "���̵� �Է� : ";
	cin >> tmpID;
	cout << "��й�ȣ �Է� : ";
	cin >> tmpPassword;
	for (auto iter = MemberList->begin(); iter != MemberList->end(); iter++) // ?
	{
		if (tmpID == iter->Id)
		{
			if (tmpPassword == iter->Password)
				Display(iter);
			else
				cout << "��й�ȣ�� Ʋ�Ƚ��ϴ�." << endl;
			return;
		}
	}
	cout << "�ش� ���̵� �����ϴ�." << endl;
}

void main()
{
	list<Member> MemberList;
	string TmpId, TmpPassword; // ?
	int Select;
	while (1)
	{
		system("cls");
		cout << "=====Login=====(ȸ����[" << MemberList.size() << "��])" << endl;
		cout << "   1.ȸ�� ����" << endl;
		cout << "   2.�α���" << endl;
		cout << "   3.����" << endl;
		cout << "�Է� : ";
		cin >> Select;
		switch (Select)
		{
		case 1:
			if (MemberList.size() >= IDMAX)
			{
				cout << "���̻� ȸ���� ����� �� �����ϴ�." << endl;
				break;
			}
			MemberList.push_back(Join(MemberList));
			break;
		case 2:
			Login(&MemberList);
			break;
		case 3:
			return;
		}
		system("pause");
	}
}

