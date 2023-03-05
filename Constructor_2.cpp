#include<iostream>
using namespace std;

class Point
{
private:
	int m_ipx, m_ipy;
public:
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
	Point pt(10,20); //변수를 함수처럼 쓴다.
	//Point pt2; //강제로 초기값을 받아야 한다.

	//신경쓸 거 줄이는 거
	//pt.getPx(5.5);처럼 맴버 함수 신경써야 하는 경우 없앰
	cout << "pt -> x : " << pt.getPx() << ", y: " << pt.getPy() << endl;
}