#include "StudentManager.h"

void StudentManager::Menu()
{
	Student student;
	int select;
	string strTmp;
	int iTmp;

	while (true)
	{
		cout << "======�л����� ���α׷�======\n";
		cout << "      1.�л� ���\n";
		cout << "      2.�л� ���<��ȣ��>\n";
		cout << "      3.�л� ���<�г��>\n";
		cout << "      4.�л� �˻�\n";
		cout << "      5.�г� �˻�\n";
		cout << "      6.������ �л� ����\n";
		cout << "      7.�л� ��ü ����\n";
		cout << "      8.����\n";
		cout << "    (�л� �� : " << m_StudentList.size() << ")\n";
		cout << "�Է� : ";
		cin >> select;
		system("cls");

		switch (select)
		{
		case 1://�л� ���
			AddStudent();
			break;
		case 2://�л� ���<��ȣ��>
			ShowStudentList_Num();
			break;
		case 3://�л� ���<�г��>
			ShowStudentList_Class();
			break;
		case 4://�л� �˻�
			cout << "�̸� �Է� : ";
			cin >> strTmp;
			if (FindStudentName(strTmp) == false)
				cout << "�ش� �л��� �����ϴ�.\n";
			break;
		case 5://�г� �˻�
			cout << "�г� �Է� : ";
			cin >> iTmp;
			if (ShowStudentList_Class_Part(iTmp, false) == false)
				cout << "�ش� �л��� �����ϴ�.\n";
			break;
		case 6://������ �л� ����
			m_StudentList.back().ShowStudent();
			m_StudentList.pop_back();
			cout << "���� �Ϸ�\n";
			break;
		case 7://�л� ��ü ����
			m_StudentList.clear();
			break;
		case 8://����
			m_StudentList.clear();
			return;
		}
		system("pause");
		system("cls");
	}
}

void StudentManager::AddStudent()
{
	Student student;

	if (m_StudentList.size() < STUDENT_MAX)
	{
		student.SetStudent(m_StudentList.size() + 1);
		m_StudentList.push_back(student);
	}
	else
		cout << "���̻� �л��� ����� �� �����ϴ�.\n";
}

void StudentManager::ShowStudentList_Num()
{
	for (list<Student>::iterator iter = m_StudentList.begin(); iter != m_StudentList.end(); iter++)
		iter->ShowStudent();
}

bool StudentManager::ShowStudentList_Class_Part(int searchClass, bool Flag)
{
	int iClass;

	cout << "��������������" << searchClass << " �г⦡������������\n";
	for (list<Student>::iterator iter = m_StudentList.begin(); iter != m_StudentList.end(); iter++)
	{
		iClass = (int)(iter->GetClass()); //
		if (iClass == searchClass) ///
		{
			iter->ShowStudent();
			Flag = true;
		}
	}
	cout << "����������������������������������\n";

	return Flag;
}

void StudentManager::ShowStudentList_Class()
{
	bool Flag = false;

	for (int searchClass = CLASS_START; searchClass < CLASS_END; searchClass++)
	{
		Flag = ShowStudentList_Class_Part(searchClass, Flag);
		if (Flag == false)
			cout << searchClass << "�г� �л��� �����ϴ�.\n";
	}
}

bool StudentManager::FindStudentName(string strName)
{//�������� ó��
	bool Flag = false;

	for (list<Student>::iterator iter = m_StudentList.begin(); iter != m_StudentList.end(); iter++)
	{
		if (iter->GetName() == strName)
		{
			iter->ShowStudent();
			Flag = true; //return true;
		}
	}

	return Flag; //return false;�� ó���ϴ� �͵� ����
}