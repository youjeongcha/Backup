#include<iostream>
using namespace std;

class Con
{
public:
	Con()
	{
		cout << "생성자 호출" << endl;
	}
};

void main()
{
	Con c;
}