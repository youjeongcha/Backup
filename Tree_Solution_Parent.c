#include<stdio.h>
#include<Windows.h>

typedef struct node
{
	int data;
	struct node* parent; //
	struct node* left;
	struct node* right;
}Node;

void gotoxy(int x, int y);//확인안해도됨
void Left_Print(Node* node, int x, int y, int addx);//확인안해도됨
void Right_Print(Node* node, int x, int y, int addx);//확인안해도됨
void print_data(Node* node);//확인안해도됨
Node* insert(Node* node, int data);
void PreOrder(Node* node);
void InOrder(Node* node);
void PostOrder(Node* node);
void All_Delete(Node* node);
Node* Delete(Node* node, int data);


void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void Left_Print(Node* node, int x, int y, int addx)
{
	if (node == NULL)	return;
	gotoxy(x -= addx, y += 2);
	printf("%d(", node->data);
	if (node->parent != NULL)
		printf("%d)", node->parent->data);
	else
		printf("NULL)");
	if (node->left)
		Left_Print(node->left, x, y, addx - 4);
	if (node->right)
		Right_Print(node->right, x, y, addx - 4);
}
void Right_Print(Node* node, int x, int y, int addx)
{
	if (node == NULL)	return;
	gotoxy(x += addx, y += 2);
	printf("%d(", node->data);
	if (node->parent != NULL)
		printf("%d)", node->parent->data);
	else
		printf("NULL)");
	if (node->left)
		Left_Print(node->left, x, y, addx - 4);
	if (node->right)
		Right_Print(node->right, x, y, addx - 4);
}
void print_data(Node* node)
{
	int x = 70, y = 2;
	if (node == NULL)
		return;

	gotoxy(x, y);
	printf("%d(", node->data);
	if (node->parent != NULL)
		printf("%d)", node->parent->data);
	else
		printf("NULL)");
	if (node->right) {
		Right_Print(node->right, x, y, 32);
	}
	if (node->left) {
		Left_Print(node->left, x, y, 32);
	}
	gotoxy(0, 10);
}


Node* insert(Node* node, int data)
{
	if (node == NULL)
	{
		node = (Node*)malloc(sizeof(Node));
		node->data = data;
		node->left = NULL;
		node->right = NULL;
		node->parent = NULL;
		return node;
	}
	else if (node->data < data)
	{
		//return후에 node로 존재 node->right를 넣는 이유
		node->right = insert(node->right, data);
		node->right->parent = node;
		//맨 앞 노드의 parent는 NULL로 존재
		//새로 만들어진 node의 parent에 부모 노드를 넣는다
	}
	else if (node->data > data)
	{
		node->left = insert(node->left, data);
		node->left->parent = node;
	}
	else
		printf("Data already exists\n");
	return node;
}

void PreOrder(Node* node)
{
	if (node == NULL)
		return;
	printf("%d ", node->data);
	PreOrder(node->left);
	PreOrder(node->right);
}

void InOrder(Node* node)
{
	if (node == NULL)
		return;
	InOrder(node->left);
	printf("%d ", node->data);
	InOrder(node->right);
}

void PostOrder(Node* node)
{
	if (node == NULL)
		return;
	PostOrder(node->left);
	PostOrder(node->right);
	printf("%d ", node->data);
}

void All_Delete(Node* node)
{
	if (node == NULL)
		return;
	All_Delete(node->left);
	All_Delete(node->right);
	printf("%d Deallocation Success \n", node->data);
	free(node);
}

Node* FindMinNode(Node* node, Node* Parent) //Parent가 삭제할 노드
{//Parent 노드까지 받아와서 처리
	if (node->left == NULL)
	{//가장 작은 수일 경우
		if (node->parent != NULL)
		{//맨 처음 노드 제외 //------조건이 이런 이유?  앞의 조건을 거치면 부모 노드는 다 존재할텐데?
			//안의 조건을 돌면서 node->parent가 NULL이 되는 경우가 있다.
			if (Parent != node->parent)//Parent의 자식이 아닐 경우. 건너건너
				node->parent->left = node->right; //Parent의 부모 노드와 자식을 연결시켜준다.
				//-------node->parent->left가 node의 data아닌가????? 굳이 이렇게 사용하는 이유?
				//이렇게 하니까 node의 값은 함수에 리턴되고 node에 존재하는 최소값이 대체된다
			else//Parent의 자식일 경우
				node->parent->right = node->right;

			if (node->right != NULL)
				//현재 node는 최소값이다. 최소값의 자식이 있으면 실행
				node->right->parent = node->parent;
				//삭제할 노드. 즉 Parent의 부모 노드와 자식을 연결시켜준다
		}
		return node;
	}
	else
		return FindMinNode(node->left, Parent);
}

Node* Delete(Node* node, int data)
{
	if (node == NULL)
	{
		printf("Not find data\n");
	}
	else if (node->data > data)
		node->left = Delete(node->left, data);
	else if (node->data < data)
		node->right = Delete(node->right, data);
	else
	{//삭제할 데이터와 node가 일치하면
		Node* deletetemp = node;
		if (node->left != NULL && node->right != NULL)
		{//양쪽 자식이 있는 경우
			Node* MinNode = FindMinNode(node->right, deletetemp);

			//최소값을 부모노드를 이용해서 최소의 부모로 바로 넘겨준다
			MinNode->parent = node->parent;

			//삭제 노드의 자식 연결
			MinNode->left = deletetemp->left;
			if (deletetemp->left != NULL)
				deletetemp->left->parent = MinNode; //deletetemp->left->parent표현 방법 감 잡기 주의
				//삭제 노드의 자식의 부모를 최소노드로 만들어준다 **중요**

			MinNode->right = deletetemp->right;
			if (deletetemp->right != NULL)
				deletetemp->right->parent = MinNode;

			node = MinNode;
		}
		else if (node->left != NULL)
		{//오른쪽 자식만 존재. 재귀 돌 필요X
			node->left->parent = node->parent;
			node = node->left;
		}
		else
		{//왼쪽 자식만 존재. 재귀 돌 필요X
			if (node->right != NULL)
				node->right->parent = node->parent;
			node = node->right;
		}
		free(deletetemp);
	}
	return node;
}

void Search(Node* node, int Data)
{
	if (node == NULL)
	{
		printf("Not Find Data..\n");
		return;
	}
	else if (node->data == Data)
	{
		printf("Find Success Data!!\n");
		return;
	}
	else if (node->data > Data)
		Search(node->left, Data);
	else if (node->data < Data)
		Search(node->right, Data);
}

void main()
{
	Node* Root = NULL;
	int Select;
	while (1)
	{
		system("cls");
		printf("======AVLTree======\n");
		printf("1.Insert\n");
		printf("2.Search\n");
		printf("3.PrintTree\n");
		printf("4.PreOrder\n");
		printf("5.InOrder\n");
		printf("6.PostOrder\n");
		printf("7.Delete\n");
		printf("8.Exit\n");
		printf("Input >> ");
		scanf("%d", &Select);
		system("cls");
		switch (Select)
		{
		case 1:
			printf("Add Data >> ");
			scanf("%d", &Select);
			Root = insert(Root, Select);
			print_data(Root);
			break;
		case 2:
			printf("Select Data >> ");
			scanf("%d", &Select);
			Search(Root, Select);
			break;
		case 3:
			print_data(Root);
			break;
		case 4:
			PreOrder(Root);
			break;
		case 5:
			InOrder(Root);
			break;
		case 6:
			PostOrder(Root);
			break;
		case 7:
			printf("Delete Data >> ");
			scanf("%d", &Select);
			Root = Delete(Root, Select);
			break;
		case 8:
			All_Delete(Root);
			return;
		default: //case문에서 default는 else와 같다
			printf("Please enter again!\n");
			break;
		}
		system("pause");
	}
}