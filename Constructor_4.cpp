#include<iostream>
using namespace std;

class Point
{
private:
	int m_ipx, m_ipy;
public:
	Point(int x, int y)//무조건 초깃값받는거
	{
		m_ipx = x;
		m_ipy = y;
	}
	int getPx() { return m_ipx; }
	int getPy() { return m_ipy; }
};

void main()
{//배열로 쓸거면
	Point pt[3] = { Point(3,5),Point(20,40),Point(50,80) };
	for (int i = 0; i < 3; i++)
		cout << "pt[" << i << "]->x : " << pt[i].getPx() << ", y : " << pt[i].getPy() << endl;
}