#include<iostream>
using namespace std;
//���� ������ �Է¹޾ƾ� �ϴ� ��Ȳ �ذ�
//->������ �����ε�

class Point
{
private:
	int m_ipx, m_ipy;
public:
	Point()
	{//�⺻ ������. default Constructor
		m_ipx = 5;
		m_ipy = 5;
	}
	Point(int x, int y)
	{
		m_ipx = x;
		m_ipy = y;
	}
	int getPx() { return m_ipx; }
	int getPy() { return m_ipy; }
};

void main()
{
	Point pt1, pt2(10, 20); //������ �����ε�
	cout << "pt1 -> x : " << pt1.getPx() << ", y : " << pt1.getPy() << endl;
	cout << "pt2 -> x : " << pt2.getPx() << ", y : " << pt2.getPy() << endl;
}