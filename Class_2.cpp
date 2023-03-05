#include<iostream>
#include<string>
using namespace std;
//����ü������ �������
enum GENDER
{
	GENDER_MAN,
	GENDER_WOMAN
};

class Person
{
private: //������ ����
	string Name;
	int Age;
	GENDER Gender;
public: //ĸ��ȭ //������ ������ ������ �Ǿ���ϰ�. ������ ������ ����ϱ� ���� ���
	void SetName(string _Name, int _Age, GENDER _Gender) //_ //��������
	{//Class1������ ������ ��𼭵��� ���� �����ߴ�. > �� �Լ��� ���ؼ��� ���ٰ����ϰ�.
		//�������� ��Ȳ�� ���� �� �ȿ����� ������ �� �ְԲ�(�ߴ��� �ɰ� �����, ���� ���� ����)
		Name = _Name;
		Age = _Age;
		Gender = _Gender;
	}
	string GetName()
	{//��� �Լ�
		return Name;
	}
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
	Person P1;
	P1.SetName( "������", 35, GENDER_WOMAN);
	cout << "======" << P1.GetName() << "�� ����" << "======" << endl;
	//P1.Name�̳� �Լ��� �� ��ġ�� �ű⼭ �ű� ������ ��? >> ���� ���ÿ�
	P1.ShowPerson(); //
}