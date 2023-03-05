#include<iostream>
#include<string>
using namespace std;

class person
{
private:
	int m_iAge;
	string m_strName;
public:
	person(int _age, string tmp)
	{
		m_iAge = _age;
		m_strName = tmp;
	}
	person(const person* tmp)
	{
		m_iAge = tmp->m_iAge;
		m_strName = tmp->m_strName;
	}
	void print()
	{
		cout << "나이 : " << m_iAge << endl;
		cout << "이름 : " << m_strName << endl;
	}
};

void main()
{
	person p1(26, "최정호");
	//person* p2 = &p1; //얕은복사
	person p2(&p1);//깊은복사
	p1.print();
	p2.print();
}