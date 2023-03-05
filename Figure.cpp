#include "Figure.h"


Figure::Figure()
{
}

void Figure::Draw()
{
	cout << "가로 : " << x << " 세로 : " << y << " 인 도형을 그렸습니다." << endl;
	return;
}

void Figure::SetSize()
{
	cout << "가로 : ";
	cin >> x;
	cout << "세로 : ";
	cin >> y;
}

Figure::~Figure()
{

}