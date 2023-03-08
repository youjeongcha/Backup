#include<iostream>
#include<string>
#define max_len 100
using namespace std;

class Student
{
private:
	string name;
	int kor, eng, math, sum;
	float avg;
	int num;
	char Class;
public:
	Student() { num = 0; }
	~Student() {}
	void SetStudent(int _num);
	void showStudent();
	int getnum()
	{
		return num;
	}
	string getname()
	{
		return name;
	}
	char getClass()
	{
		return Class;
	}
};

void Student::SetStudent(int _num)
{
	cout << "�̸��� �Է� �Ͻÿ� : ";
	cin >> name;
	cout << "3������ ������ �Է��Ͻÿ�" << endl;
	cout << "���� : ";
	cin >> kor;
	cout << "���� : ";
	cin >> eng;
	cout << "���� : ";
	cin >> math;
	sum = kor + eng + math;
	avg = (float)sum / 3;
	num = _num;
	if (avg >= 90)
		Class = 'A';
	else if (avg >= 80)
		Class = 'B';
	else if (avg >= 70)
		Class = 'C';
	else if (avg >= 60)
		Class = 'D';
	else
		Class = 'F';
	return;
}

void Student::showStudent()
{
	cout << "----------------------" << endl;
	cout << num << "�� �л�" << endl;
	cout << "�̸� : " << name << endl;
	cout << "���� ���� : " << kor << endl << "���� ���� : " << math << endl << "���� ���� : " << eng << endl;
	cout << "�հ� ���� : " << sum << "\t ������� : " << avg << endl;
	cout << "��� : [ " << Class << "]" << endl << endl;
	return;
}

class Std_manager {
	Student* std[30];
public:
	~Std_manager() //�Ҹ��� public��
	{
		for (int i = 0; i < 30; i++)
		{
			delete std[i];
		}
	}
	static Std_manager* Get_Instance()
	{
		if (NULL == m_pInstance)
			m_pInstance = new Std_manager;
		return m_pInstance;
	}

	//gameManeager ���� ��쿡�� ���� �ڵ��� �� �� �ٿ� ���ų� �� �ᵵ ��������. �ٸ� ���ٰ� �޸� ���� ���� ������ class���� �ʿ��ϴ�.
	void Destroy()
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}

	void display();

private:
	static Std_manager* m_pInstance; //static �Լ��� ����Ϸ��� static���� ����.
	Std_manager(); //������ privte�� �ڴ�� �������� ���ϰ�

	void setStudent();
	void showStudent();
	void findNumber();
	void findname();
	void findClass();
};

//static ��� ������ ��� ��ü�� ����. ���α׷� ��ü �������� �޸� ������ �Ǿ�� �Ѵ�. �ݵ�� ���� �������� ���� �� �ʱ�ȭ.
Std_manager* Std_manager::m_pInstance = NULL; //NULL �ϴ°� �ʱ�ȭ. �տ��� ����.

Std_manager::Std_manager()
{
	for (int i = 0; i < 30; i++)
		std[i] = new Student;
}

void Std_manager::display() {
	int sel;
	while (true)
	{
		cout << "=========================" << endl;
		cout << "   1.�л� ���" << endl;
		cout << "   2.��ü �л����� ���" << endl;
		cout << "   3.�л� ��ȣ �˻�" << endl;
		cout << "   4.�л� �̸� �˻�" << endl;
		cout << "   5.��޺� ���" << endl;
		cout << "   0.����" << endl;
		cout << "=========================" << endl;
		cin >> sel;
		switch (sel) {
		case 1:
			setStudent();
			break;
		case 2:
			showStudent();
			break;
		case 3:
			findNumber();
			break;
		case 4:
			findname();
			break;
		case 5:
			findClass();
			break;
		case 0:return;
		default:cout << "�߸� �Է� " << endl;
		}
		system("pause"); system("cls");
	}
}

void Std_manager::setStudent()
{
	for (int i = 0; i < 30; i++)
	{
		if (std[i]->getnum() == 0)
		{
			std[i]->SetStudent(i + 1);
			return;
		}
	}
	cout << "�л��� ���� ��� �Ǿ����ϴ�." << endl;
}

void Std_manager::showStudent()
{
	for (int i = 0; i < 30; i++)
	{
		if (std[i]->getnum() != 0)
		{
			std[i]->showStudent();
		}
		else
			return;
	}
}

void Std_manager::findNumber()
{
	int _find;
	cout << "ã�� �л��ǹ�ȣ�� �Է� �Ͻÿ�";
	cin >> _find;
	for (int i = 0; i < 30; i++)
	{
		if (std[i]->getnum() == _find)
		{
			std[i]->showStudent();
			return;
		}
	}
	cout << endl << "�ش� ��ȣ�� �л��� �����ϴ�." << endl;
}

void Std_manager::findname()
{
	string _find;
	int find_num = 0;
	cout << "ã�� �л����̸��� �Է� �Ͻÿ�";
	cin >> _find;
	for (int i = 0; i < 30; i++)
	{
		if (std[i]->getname() == _find)
		{
			std[i]->showStudent();
			find_num++;
		}
	}
	if (find_num == 0)
		cout << "�ش� �̸��� �л��� �����ϴ�." << endl;
}

void Std_manager::findClass()
{
	int _find = 0;
	cout << "========= [ A ] =========" << endl;
	for (int i = 0; i < 30; i++)
	{
		if (std[i]->getClass() == 'A')
		{
			std[i]->showStudent();
			_find++;
		}
	}
	cout << "�� " << _find << "��" << endl;
	cout << "=========================" << endl << endl << endl;
	_find = 0;
	cout << "========= [ B ] =========" << endl;
	for (int i = 0; i < 30; i++)
	{
		if (std[i]->getClass() == 'B')
		{
			std[i]->showStudent();
			_find++;
		}
	}
	cout << "�� " << _find << "��" << endl;
	cout << "=========================" << endl;
	_find = 0;
	cout << "========= [ C ] =========" << endl;
	for (int i = 0; i < 30; i++)
	{
		if (std[i]->getClass() == 'C')
		{
			std[i]->showStudent();
			_find++;
		}
	}
	cout << "�� " << _find << "��" << endl;
	cout << "=========================" << endl;
	_find = 0;
	cout << "========= [ D ] =========" << endl;
	for (int i = 0; i < 30; i++)
	{
		if (std[i]->getClass() == 'D')
		{
			std[i]->showStudent();
			_find++;
		}
	}
	cout << "�� " << _find << "��" << endl;
	cout << "=========================" << endl;
	_find = 0;
	cout << "========= [ F ] =========" << endl;
	for (int i = 0; i < 30; i++)
	{
		if (std[i]->getClass() == 'F')
		{
			std[i]->showStudent();
			_find++;
		}
	}
	cout << "�� " << _find << "��" << endl;
	cout << "=========================" << endl;

}

#define stdMgr Std_manager::Get_Instance()

void main() {
	//Std_manager Std_Manager;
	//Std_Manager.display();
	//static �������� ���α׷� ���ۺ��� �޸� ����.(��ü ���� ������ �޸� ����)
	stdMgr->display();
}