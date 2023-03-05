#include<stdio.h>
#include<Windows.h>

//insert직후 delet직후 밸런스 체크

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
Node* AVLSetUp(Node* node);
int DepthCheck(Node* node);
Node* LeftTo(Node* node, Node* temp);
Node* RightTo(Node* node, Node* temp);


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
		//=======//insert직후 delet직후 밸런스 체크
		node = AVLSetUp(node); //////
	}
	else if (node->data > data)
	{
		node->left = insert(node->left, data);
		node->left->parent = node;
		//=======//insert직후 delet직후 밸런스 체크
		node = AVLSetUp(node); //////
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
		{//맨 처음 노드 제외
			//안의 조건을 돌면서 node->parent가 NULL이 되는 경우가 있다.
			if (Parent != node->parent)//Parent의 자식이 아닐 경우. 건너건너
				node->parent->left = node->right; //Parent의 부모 노드와 자식을 연결시켜준다.
				//node->parent->left가 node의 data인데 이렇게 사용하는 이유 주의
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
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             

int DepthCheck(Node* node)
{
	int DepthCount = 0;
	if (node != NULL)
	{
		int LeftDepth = DepthCheck(node->left);
		int RigthDepth = DepthCheck(node->right);

		if (LeftDepth > RigthDepth)
			DepthCount = LeftDepth + 1;
		else
			DepthCount = RigthDepth + 1;
	}
	return DepthCount;
}

int GetDepth(Node* node)
{
	int LeftDepth = DepthCheck(node->left);
	int RightDepth = DepthCheck(node->right);
	return LeftDepth - RightDepth;
}

Node* LeftTo(Node* node, Node* temp)
{
	node->left = temp->right; //절댓값 0 노드의 오른쪽 자식을 부모의 왼쪽에 받는다
	//temp->rigth 가 null이 아닐 경우에 부모 설정 변경 해줘야 함
	if (temp->right != NULL)
	{//숫자 예시 들어봐야 한다
		temp->right->parent = node;
	}
	temp->right = node; //B를 D의 오른쪽에 넣는다
	temp->parent = node->parent;//D의 부모를 B에서 A로 변경
	//temp->parent->left = temp; //A의 왼쪽에도 넣는단 ///root노드일 경우 문제가 생긴다.
	//밖에 리턴되면서 세팅되는 코드가 이미 존재한다. node가 9 리턴되어 나가면 부모와 연결된다.
	node->parent = temp;//B의 부모 A에서 D로
	return temp;
}

Node* RightTo(Node* node, Node* temp)
{
	node->right = temp->left;
	if (temp->left != NULL)
	{//숫자 예시 들어봐야 한다
		temp->left->parent = node;
	}
	temp->left = node;
	temp->parent = node->parent;
	//temp->parent->right = temp;
	node->parent = temp;
	return temp;
}

Node* AVLSetUp(Node* node)
{
	//균형 조절 코드
	int Depth = GetDepth(node);
	if (Depth >= 2)//절댓값으로 left더 가 깊다
	{
		//바로 left-right == 1인 노드로 문제 노드는 이동해야할 노드의 부모
		//***옮겨야 할 노드의 부모가 문제가 있는 노드***
		if (GetDepth(node->left) >= 1)//GethDepth가 ChildeNode가 된다
		{//Left to Left
			//temp는 node의 자식 //tmep는 node 다음으로 크다
			Node* temp = node->left; //node 9 //temp 8
			node = LeftTo(node, temp);
		}
		else
		{//Left to Right
			//temp는 node의 자식의 오른쪽 //tmep는 node 다음으로 크다
			//Node* temp = node->left->right; //node 9 //temp 8
			//temp->left = node->left; //temp->left는 7
			//node->left->parent = temp;

			Node* temp = node->left;
			node->right = RightTo(temp, temp->right); //node 7 //temp 8
			node = LeftTo(node, node->right); //node 9 //temp는 node의 왼쪽 자식
		}
	}
	else if (Depth <= -2) //Right가 더 깊다
	{
		if (GetDepth(node->right) >= 1)//구조도 납득 필요 그려보자
		{//Right to Left
			//temp->right = node->right; //temp->right는 13
			//node->right->parent = temp;
			Node* temp = node->right; //node 11 //temp 12
			node->left = LeftTo(temp, temp->left);
			node =  RightTo(node, node->left);
		}
		else
		{//Right to Right
			Node* temp = node->right; //node 11 //temp 12
			node = RightTo(node, temp);
		}
	}
	//printf("%3d : left : %d\t Right : %d\n", node->data, LeftDepth, RightDepth);
	//3d 띄어쓰기 공간 담아서 출력
	return node;
}

Node* Delete(Node* node, int data)
{
	if (node == NULL)
	{
		printf("Not find data\n");
	}
	else if (node->data > data)
	{
		node->left = Delete(node->left, data);
		//=========//insert직후 delet직후 밸런스 체크 A노드에서
		node = AVLSetUp(node); ////
	}
	else if (node->data < data)
	{
		node->right = Delete(node->right, data);
		//=========//insert직후 delet직후 밸런스 체크 A노드에서
		node = AVLSetUp(node); ////
	}
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
			system("pause");
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