#include <iostream>
#include <string>
using namespace std;

void main()
{
	int size;
	string* student;
	cout << "등록할 학생수를 입력하시오\n";
	cin >> size;
	student = new string[size];

	for (int i = 0; i < size;i++)
	{
		cout << i + 1 << "번 학생 이름 등록 : ";
		cin >> student[i];
	}
	cout << endl << endl << endl;
	for (int i = 0; i < size;i++)
	{
		cout << i + 1 << "번 학생 : ";
		cout << student[i] << endl;
	}
	delete[]student;
}