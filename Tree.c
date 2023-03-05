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
{//���� �ΰ�
	if (node == NULL)
	{
		node = (Node*)malloc(sizeof(Node));
		node->data = temp;
		node->leftNode = NULL;
		node->rightNode = NULL;
		return node;
	}
	else
	{//��ͷ� ���� ����
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
{//���� ��ȸ �Լ�
	//����� �������� ���� �� ����. ���� �����δ� �������� �ʴ� ��ġ�� ��尡 NULL�� ��Ÿ����.
	if (node != NULL)
	{
		printf("%d ", node->data);
		preOrder(node->leftNode);
		preOrder(node->rightNode);
	}
}

void inOrder(Node* node)
{//���� ��ȸ �Լ�
	if (node != NULL)
	{
		inOrder(node->leftNode);
		printf("%d ", node->data);
		inOrder(node->rightNode);
	}
}

void postOrder(Node* node)
{//���� ��ȸ �Լ�
	if (node != NULL)
	{
		postOrder(node->leftNode);
		postOrder(node->rightNode);
		printf("%d ", node->data);
	}
}

void exit(Node* node)
{//PostOrder�� ����ϴ� ���� ��>����>�Ѹ� �� ����
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
{//������ ���� Ʈ������ ���� ���� ���� �޾ƿ´�.
	//��ͷ� �и�. ���ʰ� ������ �ű�� �۾��� ���� �༮ ���� ó���ϰ� ����
	if (node->leftNode != NULL)
	{
		node = minimumSearch(node->leftNode);
	}
	return node;
}

Node* deleteNode(Node* node, int input)
{
	//root�� NULL�� ���, Ʈ���� ����ִ�.
	if (node == NULL)
		printf("%d�� �������� �ʽ��ϴ�.\n", input);
	else
	{
		//key�� ����� Ű������ �۰ų� Ŭ ���(����Ʈ�� �̵�)
		if (input < node->data)
			node->leftNode = deleteNode(node->leftNode, input);
		else if (input > node->data)
			node->rightNode = deleteNode(node->rightNode, input);
		//Ű�� ����� Ű���� ���� ���(����)
		else
		{
			Node* DeleteNode = node;
			//����� �ڳడ �Ѱ��� ���(���� �ƴϸ� ������)
			if (node->leftNode == NULL)
				node = node->rightNode;
			else if (node->rightNode == NULL)
				node = node->leftNode;
			//����� �ڳడ �ΰ��� ���(���� ������ �� ��)
			//������ ����Ʈ������ ���� ���� ���� �����Ѵ�.
			else
			{
				node = minimumSearch(node->rightNode); //temp �����ʿ��� ���� ���� �� 22
				//�ö󰡴� ����� �ڽ� ��� ����
				//temp�� node � �������� üũ node�� 20
				node->rightNode = childLink(DeleteNode->rightNode);
				node->leftNode = DeleteNode->leftNode;
			}
			free(DeleteNode);
		}
	}
	return node;
}

void search(Node* node, int temp)
{//Ʈ�� ������ ����
	if (node != NULL)
	{
		if (node->data == temp)
			printf("%d�� �����մϴ�.\n", temp);
		else if (node->data > temp)
			search(node->leftNode, temp);
		else if (node->data < temp)
			search(node->rightNode, temp);
	}
	else
		printf("%d�� �������� �ʽ��ϴ�.\n", temp);
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
		case 2: //����
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
		case 7: //���λ���
			printf("Input Data >> ");
			scanf("%d", &temp);
			search(node, temp);
			break;
		case 8: //��ü ���� postOrder �̿�
			exit(node); //�����Ҵ� ���� - ����X
			return;
		}
		system("pause");
		system("cls");
	}
}