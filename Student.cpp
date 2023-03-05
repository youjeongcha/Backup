#include "Student.h"



Student::Student()
{
}


void Student::SetStudent(int Number)
{
	int Tmp;
	bool State = true;
	m_iNumber = Number;
	cout << Number << "번 학생 정보" << endl;
	cout << "이름 : ";
	cin >> m_strName;
	cout << "나이 : ";
	cin >> m_iAge;
	State = true;
	while (State)
	{
		cout << "학년 : ";
		cin >> Tmp;
		m_eClass = (CLASS)Tmp;
		switch (m_eClass)
		{
		case CLASS_1:
		case CLASS_2:
		case CLASS_3:
			State = false;
			break;
		default:
			cout << "잘못 입력하셧습니다.(1~3)" << endl;
			break;
		}
	}
	State = true;
	while (State)
	{
		cout << "성별(남자 0,여자 1) : ";
		cin >> Tmp;
		m_eGender = (GENDER)Tmp;
		switch (m_eGender)
		{
		case GENDER_MAN:
		case GENDER_WOMAN:
			State = false;
			break;
		default:
			cout << "잘못 입력하셧습니다.(0,1)" << endl;
			break;
		}
	}
}
void Student::ShowStudent()
{
	cout << "    ====" << m_iNumber << "번 학생====" << endl;
	cout << "    이름 : " << m_strName << endl;
	cout << "    나이 : " << m_iAge << endl;
	cout << "    성별 : ";
	switch (m_eGender)
	{
	case GENDER_MAN:
		cout << "남자" << endl;
		break;
	case GENDER_WOMAN:
		cout << "여자" << endl;
		break;
	}
	cout << "    학년 : " << (int)m_eClass << endl << endl;
}

Student::~Student()
{
}
