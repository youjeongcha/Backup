#include "circle.h"

circle::circle()
{
}

void circle::Draw()
{
	cout << fixed << setprecision(4) << "반지름 : " << pi << " 인 원형을 그렸습니다." << endl;
}

void circle::SetSize()
{
	cout << "반지름 : ";
	cin >> pi;
}

circle::~circle()
{
}