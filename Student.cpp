#include "Student.h"

void Student::SetStudent(int number)
{
	int tmp;
	bool state = true;
	m_iNumber = number;

	cout << m_iNumber << "�� �л� ����\n";
	cout << "�̸� : ";
	cin >> m_strName;
	cout << "���� : ";
	cin >> m_iAge;

	while (state)
	{
		cout << "�г� : ";
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
			cout << "�߸� �Է��ϼ̽��ϴ�.(1~3)\n";
			break;
		}
	}
	state = true;

	while (state)
	{
		cout << "����(���� 0, ���� 1) : ";
		cin >> tmp;
		m_eGender = (GENDER)tmp;
		switch (m_eGender)
		{
		case GENDER_MAN:
		case GENDER_WOMAN:
			state = false;
			break;
		default:
			cout << "�߸� �Է��ϼ̽��ϴ�.(0,1)\n";
			break;
		}
	}
}

void Student::ShowStudent()
{
	cout << "    ====" << m_iNumber << "�� �л�====\n";
	cout << "    �̸� : " << m_strName << "\n";
	cout << "    ���� : " << m_iAge << "\n";
	cout << "    ���� : ";
	switch (m_eGender)
	{
	case GENDER_MAN:
		cout << "����\n";
		break;
	case GENDER_WOMAN:
		cout << "����\n";
		break;
	}
	cout << "    �г� : " << (int)m_eClass << "\n\n";
}