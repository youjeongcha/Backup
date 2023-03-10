#include<stdio.h>
#include<Windows.h>

typedef struct node
{
	int data;
	struct node* parent; //
	struct node* left;
	struct node* right;
}Node;

void gotoxy(int x, int y);//Ȯ?ξ??ص???
void Left_Print(Node* node, int x, int y, int addx);//Ȯ?ξ??ص???
void Right_Print(Node* node, int x, int y, int addx);//Ȯ?ξ??ص???
void print_data(Node* node);//Ȯ?ξ??ص???
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
		//return?Ŀ? node?? ???? node->right?? ?ִ? ????
		node->right = insert(node->right, data);
		node->right->parent = node;
		//?? ?? ?????? parent?? NULL?? ????
		//???? ???????? node?? parent?? ?θ? ???带 ?ִ´?
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

Node* FindMinNode(Node* node, Node* Parent) //Parent?? ?????? ????
{//Parent ???????? ?޾ƿͼ? ó??
	if (node->left == NULL)
	{//???? ???? ???? ????
		if (node->parent != NULL)
		{//?? ó?? ???? ???? //------?????? ?̷? ?????  ???? ?????? ??ġ?? ?θ? ?????? ?? ???????ٵ??
			//???? ?????? ???鼭 node->parent?? NULL?? ?Ǵ? ???찡 ?ִ?.
			if (Parent != node->parent)//Parent?? ?ڽ??? ?ƴ? ????. ?ǳʰǳ?
				node->parent->left = node->right; //Parent?? ?θ? ?????? ?ڽ??? ?????????ش?.
				//-------node->parent->left?? node?? data?ƴѰ?????? ???? ?̷??? ?????ϴ? ?????
				//?̷??? ?ϴϱ? node?? ???? ?Լ??? ???ϵǰ? node?? ?????ϴ? ?ּҰ??? ??ü?ȴ?
			else//Parent?? ?ڽ??? ????
				node->parent->right = node->right;

			if (node->right != NULL)
				//???? node?? ?ּҰ??̴?. ?ּҰ??? ?ڽ??? ?????? ????
				node->right->parent = node->parent;
				//?????? ????. ?? Parent?? ?θ? ?????? ?ڽ??? ?????????ش?
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
	{//?????? ?????Ϳ? node?? ??ġ?ϸ?
		Node* deletetemp = node;
		if (node->left != NULL && node->right != NULL)
		{//???? ?ڽ??? ?ִ? ????
			Node* MinNode = FindMinNode(node->right, deletetemp);

			//?ּҰ??? ?θ????带 ?̿??ؼ? ?ּ??? ?θ??? ?ٷ? ?Ѱ??ش?
			MinNode->parent = node->parent;

			//???? ?????? ?ڽ? ????
			MinNode->left = deletetemp->left;
			if (deletetemp->left != NULL)
				deletetemp->left->parent = MinNode; //deletetemp->left->parentǥ?? ???? ?? ???? ????
				//???? ?????? ?ڽ??? ?θ??? ?ּҳ????? ???????ش? **?߿?**

			MinNode->right = deletetemp->right;
			if (deletetemp->right != NULL)
				deletetemp->right->parent = MinNode;

			node = MinNode;
		}
		else if (node->left != NULL)
		{//?????? ?ڽĸ? ????. ???? ?? ?ʿ?X
			node->left->parent = node->parent;
			node = node->left;
		}
		else
		{//???? ?ڽĸ? ????. ???? ?? ?ʿ?X
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
		default: //case?????? default?? else?? ????
			printf("Please enter again!\n");
			break;
		}
		system("pause");
	}
}