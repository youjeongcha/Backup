#pragma once
#include"Student.h"
#include<list>

#define STUDENT_MAX 10

class StudentManager
{
private:
	list<Student> m_StudentList;
public:

	void MainMenu();

	void AddStudent();
	void ShowStudentList();
	inline int GetStudentCount()
	{
		return m_StudentList.size();
	}
	bool FindStudentName(string Name);
	bool ShowStudentClass(CLASS Class);
	void DeleteStudent();
	void ClearStudent();
	StudentManager();
	~StudentManager();
};

