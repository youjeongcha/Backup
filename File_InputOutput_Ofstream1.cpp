#include<iostream>
#include<fstream>
using namespace std;

void main()
{
	ofstream save;//������ ���ٸ� ������ٰ�.
	//save.open("test.txt");//����� //c����� fopen�� ������ ����
	save.open("test.txt", ios::app);//�߰����
	if (save.is_open())//true�� ����� ������. false�� �� �����Ŷ� ���� �ʿ䵵 ����.
	{
		save << "�̰� ���� ����� �߰�����Դϴ�.";
		save.close();
	}
}