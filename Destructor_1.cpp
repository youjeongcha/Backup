#include<iostream>
using namespace std;
//�Ҹ���

class Con
{
public:
	Con()
	{
		cout << "������ ȣ��" << endl;
	}
	~Con()
	{
		cout << "�Ҹ��� ȣ��" << endl;
	}
};
void main()
{
	Con c; //������ ȣ��
	cout << "Hello" << endl;
	c.~Con();//ȣ���ߴ��ؼ� �޸� ����x
}