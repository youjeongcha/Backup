#include<iostream>
#include<fstream>
#include<string>
using namespace std;
//���⸦ ������ �´ٴ� �� ���ڿ��ۿ� ���ٴ� ��

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
		getline(load, str);
		cout << str << endl;
	}
}

/*
[[[[[[[[[[[[r�ɼ�]]]]]]]]]]]]]]]]]]]]

>fscanf ���� �Ǵ� ���ʹ����� ���� ������

>fgets ���ʹ����� ���� ������
//char buf[]������� ���԰���
fgets(buf, sizeof(buf), f); //������, ���� ũ��. ��� ��� �ðǰ�.

>fread ���� ��ü�� ������
*/