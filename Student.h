#pragma once
#include<iostream>
#include<string>
#include<Windows.h>
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
	CLASS m_eClass;
	GENDER m_eGender;
	int m_iNumber;
public:
	void SetStudent(int Number);
	void ShowStudent();
	string GetName()
	{
		return m_strName;
	}
	CLASS GetClass()
	{
		return m_eClass;
	}
};

