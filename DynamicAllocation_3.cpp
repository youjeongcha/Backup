#include <iostream>
#include <string>
using namespace std;

void main()
{
	int size;
	string* student;
	cout << "����� �л����� �Է��Ͻÿ�\n";
	cin >> size;
	student = new string[size];

	for (int i = 0; i < size;i++)
	{
		cout << i + 1 << "�� �л� �̸� ��� : ";
		cin >> student[i];
	}
	cout << endl << endl << endl;
	for (int i = 0; i < size;i++)
	{
		cout << i + 1 << "�� �л� : ";
		cout << student[i] << endl;
	}
	delete[]student;
}