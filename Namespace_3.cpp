#include <iostream>
#include <string>
using namespace std;

//��������
string str = "Global Variavle\n";

namespace Nsp
{
	string str = "Namespace Variavle\n";
}

void main()
{
	//����
	string str = "Local Variable\n";
	//���� ���� �ȿ��� ������ ������ �ִ��� > ����� ������ �� �켱
	cout << str;//����
	cout << Nsp::str;
	cout << ::str; //����
}