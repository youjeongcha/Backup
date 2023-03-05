#pragma once //중복 막아주는 역할
//쌍방 바라보는 include 못막아준다 //#include"StudentManager.h"
#include<list>
#include"Student.h" //중복 include 주의
//"" 프로젝트 경로 기준
//<> 비주얼스튜디오 설치 경로 기준

#define STUDENT_MAX 10

class StudentManager
{
private:
	list<Student> m_StudentList;
public:
	void Main();
	void AddStudent();
	void ShowStudentList();
	inline int GetStudentCount()
	{
		return m_StudentList.size();
	}
	bool FindStudentName(string Name);
	StudentManager(); //생성자
	~StudentManager(); //소멸자
};

