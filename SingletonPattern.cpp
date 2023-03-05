#include<iostream>
#include<string>
#define max_len 100
using namespace std;

class Student
{
private:
	string name;
	int kor, eng, math, sum;
	float avg;
	int num;
	char Class;
public:
	Student() { num = 0; }
	~Student() {}
	void SetStudent(int _num);
	void showStudent();
	int getnum()
	{
		return num;
	}
	string getname()
	{
		return name;
	}
	char getClass()
	{
		return Class;
	}
};

void Student::SetStudent(int _num)
{
	cout << "이름을 입력 하시오 : ";
	cin >> name;
	cout << "3과목의 점수를 입력하시오" << endl;
	cout << "국어 : ";
	cin >> kor;
	cout << "영어 : ";
	cin >> eng;
	cout << "수학 : ";
	cin >> math;
	sum = kor + eng + math;
	avg = (float)sum / 3;
	num = _num;
	if (avg >= 90)
		Class = 'A';
	else if (avg >= 80)
		Class = 'B';
	else if (avg >= 70)
		Class = 'C';
	else if (avg >= 60)
		Class = 'D';
	else
		Class = 'F';
	return;
}

void Student::showStudent()
{
	cout << "----------------------" << endl;
	cout << num << "번 학생" << endl;
	cout << "이름 : " << name << endl;
	cout << "국어 점수 : " << kor << endl << "수학 점수 : " << math << endl << "영어 점수 : " << eng << endl;
	cout << "합계 점수 : " << sum << "\t 평균점수 : " << avg << endl;
	cout << "등급 : [ " << Class << "]" << endl << endl;
	return;
}

class Std_manager {
	Student* std[30];
public:
	~Std_manager() //소멸자 public에
	{
		for (int i = 0; i < 30; i++)
		{
			delete std[i];
		}
	}
	static Std_manager* Get_Instance()
	{
		if (NULL == m_pInstance)
			m_pInstance = new Std_manager;
		return m_pInstance;
	}

	//gameManeager 같은 경우에는 보통 코드의 맨 끝 줄에 쓰거나 안 써도 괜찮지만. 다만 쓰다가 메모리 낭비를 위해 삭제할 class에는 필요하다.
	void Destroy()
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}

	void display();

private:
	static Std_manager* m_pInstance; //static 함수에 사용하려면 static으로 선언.
	Std_manager(); //생성자 privte에 멋대로 생성하지 못하게

	void setStudent();
	void showStudent();
	void findNumber();
	void findname();
	void findClass();
};

//static 멤버 변수는 모든 객체가 공유. 프로그램 전체 영역에서 메모리 유지가 되어야 한다. 반드시 전역 범위에서 정의 및 초기화.
Std_manager* Std_manager::m_pInstance = NULL; //NULL 하는게 초기화. 앞에가 선언.

Std_manager::Std_manager()
{
	for (int i = 0; i < 30; i++)
		std[i] = new Student;
}

void Std_manager::display() {
	int sel;
	while (true)
	{
		cout << "=========================" << endl;
		cout << "   1.학생 등록" << endl;
		cout << "   2.전체 학생정보 출력" << endl;
		cout << "   3.학생 번호 검색" << endl;
		cout << "   4.학생 이름 검색" << endl;
		cout << "   5.등급별 출력" << endl;
		cout << "   0.종료" << endl;
		cout << "=========================" << endl;
		cin >> sel;
		switch (sel) {
		case 1:
			setStudent();
			break;
		case 2:
			showStudent();
			break;
		case 3:
			findNumber();
			break;
		case 4:
			findname();
			break;
		case 5:
			findClass();
			break;
		case 0:return;
		default:cout << "잘못 입력 " << endl;
		}
		system("pause"); system("cls");
	}
}

void Std_manager::setStudent()
{
	for (int i = 0; i < 30; i++)
	{
		if (std[i]->getnum() == 0)
		{
			std[i]->SetStudent(i + 1);
			return;
		}
	}
	cout << "학생이 전원 등록 되었습니다." << endl;
}

void Std_manager::showStudent()
{
	for (int i = 0; i < 30; i++)
	{
		if (std[i]->getnum() != 0)
		{
			std[i]->showStudent();
		}
		else
			return;
	}
}

void Std_manager::findNumber()
{
	int _find;
	cout << "찾을 학생의번호를 입력 하시오";
	cin >> _find;
	for (int i = 0; i < 30; i++)
	{
		if (std[i]->getnum() == _find)
		{
			std[i]->showStudent();
			return;
		}
	}
	cout << endl << "해당 번호의 학생이 없습니다." << endl;
}

void Std_manager::findname()
{
	string _find;
	int find_num = 0;
	cout << "찾을 학생의이름을 입력 하시오";
	cin >> _find;
	for (int i = 0; i < 30; i++)
	{
		if (std[i]->getname() == _find)
		{
			std[i]->showStudent();
			find_num++;
		}
	}
	if (find_num == 0)
		cout << "해당 이름의 학생이 없습니다." << endl;
}

void Std_manager::findClass()
{
	int _find = 0;
	cout << "========= [ A ] =========" << endl;
	for (int i = 0; i < 30; i++)
	{
		if (std[i]->getClass() == 'A')
		{
			std[i]->showStudent();
			_find++;
		}
	}
	cout << "총 " << _find << "명" << endl;
	cout << "=========================" << endl << endl << endl;
	_find = 0;
	cout << "========= [ B ] =========" << endl;
	for (int i = 0; i < 30; i++)
	{
		if (std[i]->getClass() == 'B')
		{
			std[i]->showStudent();
			_find++;
		}
	}
	cout << "총 " << _find << "명" << endl;
	cout << "=========================" << endl;
	_find = 0;
	cout << "========= [ C ] =========" << endl;
	for (int i = 0; i < 30; i++)
	{
		if (std[i]->getClass() == 'C')
		{
			std[i]->showStudent();
			_find++;
		}
	}
	cout << "총 " << _find << "명" << endl;
	cout << "=========================" << endl;
	_find = 0;
	cout << "========= [ D ] =========" << endl;
	for (int i = 0; i < 30; i++)
	{
		if (std[i]->getClass() == 'D')
		{
			std[i]->showStudent();
			_find++;
		}
	}
	cout << "총 " << _find << "명" << endl;
	cout << "=========================" << endl;
	_find = 0;
	cout << "========= [ F ] =========" << endl;
	for (int i = 0; i < 30; i++)
	{
		if (std[i]->getClass() == 'F')
		{
			std[i]->showStudent();
			_find++;
		}
	}
	cout << "총 " << _find << "명" << endl;
	cout << "=========================" << endl;

}

#define stdMgr Std_manager::Get_Instance()

void main() {
	//Std_manager Std_Manager;
	//Std_Manager.display();
	//static 선언으로 프로그램 시작부터 메모리 존재.(객체 생성 전에도 메모리 존재)
	stdMgr->display();
}
