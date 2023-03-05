#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>

typedef struct Node
{
	int data;
	struct Node* leftNode;
	struct Node* rightNode;
} Node;

Node* insert(Node* node, int temp)
{//인자 두개
	if (node == NULL)
	{
		node = (Node*)malloc(sizeof(Node));
		node->data = temp;
		node->leftNode = NULL;
		node->rightNode = NULL;
		return node;
	}
	else
	{//재귀로 구성 가능
		if (node->data > temp)
			node->leftNode = insert(node->leftNode, temp);
		else if (node->data < temp)
			node->rightNode = insert(node->rightNode, temp);
		return node;
	}
}

void print(Node* node)
{

}

void preOrder(Node* node)
{//전위 순회 함수
	//출력을 기준으로 보면 더 쉽다. 로직 상으로는 존재하지 않는 위치의 노드가 NULL로 나타난다.
	if (node != NULL)
	{
		printf("%d ", node->data);
		preOrder(node->leftNode);
		preOrder(node->rightNode);
	}
}

void inOrder(Node* node)
{//중위 순회 함수
	if (node != NULL)
	{
		inOrder(node->leftNode);
		printf("%d ", node->data);
		inOrder(node->rightNode);
	}
}

void postOrder(Node* node)
{//후위 순회 함수
	if (node != NULL)
	{
		postOrder(node->leftNode);
		postOrder(node->rightNode);
		printf("%d ", node->data);
	}
}

void exit(Node* node)
{//PostOrder로 사용하는 이유 잎>가지>뿌리 순 제거
	if (node != NULL)
	{
		exit(node->leftNode);
		exit(node->rightNode);
		printf("%d ", node->data);
		free(node);
	}
}

Node* childLink(Node* node)
{
	if (node != NULL)
	{
		if (node->leftNode == NULL)
		{
			node = node->rightNode;
		}
		else
			node->leftNode = childLink(node->leftNode);
	}
	return node;
}

Node* minimumSearch(Node* node)
{//오른쪽 서브 트리에서 가장 작은 수를 받아온다.
	//재귀로 분리. 왼쪽과 오른족 옮기는 작업은 작은 녀석 먼저 처리하고 나서
	if (node->leftNode != NULL)
	{
		node = minimumSearch(node->leftNode);
	}
	return node;
}

Node* deleteNode(Node* node, int input)
{
	//root가 NULL일 경우, 트리가 비어있다.
	if (node == NULL)
		printf("%d는 존재하지 않습니다.\n", input);
	else
	{
		//key가 노드의 키값보다 작거나 클 경우(하위트리 이동)
		if (input < node->data)
			node->leftNode = deleteNode(node->leftNode, input);
		else if (input > node->data)
			node->rightNode = deleteNode(node->rightNode, input);
		//키가 노드의 키값과 같은 경우(삭제)
		else
		{
			Node* DeleteNode = node;
			//노드의 자녀가 한개일 경우(왼쪽 아니면 오른쪽)
			if (node->leftNode == NULL)
				node = node->rightNode;
			else if (node->rightNode == NULL)
				node = node->leftNode;
			//노드의 자녀가 두개일 경우(왼쪽 오른쪽 둘 다)
			//오른쪽 서브트리에서 가장 적은 수를 선택한다.
			else
			{
				node = minimumSearch(node->rightNode); //temp 오른쪽에서 가장 작은 수 22
				//올라가는 노드의 자식 노드 연결
				//temp와 node 어떤 상태인지 체크 node가 20
				node->rightNode = childLink(DeleteNode->rightNode);
				node->leftNode = DeleteNode->leftNode;
			}
			free(DeleteNode);
		}
	}
	return node;
}

void search(Node* node, int temp)
{//트리 오른쪽 왼쪽
	if (node != NULL)
	{
		if (node->data == temp)
			printf("%d는 존재합니다.\n", temp);
		else if (node->data > temp)
			search(node->leftNode, temp);
		else if (node->data < temp)
			search(node->rightNode, temp);
	}
	else
		printf("%d는 존재하지 않습니다.\n", temp);
}


void main()
{
	Node* node = NULL;
	Node* moveNode = NULL;
	int select, input;
	int temp = 0;
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
		printf("Input >> ");
		scanf("%d", &select);

		switch (select) {
		case 1:
			printf("Input Data >> ");
			scanf("%d", &temp);
			node = insert(node, temp);
			break;
		case 2: //보류
			//print(node);
			break;
		case 3:
			printf("PreOrder : ");
			preOrder(node);
			break;
		case 4:
			printf("InOrder : ");
			inOrder(node);
			break;
		case 5:
			printf("PostOrder : ");
			postOrder(node);
			break;
		case 6:
		{
			printf("Input Data >> ");
			scanf("%d", &input);
			node = deleteNode(node, input);
			break;
		}
		case 7: //세부사항
			printf("Input Data >> ");
			scanf("%d", &temp);
			search(node, temp);
			break;
		case 8: //전체 삭제 postOrder 이용
			exit(node); //동적할당 해제 - 리턴X
			return;
		}
		system("pause");
		system("cls");
	}
}