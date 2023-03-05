#include "Triangle.h"


Triangle::Triangle()
{
}

void Triangle::Draw()
{
	cout << "¹Øº¯ : " << x << " ³ôÀÌ : " << y << " ÀÎ »ï°¢ÇüÀ» ±×·È½À´Ï´Ù." << endl;
}

void Triangle::SetSize()
{
	cout << "¹Øº¯ : ";
	cin >> x;
	cout << "³ôÀÌ : ";
	cin >> y;
}

Triangle::~Triangle()
{
}