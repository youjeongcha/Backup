#include<iostream>
using namespace std;

class GuGuDan
{
private:
	int StartGuGuDan;
	int EndGuGuDan;
public:
	void SetGuGuDan()
	{
		while (1)
		{
			cout << "���� �� �Է� : ";
			cin >> StartGuGuDan;
			cout << "�� �� �Է� : ";
			cin >> EndGuGuDan;
			if (StartGuGuDan < 2 || StartGuGuDan > 9) //if�� ó���ϴ� �ʵ� ����
				cout << "���� ���� 2���� �۰ų� 9���� Ů�ϴ�." << endl;
			else if (EndGuGuDan < 2 || EndGuGuDan > 9)
				cout << "�� ���� 2���� �۰ų� 9���� Ů�ϴ�." << endl;
			else if (StartGuGuDan > EndGuGuDan)
				cout << "���� ���� �� �ܺ��� Ů�ϴ�." << endl;
			else
				break;
			system("pause");
		}
	}
	void ShowGuGuDan()
	{
		for (int j = 0; j <= 9; j++)
		{
			for (int i = StartGuGuDan; i <= EndGuGuDan; i++)
			{//���η� 2��*1 3��*1 4��*1 ������ ���� ����ϰ� *9���� ������� ���
				if (j == 0) //j�� �����ϱ� ���� ���� ���� ��� ó�� //����
					cout << "=======" << i << "��=======\t";
				else
					cout << "    " << i << " x " << j << " = " << i * j << "\t\t";
			}
			cout << endl;
		}
	}
};

void main()
{
	GuGuDan Gu1;
	Gu1.SetGuGuDan();
	Gu1.ShowGuGuDan();
}