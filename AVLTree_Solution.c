#include<stdio.h>
#include<Windows.h>

typedef struct node
{
	int data;
	struct node* parent;
	struct node* left;
	struct node* right;
}Node;

void gotoxy(int x, int y);
void Left_Print(Node* node, int x, int y, int addx);
void Right_Print(Node* node, int x, int y, int addx);
void print_data(Node* node);
int Height(Node* node);
int DepthCheck(Node* node);
Node* LL(Node* node);
Node* RR(Node* node);
Node* LR(Node* node);
Node* RL(Node* node);
Node* AVLSet(Node* node);
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
int Height(Node* node)
{
	int HCount = 0;
	if (node != NULL)
	{
		int LeftCount = Height(node->left);
		int RightCount = Height(node->right);
		if (LeftCount > RightCount)
			HCount = LeftCount + 1;
		else
			HCount = RightCount + 1;
	}
	return HCount;
}

int DepthCheck(Node* node)
{
	int LeftCount = Height(node->left);
	int RightCount = Height(node->right);
	return LeftCount - RightCount;
}

Node* LL(Node* node)
{
	Node* temp = node->left;
	node->left = temp->right;
	if (node->left != NULL)
		node->left->parent = node;
	temp->right = node;
	temp->parent = node->parent;
	node->parent = temp;
	return temp;
}

Node* RR(Node* node)
{
	Node* temp = node->right;
	node->right = temp->left;
	if (node->right != NULL)
		node->right->parent = node;
	temp->left = node;
	temp->parent = node->parent;
	node->parent = temp;
	return temp;
}

Node* LR(Node* node)
{
	node->left = RR(node->left);
	return LL(node);
}

Node* RL(Node* node)
{
	node->right = LL(node->right);
	return RR(node);
}

Node* AVLSet(Node* node)
{
	int Depth = DepthCheck(node);
	if (Depth > 1)
	{
		if (DepthCheck(node->left) > 0)
			node = LL(node);
		else
			node = LR(node);
	}
	else if (Depth < -1)
	{
		if (DepthCheck(node->right) > 0)
			node = RL(node);
		else
			node = RR(node);
	}
	return node;
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
		node->right = insert(node->right, data);
		node->right->parent = node;
		node = AVLSet(node);
	}
	else if (node->data > data)
	{
		node->left = insert(node->left, data);
		node->left->parent = node;
		node = AVLSet(node);
	}
	else
	{
		printf("Data already exists\n");
	}
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

Node* FindMinNode(Node* node, Node* Parent)
{
	if (node->left == NULL)
	{
		if (node->parent != NULL)
		{
			if (Parent != node->parent)
				node->parent->left = node->right;
			else
				node->parent->right = node->right;

			if (node->right != NULL)
				node->right->parent = node->parent;
		}
		return node;
	}
	else
		return FindMinNode(node->left, Parent);
}

Node* Delete(Node* node, int data)
{//표시 안 되어있지만 Delete에도 정렬 필요한 거 맞음
	if (node == NULL)
	{
		printf("Not find data\n");
	}
	else if (node->data > data)
		node->left = Delete(node->left, data);
	else if (node->data < data)
		node->right = Delete(node->right, data);
	else
	{
		Node* deletetemp = node;
		if (node->left != NULL && node->right != NULL)
		{
			Node* MinNode = FindMinNode(node->right, deletetemp);

			MinNode->parent = node->parent;

			MinNode->left = deletetemp->left;
			if (deletetemp->left != NULL)
				deletetemp->left->parent = MinNode;

			MinNode->right = deletetemp->right;
			if (deletetemp->right != NULL)
				deletetemp->right->parent = MinNode;

			node = MinNode;
		}
		else if (node->left != NULL)
		{
			if (node->left != NULL)
				node->left->parent = node->parent;
			node = node->left;
		}
		else
		{
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
		default:
			printf("Please enter again!\n");
			break;
		}
		system("pause");
	}
}