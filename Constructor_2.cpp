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
	Point pt(10,20); //������ �Լ�ó�� ����.
	//Point pt2; //������ �ʱⰪ�� �޾ƾ� �Ѵ�.

	//�Ű澵 �� ���̴� ��
	//pt.getPx(5.5);ó�� �ɹ� �Լ� �Ű��� �ϴ� ��� ����
	cout << "pt -> x : " << pt.getPx() << ", y: " << pt.getPy() << endl;
}