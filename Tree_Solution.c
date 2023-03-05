#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
//2��Ž��Ʈ��,B Tree,AVL Tree, ���� ��Tree
#define WIDTH_VALUE 20
#define HEIGHT_VALUE 4

typedef struct Node
{
	int Data;
	struct Node* Left;
	struct Node* Right;
}Node;

//200��° ���� �ʿ��� ����

void gotoxy(int x, int y); //Ȯ�ξ��ص��� //���� ����
void RightPrint(Node* node, int x, int y);//Ȯ�ξ��ص���
void LeftPrint(Node* node, int x, int y);//Ȯ�ξ��ص���
void Print_Tree(Node* node);//Ȯ�ξ��ص���
Node* CreateNode(int Data);
Node* Insert(Node* node, int Data);
void PreOrder(Node* node);
void PostOrder(Node* node);
void InOrder(Node* node);
int Search(Node* node, int Data);
void AllDelete(Node* node);
Node* Delete(Node* node, int Data);

//WinAIP -> ����ũ�μ���Ʈ�翡�� �����ϴ� �������� ��Ʈ�� �Լ� ����
void gotoxy(int x, int y)//���ϴ� ��ǥ�� Ŀ���� �̵��� �ִ� �Լ�
{
	COORD pos = { x,y }; 
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); //?
}

void RightPrint(Node* node, int x, int y)
{
	if (node == NULL)
		return;
	x += WIDTH_VALUE;
	y += HEIGHT_VALUE;
	gotoxy(x, y);
	printf("%d", node->Data);
	RightPrint(node->Right, x, y);
	LeftPrint(node->Left, x, y);
}

void LeftPrint(Node* node, int x, int y)
{
	if (node == NULL)
		return;
	x -= WIDTH_VALUE;
	y += HEIGHT_VALUE;
	gotoxy(x, y);
	printf("%d", node->Data);
	RightPrint(node->Right, x, y);
	LeftPrint(node->Left, x, y);
}

void Print_Tree(Node* node)
{
	system("cls");
	int x = 70, y = 2;
	if (node == NULL)
		return;
	gotoxy(x, y);
	printf("%d", node->Data);
	RightPrint(node->Right, x, y);
	LeftPrint(node->Left, x, y);
	gotoxy(0, 0);
}

Node* CreateNode(int Data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->Data = Data;
	newNode->Right = NULL;
	newNode->Left = NULL;
	return newNode;
}

Node* Insert(Node* node, int Data)
{
	if (node == NULL)
	{
		return CreateNode(Data);
	}
	else
	{
		if (node->Data > Data)
			node->Left = Insert(node->Left, Data);
		else if (node->Data < Data)
			node->Right = Insert(node->Right, Data);
		else {//�ߺ� ���� üũ
			printf("�ߺ��� ���ڰ� �̹� �����մϴ�.\n");
		}
		return node;
	}
}
void PreOrder(Node* node)
{
	if (node == NULL)
		return;
	printf("%d ", node->Data);
	PreOrder(node->Left);
	PreOrder(node->Right);
}

void InOrder(Node* node)
{
	if (node == NULL)
		return;
	InOrder(node->Left);
	printf("%d ", node->Data);
	InOrder(node->Right);
}

void PostOrder(Node* node)
{
	if (node == NULL)
		return;
	PostOrder(node->Left);
	PostOrder(node->Right);
	printf("%d ", node->Data);
}

void AllDelete(Node* node)
{
	if (node == NULL)
		return;
	AllDelete(node->Left);
	AllDelete(node->Right);
	free(node);
}

int Search(Node* node, int Data)
{//��� ������ ����
	if (node == NULL)
	{
		printf("%d�� �������� �ʽ��ϴ�.\n", Data);
		return -1;
	}
	else if (node->Data == Data)
	{
		printf("%d�� �����մϴ�.\n", Data);
		return node->Data;
	}
	else
	{
		if (node->Data > Data)
			return Search(node->Left, Data);
		else if (node->Data < Data)
			return Search(node->Right, Data);
	}
}

Node* FindMinNode(Node* node, Node** MinNode)
{
	if (node->Left == NULL)
	{//���� ���� ���� ã�´�
		*MinNode = node; //*MinNode�� �ּҰ��� �ּҰ��� �̿��� ���� �޴´�. minimumSeach()�� ����
		node = node->Right; //minimumSearch()�� childLink()�� ���ĵ� ����
		return node;
	}
	else
	{
		node->Left = FindMinNode(node->Left, MinNode);
		//FindeMinNode()�� �ּҸ� ã�� �ٷ� ���� �θ� ��带 ��ü
		return node;
	}
}

Node* Delete(Node* node, int Data)
{
	if (node == NULL)
	{
		printf("������ �����Ͱ� �������� �ʽ��ϴ�.\n");
		return NULL;
	}
	else if (node->Data == Data)
	{
		Node* DeleteNode = node;
		if (node->Left == NULL && node->Right == NULL)
			//���� �� ��찡 �˾Ƽ� �ǵ��� ����. �ٸ� ��
			node = NULL;
		else if (node->Left != NULL && node->Right == NULL)
			//���� Ʈ���� ����
			node = node->Left;
		else if (node->Left == NULL && node->Right != NULL)
			//������ Ʈ���� ����
			node = node->Right;
		else
		{//�ڳడ �Ѵ� ����
			Node* MinNode = NULL;
			node->Right = FindMinNode(node->Right, &MinNode); //MinNode �ּҸ� �̿��� ���Ϲ��� �ʰ� �� ����
			MinNode->Left = DeleteNode->Left;
			MinNode->Right = DeleteNode->Right;
			node = MinNode;
		}
		printf("%d�����͸� �����Ͽ����ϴ�.", Data);
		free(DeleteNode);
		return node;
	}
	else
	{//�ش� ���� ���� ���� ����
		if (node->Data > Data)
			node->Left = Delete(node->Left, Data);
		else
			node->Right = Delete(node->Right, Data);
		return node;
	}
}

void main()
{
	Node* Root = NULL;
	int Data;
	while (1)
	{
		printf("========Tree========\n");
		printf("1.Insert\n");
		printf("2.Print\n");
		printf("3.PreOrder\n");
		printf("4.InOrder\n");
		printf("5.PostOrder\n");
		printf("6.Delete\n");
		printf("7.Search\n");
		printf("8.Exit\n");
		int Select;
		printf("Input >> ");
		scanf("%d", &Select);
		switch (Select)
		{
		case 1:
			printf("Input Data >>");
			scanf("%d", &Data);
			Root = Insert(Root, Data);
			Print_Tree(Root);
			break;
		case 2:
			Print_Tree(Root);
			break;
		case 3:
			Print_Tree(Root);
			gotoxy(0, 0);
			printf("PreOrder : ");
			PreOrder(Root);
			break;
		case 4:
			Print_Tree(Root);
			gotoxy(0, 0);
			printf("InOrder : ");
			InOrder(Root);
			break;
		case 5:
			Print_Tree(Root);
			gotoxy(0, 0);
			printf("PostOrder : ");
			PostOrder(Root);
			break;
		case 6:
			printf("Input Data >>");
			scanf("%d", &Data);
			Root = Delete(Root, Data);
			Print_Tree(Root);
			break;
		case 7:
			Print_Tree(Root);
			printf("Input Data >>");
			scanf("%d", &Data);
			Search(Root, Data);
			break;
		case 8:
			AllDelete(Root);
			return;
		}
		system("pause");
	}
}