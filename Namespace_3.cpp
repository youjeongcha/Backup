#include <iostream>
#include <string>
using namespace std;

//전역변수
string str = "Global Variavle\n";

namespace Nsp
{
	string str = "Namespace Variavle\n";
}

void main()
{
	//지역
	string str = "Local Variable\n";
	//같은 지역 안에서 동일한 변수가 있더라도 > 가까운 지역의 것 우선
	cout << str;//지역
	cout << Nsp::str;
	cout << ::str; //전역
}