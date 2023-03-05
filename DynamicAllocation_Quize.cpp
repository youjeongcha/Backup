#include<iostream>
#include<string>
//#include<vector>
//�������� ���� ���ķ�
using namespace std;


//Q3
//�����Ҵ��ϸ� ���� ���ϴ� ��� �ݺ� �ϳ��ϳ� ������?
//>(�Է¹��� ��) �Ҵ�� ũ�⸦ �����صδ� ���ۿ� ����. �ּ��� ũ�⸸ ���´�.

void Print(string display, int* num, int input)
{
	cout << display;
	for (int i = 0; i < input; i++)
	{
		//cout << num + i << " "; //�ּ�
		//cout << *(num + i) << " "; //��
		cout << num[i] << " "; //��
	}
}

void Merge(int* num, int left, int mid, int right)
{
	int leftIndex = left, rightIndex = mid + 1;
	int index = 0;
	int* tmp;
	tmp = new int[right - left + 1];

	while (leftIndex <= mid && rightIndex <= right)
	{//�񱳴�� �� ���� ���������
		if (num[leftIndex] < num[rightIndex])
			tmp[index++] = num[leftIndex++];
		else
			tmp[index++] = num[rightIndex++];
	}
	while (leftIndex <= mid || rightIndex <= right)
	{//�񱳴���� �� �ʸ� ������
		if (leftIndex > mid) //left�� ���� ������
			tmp[index++] = num[rightIndex++];
		else//right�� ���� ������
			tmp[index++] = num[leftIndex++];
	}
	for (int i = 0; i < index; i++)
		num[left++] = tmp[i];
}


//Q1
//���� �Լ� ����Ҷ� ���� �ٷ� �ѱ��� �ʾҳ�
//�� �����Ҵ��� �ּҸ� �Ѱܼ� ���� ����? ����
//> �Լ� ȣ�⿡�� num�� �ּҸ� �޾Ƽ�, *num���� �ּҷ� �޴´�.
//---------  �߿�  ---------------
//>>int* a = &b �� �������� �� ������ ����a�� ����b�� �ּҸ� ������ ������ *a�� ���� b�� ���� ���� ����Ű�� ���Դϴ�. 
//int* a;
//a = &b; �� ���� ��
//-----------
//a�� �ּҸ� �����ϴ� ��.
//�ű⿡ *���� ���󰡴� ��.
//---------------------------------
//int a = 3;
//int* b = &a;
//���� ���󰡾� �ϴ� ���� >> byte ũ�⶧��?
//malloc(sizeof(int))�� �ּҰ� byte�� �������� �ʳ�
void Sort(int* num, int left, int right)//*�� num�� ���� ����Ű�� �ּҷ� num(�ּ�) �޾� �´�
{

	cout << "�̰� ���� Ȯ�� num > " << num << endl;
	cout << "�̰� ���� Ȯ�� *num > " << *num << endl;
	if (left != right)
	{
		int mid = (left + right) / 2;
		Sort(num, left, mid);
		Sort(num, mid + 1, right);
		Merge(num, left, mid, right);
	}
}

void main()
{
	int* num;
	int input;

	cout << "���� �����Ҵ��� ���� �Է�(5) >> ";
	cin >> input;
	cout << endl;

	num = new int[input]; //�ּ� �����ϴ� �ڵ忡�� ũ�� ����

	//Q2
	//vector<int*> sortlist;//vector�� ����Ÿ� �����Ҵ� �ʿ�?
	//vector����� ��������, ������ �ִ���
	//vector����ϸ� �ڵ����� �����Ҵ��� ���ִ� ��?

	for (int i = 0; i < input; i++)
	{
		cout << "���� �Է� : ";
		cin >> *(num + i);
	}

	cout << endl;
	Print("�Է� ���� ���� : ", num, input);
	cout << endl;

	//�������� ��������
	Sort(num, 0, input - 1); //�ּ� �Ѱ���
	Print("������ ���� : ", num, input);

	delete[]num;
}