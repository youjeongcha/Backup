#include<iostream>
using namespace std;

class Point
{
private:
	int m_ix; //const ����� ����ϸ� �����Ⱚ.  �̸� �ذ��ϴ� �� ���� ������
	int m_iy;
public:
	Point() {} //�Ű� x
	void SetNum(int x, int y)
	{
		m_ix = x;
		m_iy = y;
	}
	void ShowNum()//const //�ش� �Լ��� ���ӹ���
	{
		cout << "x = " << m_ix << endl;
		cout << "y = " << m_iy << endl;
		m_ix = 30;
		m_iy = 40;
		cout << "x = " << m_ix << endl << endl;
	}
	const int* GetNum() const //��ȯ�ڷ������� ���� �޴� �ſ��� const 3
		//�յڷ� ���̸� ���� �޴� �͵� const ���ӹ��� �ȿ����� const �Ұ�
	{
		return &m_ix;
	}
};

void main()
{
	Point p;
	p.SetNum(10, 20);
	p.ShowNum();
	*(p.GetNum()) = 100; //3
	p.ShowNum();
}