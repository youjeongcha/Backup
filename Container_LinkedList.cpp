#include<stdio.h>
#include<list>//Linked Type List
#include<vector>//Array Type List
#include<algorithm>//�˰��� vector���� ���

//�����󵵿� ���ٺ�

//list
//���� : �������� �߰� ���Ű� �����Ӵ�.
//���� : Ư�� �������� ���ټӵ��� ������.
//--��� �߰��� �Ǵ� ���

//vector �����迭
//���� : Ư�� �������� ���ټӵ��� ������. > �ּҰ� ���������� �����Ǿ��ִ�.
//���� : �������� �߰� ���Ű� �������� ���ϴ�. > ���迭 ũ��+1 �� ���� �����ϰ� �߰�
//-- ������ ���� �ѹ� �صΰ� ���� �ӵ� ������ �Ҷ�

void PrintList(std::vector<int> iList)
{//iterator ������ �����͸� ����Ű�� ������ ���� ���� ����
	//begin()���� ó�� ������ �����͸� ����Ű�� ������ ���� ����//�׷��ٰ� �����ʹ� �ƴ�
	//end() ������ ���� ������ �ΰ� ���� ���� //������ �����ʹ� vack
	//for (std::vector<int>::iterator iter = iList.begin(); iter != iList.end(); iter++)
	for (int i = 0; i < iList.size(); i++)
		printf("%d ", iList[i]);//�����Ϳ� ����� ���� ������ �ּҸ� ���󰡶� ����
	printf("\n");
}

std::vector<int>::iterator Search(std::vector<int>* iList, int Data)
{
	for (std::vector<int>::iterator iter = iList->begin(); iter != iList->end(); iter++)
	{
		if (*iter == Data)
			return iter;
	}
	return iList->end();
}

void SearchData(std::vector<int> iList, int Data)
{
	//std::vector<int>::iterator iter = Search(&iList, Data);
	std::vector<int>::iterator iter = std::find(iList.begin(), iList.end(), Data); //��Ȯ�ϰ� ��ɷ� ���� �ƴ� ��Ȳ ex>����ü���� �� �Ұ� C++�� ����
	if (iter == iList.end())
		printf("������ %d�� ã�����߽��ϴ�.\n", Data);
	else
		printf("������ %d�� ã�ҽ��ϴ�.\n", Data);
}

void Add(std::vector<int>* iList, int Data, int AddData)
{
	std::vector<int>::iterator iter = Search(iList, Data);
	if(iter == iList->end())
		printf("������ %d�� ã�����߽��ϴ�.\n", Data);
	else
	{
		//���ٰ� �߰��� �ų�. �� �߰��� �ų� ����
		iList->insert(iter, AddData);
	}
}

void Modify(std::vector<int>* iList, int Data, int ModifyData)
{
	std::vector<int>::iterator iter = Search(iList, Data);
	if (iter == iList->end())
		printf("������ %d�� ã�����߽��ϴ�.\n", Data);
	else
	{
		*iter = ModifyData;
	}
}

void Delete(std::vector<int>* iList, int Data)
{
	std::vector<int>::iterator iter = Search(iList, Data);
	if (iter == iList->end())
		printf("������ %d�� ã�����߽��ϴ�.\n", Data);
	else
	{
		iList->erase(iter);
	}
}

void main()
{
	//����, ���, �˻�, �߰�, ����, ����
	std::vector<int> iList;
	
	for (int i = 1; i <= 10; i++) 
		iList.push_back(i); //�ڿ� ����

	///iList.push_front(11); //�տ� ����
	PrintList(iList);

	SearchData(iList, 5);
	SearchData(iList, 25);

	Add(&iList, 5, 25);
	PrintList(iList);

	Modify(&iList, 7, 77);
	PrintList(iList);

	iList.pop_back(); //vector���� pop_back push_back�� �� �ȴ�
	PrintList(iList);

	///iList.pop_front();
	PrintList(iList);

	Delete(&iList, 77);
	PrintList(iList);

	//front
	//back�� Queue�� ����
	//empty ����ִ°� Ȯ���ϴ�

	iList.clear();//��ü����
	///iList.sort();//�������� ����
	//vector ����
	std::sort(iList.begin(), iList.end());//��������
	std::sort(iList.begin(), iList.end(),std::greater<int>());//��������
	///iList.reverse();//������ ����
	//������ �������� ���� X > sort()�ϰ� reverse()
}