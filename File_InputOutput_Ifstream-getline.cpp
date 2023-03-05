#include<iostream>
#include<fstream>
#include<string>
using namespace std;
//띄어쓰기를 가지고 온다는 건 문자열밖에 없다는 것

void main()
{
	ofstream save;
	save.open("test.txt");
	if (save.is_open())
	{
		save << "이건 파일 입출력";
		save.close();
	}
	ifstream load;//left스트림은 띄워쓰기와 엔터 단위로 구분 fscanf처럼
	string str;
	string tmp;
	load.open("test.txt");
	while (!load.eof())//feof 파일 끝에 도착했는지 확인
	{
		getline(load, str);
		cout << str << endl;
	}
}

/*
[[[[[[[[[[[[r옵션]]]]]]]]]]]]]]]]]]]]

>fscanf 띄어쓰기 또는 엔터단위로 정보 가져옴

>fgets 엔터단위로 정보 가져옴
//char buf[]띄워쓰기 포함가능
fgets(buf, sizeof(buf), f); //변수명, 저장 크기. 어디서 들고 올건가.

>fread 정보 전체를 가져옴
*/