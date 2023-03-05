#include "StudentManager.h"

void StudentManager::Menu()
{
	Student student;
	int select;
	string strTmp;
	int iTmp;

	while (true)
	{
		cout << "======학생관리 프로그램======\n";
		cout << "      1.학생 등록\n";
		cout << "      2.학생 목록<번호순>\n";
		cout << "      3.학생 목록<학년순>\n";
		cout << "      4.학생 검색\n";
		cout << "      5.학년 검색\n";
		cout << "      6.마지막 학생 삭제\n";
		cout << "      7.학생 전체 삭제\n";
		cout << "      8.종료\n";
		cout << "    (학생 수 : " << m_StudentList.size() << ")\n";
		cout << "입력 : ";
		cin >> select;
		system("cls");

		switch (select)
		{
		case 1://학생 등록
			AddStudent();
			break;
		case 2://학생 목록<번호순>
			ShowStudentList_Num();
			break;
		case 3://학생 목록<학년순>
			ShowStudentList_Class();
			break;
		case 4://학생 검색
			cout << "이름 입력 : ";
			cin >> strTmp;
			if (FindStudentName(strTmp) == false)
				cout << "해당 학생이 없습니다.\n";
			break;
		case 5://학년 검색
			cout << "학년 입력 : ";
			cin >> iTmp;
			if (ShowStudentList_Class_Part(iTmp, false) == false)
				cout << "해당 학생이 없습니다.\n";
			break;
		case 6://마지막 학생 삭제
			m_StudentList.back().ShowStudent();
			m_StudentList.pop_back();
			cout << "삭제 완료\n";
			break;
		case 7://학생 전체 삭제
			m_StudentList.clear();
			break;
		case 8://종료
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
		cout << "더이상 학생을 등록할 수 없습니다.\n";
}

void StudentManager::ShowStudentList_Num()
{
	for (list<Student>::iterator iter = m_StudentList.begin(); iter != m_StudentList.end(); iter++)
		iter->ShowStudent();
}

bool StudentManager::ShowStudentList_Class_Part(int searchClass, bool Flag)
{
	int iClass;

	cout << "┌──────" << searchClass << " 학년──────┐\n";
	for (list<Student>::iterator iter = m_StudentList.begin(); iter != m_StudentList.end(); iter++)
	{
		iClass = (int)(iter->GetClass()); //
		if (iClass == searchClass) ///
		{
			iter->ShowStudent();
			Flag = true;
		}
	}
	cout << "└───────────────┘\n";

	return Flag;
}

void StudentManager::ShowStudentList_Class()
{
	bool Flag = false;

	for (int searchClass = CLASS_START; searchClass < CLASS_END; searchClass++)
	{
		Flag = ShowStudentList_Class_Part(searchClass, Flag);
		if (Flag == false)
			cout << searchClass << "학년 학생이 없습니다.\n";
	}
}

bool StudentManager::FindStudentName(string strName)
{//동명이인 처리
	bool Flag = false;

	for (list<Student>::iterator iter = m_StudentList.begin(); iter != m_StudentList.end(); iter++)
	{
		if (iter->GetName() == strName)
		{
			iter->ShowStudent();
			Flag = true; //return true;
		}
	}

	return Flag; //return false;로 처리하는 것도 가능
}