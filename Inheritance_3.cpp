#include <iostream>
using namespace std;

class A
{
private:
	int m_iprivate;
protected:
	int m_iprotected;
public:
	int m_ipublic;
	void Test()
	{
		m_iprivate = 10;
		m_iprotected = 10;
		m_ipublic = 10;
	}
};

class B : public A
{
	void Test()
	{
		m_iprivate = 10;
		m_iprotected = 10;
		m_ipublic = 10;
	}
};

class C : public B
{
	void Test()
	{
		m_iprivate = 10;
		m_iprotected = 10;
		m_ipublic = 10;
	}
};

void main()
{
	B b;
	b.m_iprivate = 10;
	b.m_iprotected = 10;
	b.m_ipublic = 10;
}