#include<iostream>
#include<string>
using namespace std;

void main()
{
	string str = " Education is the vest provision for old age.\n - Aristotle";
	int index = str.find("provision"); //.find �� ������ �� ���� �ε��� ��ȣ �����´�
	cout << "Find Provision = " << index << endl;
	cout << str[index] << endl;
	cout << str.substr(index, sizeof("provision")); //substr ��  .subtr(a,b) a���� b��ŭ �����´�
	return;
	//��ã�� ��� string::npos ��ȯ
}