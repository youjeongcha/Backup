#include<iostream>
#include<fstream>
#include<string>
using namespace std;

void main()
{
	ofstream save;
	save.open("test.txt");
	if (save.is_open())
	{
		save << "�̰� ���� �����";
		save.close();
	}
	ifstream load;//left��Ʈ���� �������� ���� ������ ���� fscanfó��
	string str;
	string tmp;
	load.open("test.txt");
	while (!load.eof())//feof ���� ���� �����ߴ��� Ȯ��
	{
		load >> tmp;
		str += tmp;
		str += " ";
	}
	cout << str;
}

/*
[[[[[[[[[[[[r�ɼ�]]]]]]]]]]]]]]]]]]]]

>fscanf ���� �Ǵ� ���ʹ����� ���� ������

>fgets ���ʹ����� ���� ������
//char buf[]������� ���԰���
fgets(buf, sizeof(buf), f); //������, ���� ũ��. ��� ��� �ðǰ�.

>fread ���� ��ü�� ������
*/