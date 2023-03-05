#include "Student.h"

void Student::SetStudent(int number)
{
	int tmp;
	bool state = true;
	m_iNumber = number;

	cout << m_iNumber << "번 학생 정보\n";
	cout << "이름 : ";
	cin >> m_strName;
	cout << "나이 : ";
	cin >> m_iAge;

	while (state)
	{
		cout << "학년 : ";
		cin >> tmp;
		m_eClass = (CLASS)tmp;
		switch (m_eClass)
		{
		case CLASS_1:
		case CLASS_2:
		case CLASS_3:
			state = false;
			break;
		default:
			cout << "잘못 입력하셨습니다.(1~3)\n";
			break;
		}
	}
	state = true;

	while (state)
	{
		cout << "성별(남자 0, 여자 1) : ";
		cin >> tmp;
		m_eGender = (GENDER)tmp;
		switch (m_eGender)
		{
		case GENDER_MAN:
		case GENDER_WOMAN:
			state = false;
			break;
		default:
			cout << "잘못 입력하셨습니다.(0,1)\n";
			break;
		}
	}
}

void Student::ShowStudent()
{
	cout << "    ====" << m_iNumber << "번 학생====\n";
	cout << "    이름 : " << m_strName << "\n";
	cout << "    나이 : " << m_iAge << "\n";
	cout << "    성별 : ";
	switch (m_eGender)
	{
	case GENDER_MAN:
		cout << "남자\n";
		break;
	case GENDER_WOMAN:
		cout << "여자\n";
		break;
	}
	cout << "    학년 : " << (int)m_eClass << "\n\n";
}