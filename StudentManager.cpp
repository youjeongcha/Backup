#include "StudentManager.h" //".h"



StudentManager::StudentManager()
{
}


void StudentManager::Main()
{
	int Select;
	string strTmp;
	while (1)
	{
		system("cls");
		cout << "======�л����� ���α׷�======" << endl;
		cout << "      1.�л� ���" << endl;
		cout << "      2.�л� ���" << endl;
		cout << "      3.�л� �̸� �˻�" << endl;
		cout << "      4.����" << endl;
		cout << "   (�л� �� : " << m_StudentList.size() << ")" << endl;
		cout << "�Է� : ";
		cin >> Select;
		system("cls");
		switch (Select)
		{
		case 1:
			AddStudent();
			break;
		case 2:
			ShowStudentList();
			break;
		case 3:
				cout << "�̸� �Է� : ";
			cin >> strTmp;
			if (FindStudentName(strTmp) == false)
				cout << "�ش� �л��� �����ϴ�." << endl;
			break;
		case 4:
			return;
		}
		system("pause");
	}
}

void StudentManager::AddStudent()
{
	Student student; //#include "StudentManager.h"�� ���� ����
	if (m_StudentList.size() < STUDENT_MAX)
	{
		student.SetStudent(m_StudentList.size() + 1);
		m_StudentList.push_back(student);
	}
	else
		cout << "���̻� �л��� ����� �� �����ϴ�." << endl;
}

void StudentManager::ShowStudentList()
{
	for (auto iter = m_StudentList.begin(); iter != m_StudentList.end(); iter++)
		iter->ShowStudent(); //�ɹ��� �����Ѵ�.
}

bool StudentManager::FindStudentName(string Name)
{//�������� ó��
	bool Flag = false;
	for (auto iter = m_StudentList.begin(); iter != m_StudentList.end(); iter++)
	{
		if (iter->GetName() == Name)
		{
			iter->ShowStudent();
			Flag = true;
		}
	}
	return Flag;
}

StudentManager::~StudentManager()
{
}
