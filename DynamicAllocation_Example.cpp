#include<iostream>
#include<string>
#include<Windows.h>
#include<vector>
using namespace std;

#define STUDENTMAX 50

void main()
{
	int Select;
	vector<string*> ptrStringList; //�����Ҵ絵 �ڷ��� ���� //string�� �ּҰ��� vector�� �ּҸ� ���� ����
	string* studentTmp;
	while (1)
	{
		system("cls");
		cout << "===�л���������===(�л��� : " << ptrStringList.size() << "��)" << endl;
		cout << "   1.�л����" << endl;
		cout << "   2.�л����� ����" << endl;
		cout << "   3.����" << endl;
		cout << " �Է� : " << endl;
		cin >> Select;
		switch (Select)
		{
		case 1:
			if (ptrStringList.size() < STUDENTMAX)
			{
				studentTmp = new string; //�����Ҵ� �ּ� ����
				cout << ptrStringList.size() + 1 << "�� �л� �̸� : ";
				cin >> *studentTmp; //�� �ޱ�
				ptrStringList.push_back(studentTmp);
			}
			break;
		case 2:
			for (int i = 0; i < ptrStringList.size(); i++)
				cout << i + 1 << "�� �л� : " << *(ptrStringList[i]) << endl; //*ptrStringList[i] 
																		 //ptrStringList[i]�� �ּҸ� ���� �迭
																		//*�� �ٿ��� ���� ����Ų��
			system("pause");
			break;
		case 3:
			for (int i = 0; i < ptrStringList.size(); i++)
			{
				cout << *ptrStringList[i] << "�л�" << endl;
				delete ptrStringList[i];
				cout << "�Ҵ� ���� �Ϸ�" << endl;
			}
			ptrStringList.clear(); //clear()�ϴ� ���� ��� ����ϸ� clear
			system("pause");
			return;
		}
	}
}


