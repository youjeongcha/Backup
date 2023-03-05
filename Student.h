#pragma once
#include<iostream>
#include<string>
using namespace std;

enum GENDER
{
	GENDER_MAN,
	GENDER_WOMAN
};

enum CLASS
{
	CLASS_START = 1,
	CLASS_1 = 1,
	CLASS_2,
	CLASS_3,
	CLASS_END
};

class Student
{
private:
	string m_strName;	
	int m_iAge;
	GENDER m_eGender;
	CLASS m_eClass;
	int m_iNumber;
public:
	void SetStudent(int Number);
	void ShowStudent();
	inline string GetName()
	{
		return m_strName;
	}
	inline CLASS GetClass()
	{
		return m_eClass;
	}
	Student();
	~Student();
};

