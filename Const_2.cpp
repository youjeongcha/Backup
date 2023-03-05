#include<iostream>
using namespace std;

class Point
{
private:
	int m_ix; //const 선언시 사용하면 쓰레기값.  이를 해결하는 건 다음 진도에
	int m_iy;
public:
	Point() {} //신경 x
	void SetNum(int x, int y)
	{
		m_ix = x;
		m_iy = y;
	}
	void ShowNum()//const //해당 함수의 종속문장
	{
		cout << "x = " << m_ix << endl;
		cout << "y = " << m_iy << endl;
		m_ix = 30;
		m_iy = 40;
		cout << "x = " << m_ix << endl << endl;
	}
	const int* GetNum() const //반환자료형에서 리턴 받는 거에서 const 3
		//앞뒤로 붙이면 리턴 받는 것도 const 종속문장 안에서도 const 불가
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