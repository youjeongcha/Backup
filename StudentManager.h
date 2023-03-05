#pragma once
#include<list>
#include"Student.h"

#define STUDENT_MAX 10

class StudentManager
{
private:
	list<Student> m_StudentList;
public:
	void Menu();
	int GetStudentCsount()
	{//size
		return m_StudentList.size();
	}
	void AddStudent();
	void ShowStudentList_Num();
	bool ShowStudentList_Class_Part(int searchClass, bool Flag);
	void ShowStudentList_Class();
	bool FindStudentName(string strName);
};
