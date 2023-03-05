#pragma once //�ߺ� �����ִ� ����
//�ֹ� �ٶ󺸴� include �������ش� //#include"StudentManager.h"
#include<list>
#include"Student.h" //�ߺ� include ����
//"" ������Ʈ ��� ����
//<> ���־�Ʃ��� ��ġ ��� ����

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
	StudentManager(); //������
	~StudentManager(); //�Ҹ���
};

