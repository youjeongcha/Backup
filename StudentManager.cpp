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
		cout << "======학생관리 프로그램======" << endl;
		cout << "      1.학생 등록" << endl;
		cout << "      2.학생 목록<번호순>" << endl;
		cout << "      3.학생 목록<학년순>" << endl;
		cout << "      4.학생 검색" << endl;
		cout << "      5.학년 검색" << endl;
		cout << "      6.마지막 학생 삭제" << endl;
		cout << "      7.학생 전체 삭제" << endl;
		cout << "      8.종료" << endl;
		cout << "   (학생 수 : " << GetStudentCount() << ")" << endl;
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
			for (int i = CLASS_START; i < CLASS_END; i++)
			{
				bTmp = ShowStudentClass((CLASS)i);
				if (!bTmp)
					cout << i << "학년 학생이 없습니다." << endl;
			}
			break;
		case 4:
			cout << "이름 입력 : ";
			cin >> strTmp;
			bTmp = FindStudentName(strTmp);
			if (bTmp == false)
				cout << "해당 학생이 없습니다." << endl;
			break;
		case 5:
			cout << "학년 입력 : ";
			cin >> iTmp;
			bTmp = ShowStudentClass((CLASS)iTmp);
			if (!bTmp)
				cout << iTmp << "학년 학생이 없습니다." << endl;
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
		cout << "더이상 학생을 등록할 수 없습니다." << endl;
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
	cout << "┌─────" << (int)Class << " 학년─────┐" << endl;
	for (list<Student>::iterator iter = m_StudentList.begin(); iter != m_StudentList.end(); iter++)
	{
		if (iter->GetClass() == Class)
		{
			iter->ShowStudent();
			State = true;
		}
	}
	cout << "└─────────────┘" << endl;
	return State;
}


void StudentManager::DeleteStudent()
{
	if (m_StudentList.empty())
		cout << "삭제할 학생이 없습니다." << endl;
	else
	{
		m_StudentList.back().ShowStudent();
		m_StudentList.pop_back();
		cout << "삭제 완료" << endl;
	}
}
void StudentManager::ClearStudent()
{
	m_StudentList.clear();
}

StudentManager::~StudentManager()
{
}
