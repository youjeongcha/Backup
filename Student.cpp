#include "Student.h" //".h"



Student::Student()
{
}


void Student::SetStudent(int Number)
{
	int Tmp;
	bool State = true;
	m_iNumber = Number; //Number�� m_iNumber�� �ٽ� �޾Ƽ� ���?
	cout << m_iNumber << "�� �л� ����" << endl;
	cout << "�̸� : ";
	cin >> m_strName;
	cout << "���� : ";
	cin >> m_iAge;
	//State = true;
	while (State)
	{
		cout << "�г� : ";
		cin >> Tmp;
		m_eClass = (CLASS)Tmp; //enum�� int�� ��� ���� //int�� enum ��� �Ұ� ����ȯ �ʿ�
		switch (m_eClass)
		{
		case CLASS_1:
		case CLASS_2:
		case CLASS_3:
			State = false;
			break;
		default:
			cout << "�߸� �Է��ϼ˽��ϴ�.(1~3)" << endl;
			break;
		}
	}
	State = true;
	while (State)
	{
		cout << "����(���� 0,���� 1) : ";
		cin >> Tmp;
		m_eGender = (GENDER)Tmp;
		switch (m_eGender)
		{
		case GENDER_MAN:
		case GENDER_WOMAN:
			State = false;
			break;
		default:
			cout << "�߸� �Է��ϼ˽��ϴ�.(0,1)" << endl;
			break;
		}
	}
}
void Student::ShowStudent()
{
	cout << "====" << m_iNumber << "�� �л�====" << endl;
	cout << "�̸� : " << m_strName << endl;
	cout << "���� : " << m_iAge << endl;
	cout << "���� : ";
	switch (m_eGender)
	{
	case GENDER_MAN:
		cout << "����" << endl;
		break;
	case GENDER_WOMAN:
		cout << "����" << endl;
		break;
	}
	cout << "�г� : " << (int)m_eClass << endl << endl; //(int)�ƴϾ ��� �����ѵ�
	//enum class GENDER�� ���� �Ұ�. (int)�ʼ��� ���־�� �Ѵ�.
}

Student::~Student() //?
{
}