#include<iostream>
#include<string>
using namespace std;

void main()
{
	string str = " Education is the vest provision for old age.\n - Aristotle";
	int index = str.find("provision"); //.find 는 같으면 맨 앞의 인덱스 번호 가져온다
	cout << "Find Provision = " << index << endl;
	cout << str[index] << endl;
	cout << str.substr(index, sizeof("provision")); //substr 는  .subtr(a,b) a부터 b만큼 가져온다
	return;
	//못찾을 경우 string::npos 반환
}