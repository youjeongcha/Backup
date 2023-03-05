#include "StudentManager.h"



StudentManager::StudentManager()
{
}


void StudentManager::MainMenu()
{
	int Select;
	string strTmp;
	bool bTmp;
	int iTmp;
	while (1)
	{
		system("cls");
		cout << "======�л����� ���α׷�======" << endl;
		cout << "      1.�л� ���" << endl;
		cout << "      2.�л� ���<��ȣ��>" << endl;
		cout << "      3.�л� ���<�г��>" << endl;
		cout << "      4.�л� �˻�" << endl;
		cout << "      5.�г� �˻�" << endl;
		cout << "      6.������ �л� ����" << endl;
		cout << "      7.�л� ��ü ����" << endl;
		cout << "      8.����" << endl;
		cout << "   (�л� �� : " << GetStudentCount() << ")" << endl;
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
			for (int i = CLASS_START; i < CLASS_END; i++)
			{
				bTmp = ShowStudentClass((CLASS)i);
				if (!bTmp)
					cout << i << "�г� �л��� �����ϴ�." << endl;
			}
			break;
		case 4:
			cout << "�̸� �Է� : ";
			cin >> strTmp;
			bTmp = FindStudentName(strTmp);
			if (bTmp == false)
				cout << "�ش� �л��� �����ϴ�." << endl;
			break;
		case 5:
			cout << "�г� �Է� : ";
			cin >> iTmp;
			bTmp = ShowStudentClass((CLASS)iTmp);
			if (!bTmp)
				cout << iTmp << "�г� �л��� �����ϴ�." << endl;
			break;
		case 6:
			DeleteStudent();
			break;
		case 7:
			ClearStudent();
			break;
		case 8:
			ClearStudent();
			return;
		}
		system("pause");
	}
}

void StudentManager::AddStudent()
{
	if (m_StudentList.size() < STUDENT_MAX)
	{
		Student st;
		st.SetStudent(m_StudentList.size());
		m_StudentList.push_back(st);
	}
	else
		cout << "���̻� �л��� ����� �� �����ϴ�." << endl;
}

void StudentManager::ShowStudentList()
{
	for (list<Student>::iterator iter = m_StudentList.begin(); iter != m_StudentList.end(); iter++)
		iter->ShowStudent();
}

bool StudentManager::FindStudentName(string Name)
{
	for (list<Student>::iterator iter = m_StudentList.begin(); iter != m_StudentList.end(); iter++)
	{
		if (iter->GetName() == Name)
		{
			iter->ShowStudent();
			return true;
		}
	}
	return false;
}

bool StudentManager::ShowStudentClass(CLASS Class)
{
	bool State = false;
	cout << "������������" << (int)Class << " �г⦡����������" << endl;
	for (list<Student>::iterator iter = m_StudentList.begin(); iter != m_StudentList.end(); iter++)
	{
		if (iter->GetClass() == Class)
		{
			iter->ShowStudent();
			State = true;
		}
	}
	cout << "������������������������������" << endl;
	return State;
}


void StudentManager::DeleteStudent()
{
	if (m_StudentList.empty())
		cout << "������ �л��� �����ϴ�." << endl;
	else
	{
		m_StudentList.back().ShowStudent();
		m_StudentList.pop_back();
		cout << "���� �Ϸ�" << endl;
	}
}
void StudentManager::ClearStudent()
{
	m_StudentList.clear();
}

StudentManager::~StudentManager()
{
}
