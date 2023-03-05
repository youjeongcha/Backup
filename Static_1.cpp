#include <iostream>
using namespace std;

void counter()
{
	static int count = 0; //static이 없으면 호출할때마다 다 1로 뜬다
	//static은 프로그램이 실행될 때 만들어지는 //프로그램이 사라질때까지 유지
	//하지만 다른 지역에서는 하용하지 못함
	cout << ++count << endl;
}

void main()
{
	for (int i = 0; i < 10; i++)
		counter();
	//count = 20; //하지만 다른 지역에서는 하용하지 못함 <<<<
}