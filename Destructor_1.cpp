#include<iostream>
using namespace std;
//소멸자

class Con
{
public:
	Con()
	{
		cout << "생성자 호출" << endl;
	}
	~Con()
	{
		cout << "소멸자 호출" << endl;
	}
};
void main()
{
	Con c; //생성자 호출
	cout << "Hello" << endl;
	c.~Con();//호출했다해서 메모리 해제x
}