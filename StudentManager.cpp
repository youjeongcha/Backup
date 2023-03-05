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
		cout << "======학생관리 프로그램======" << endl;
		cout << "      1.학생 등록" << endl;
		cout << "      2.학생 목록" << endl;
		cout << "      3.학생 이름 검색" << endl;
		cout << "      4.종료" << endl;
		cout << "   (학생 수 : " << m_StudentList.size() << ")" << endl;
		cout << "입력 : ";
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
				cout << "이름 입력 : ";
			cin >> strTmp;
			if (FindStudentName(strTmp) == false)
				cout << "해당 학생이 없습니다." << endl;
			break;
		case 4:
			return;
		}
		system("pause");
	}
}

void StudentManager::AddStudent()
{
	Student student; //#include "StudentManager.h"에 선언 있음
	if (m_StudentList.size() < STUDENT_MAX)
	{
		student.SetStudent(m_StudentList.size() + 1);
		m_StudentList.push_back(student);
	}
	else
		cout << "더이상 학생을 등록할 수 없습니다." << endl;
}

void StudentManager::ShowStudentList()
{
	for (auto iter = m_StudentList.begin(); iter != m_StudentList.end(); iter++)
		iter->ShowStudent(); //맴버에 접근한다.
}

bool StudentManager::FindStudentName(string Name)
{//동명이인 처리
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
