#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
//2진탐색트리,B Tree,AVL Tree, 레드 블랙Tree
#define WIDTH_VALUE 20
#define HEIGHT_VALUE 4

typedef struct Node
{
	int Data;
	struct Node* Left;
	struct Node* Right;
}Node;

//200번째 줄이 필요한 이유

void gotoxy(int x, int y); //확인안해도됨 //전방 선언
void RightPrint(Node* node, int x, int y);//확인안해도됨
void LeftPrint(Node* node, int x, int y);//확인안해도됨
void Print_Tree(Node* node);//확인안해도됨
Node* CreateNode(int Data);
Node* Insert(Node* node, int Data);
void PreOrder(Node* node);
void PostOrder(Node* node);
void InOrder(Node* node);
int Search(Node* node, int Data);
void AllDelete(Node* node);
Node* Delete(Node* node, int Data);

//WinAIP -> 마이크로소프트사에서 제공하는 윈도우즈 컨트롤 함수 모음
void gotoxy(int x, int y)//원하는 좌표로 커서를 이동해 주는 함수
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
		else {//중복 숫자 체크
			printf("중복된 숫자가 이미 존재합니다.\n");
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
{//기능 나누기 참고
	if (node == NULL)
	{
		printf("%d는 존재하지 않습니다.\n", Data);
		return -1;
	}
	else if (node->Data == Data)
	{
		printf("%d는 존재합니다.\n", Data);
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
	{//가장 작은 수를 찾는다
		*MinNode = node; //*MinNode로 최소값을 주소값을 이용해 따로 받는다. minimumSeach()의 역할
		node = node->Right; //minimumSearch()와 childLink()를 합쳐둔 구조
		return node;
	}
	else
	{
		node->Left = FindMinNode(node->Left, MinNode);
		//FindeMinNode()로 최소를 찾고 바로 위로 부모 노드를 대체
		return node;
	}
}

Node* Delete(Node* node, int Data)
{
	if (node == NULL)
	{
		printf("삭제할 데이터가 존재하지 않습니다.\n");
		return NULL;
	}
	else if (node->Data == Data)
	{
		Node* DeleteNode = node;
		if (node->Left == NULL && node->Right == NULL)
			//나는 이 경우가 알아서 되도록 했음. 다른 점
			node = NULL;
		else if (node->Left != NULL && node->Right == NULL)
			//왼쪽 트리만 존재
			node = node->Left;
		else if (node->Left == NULL && node->Right != NULL)
			//오른쪽 트리만 존재
			node = node->Right;
		else
		{//자녀가 둘다 존재
			Node* MinNode = NULL;
			node->Right = FindMinNode(node->Right, &MinNode); //MinNode 주소를 이용해 리턴받지 않고 값 변경
			MinNode->Left = DeleteNode->Left;
			MinNode->Right = DeleteNode->Right;
			node = MinNode;
		}
		printf("%d데이터를 삭제하였습니다.", Data);
		free(DeleteNode);
		return node;
	}
	else
	{//해당 역할 별로 구역 정리
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