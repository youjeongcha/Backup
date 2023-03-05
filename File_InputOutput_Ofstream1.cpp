#include<iostream>
#include<fstream>
using namespace std;

void main()
{
	ofstream save;//파일이 없다면 만들어줄것.
	//save.open("test.txt");//덮어쓰기 //c언어의 fopen과 동일한 역할
	save.open("test.txt", ios::app);//추가모드
	if (save.is_open())//true면 제대로 열린것. false면 안 열린거라 닫을 필요도 없다.
	{
		save << "이건 파일 입출력 추가모드입니다.";
		save.close();
	}
}