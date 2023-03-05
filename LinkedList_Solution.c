#include<stdio.h>
#include<malloc.h> //malloc은 stdlib.h에서 사용하는 걸로 암
#include<string.h> //문자열 비교 복사 등 string cat string cpy
#include<Windows.h>
typedef struct node
{
	char name[20];
	char add[20];
	int sum, kor, eng, mat, age; //입력방식
	float abs;
	char grade;
	struct node* link;
}node;

void SetGrade(node* head)
{
	head->sum = (head->eng) + (head->kor) + (head->mat);
	head->abs = head->sum / 3;
	if (head->abs > 90)
		head->grade = 'A';
	else if (head->abs > 80)
		head->grade = 'B';
	else if (head->abs > 70)
		head->grade = 'C';
	else if (head->abs > 60)
		head->grade = 'D';
	else
		head->grade = 'F';
}

node* get_node()
{//함수 안에서 변수를 처음 생성해서 리턴으로 새 값을 만드는 거.
	node* tmp;
	tmp = (node*)malloc(sizeof(node));
	tmp->link = NULL;

	printf("학생 이름 입력 : ");
	scanf("%s", tmp->name);
	printf("%s 학생 나이 입력 : ", tmp->name);
	scanf("%d", &tmp->age);
	printf("%s 학생 주소 입력 : ", tmp->name);
	scanf("%s", tmp->add);
	printf("%s 학생 국어 입력 : ", tmp->name);
	scanf("%d", &tmp->kor);
	printf("%s 학생  영어 입력 : ", tmp->name);
	scanf("%d", &tmp->eng);
	printf("%s 학생 수학 입력 : ", tmp->name);
	scanf("%d", &tmp->mat);
	SetGrade(tmp);
	return tmp;
}

node* insert(node* head) {
	if (head == NULL)
		return get_node(); //바로 리턴 받아버림
	head->link = insert(head->link);
	return head;
}

void ShowStudent(node* head)
{
	printf("========================\n");
	printf("학생 이름 : %s\n", head->name);
	printf("학생 나이 : %d 세\n", head->age);
	printf("학생 주소 : %s\n", head->add);
	printf("국어 점수 : %d\n", head->kor);
	printf("수학 점수 : %d\n", head->mat);
	printf("합계 점수 : %d\n", head->sum);
	printf("평균 점수 : %.2f\n", head->abs);
	printf("등급 : %c\n", head->grade);
}

node* search(node* head, char* name)
{
	system("cls");
	if (head == NULL)
	{
		printf("찾는학생 없음 \n");
		return NULL;
	}
	if (strcmp(head->name, name) == 0)
	{
		printf("정보 검색 완료\n");
		ShowStudent(head);
		return head;
	}
	return search(head->link, name); //재귀 돌려서 찾음.
}

void print(node* head)
{
	if (head == NULL)
	{
		printf("\n<학생 개개인의 점수는 검색을 이용하세요 !!>\n");
		return;
	}
	else
	{//%10s?? //띄어쓰기 몇개인지.칸 잡아두는용
		printf("%10s%10d%10s\n", head->name, head->age, head->add);
	}
	print(head->link);
}

void modify(node* head, char* name)
{
	int i, ag;
	char na[20], ad[20];
	head = search(head, name);
	if (head != NULL)
	{
		while (1)
		{
			system("cls");
			printf("수정할 항목을 선택 하시오 \n");
			printf("1.이름\t2.나이\t3.주소\t4.점수\t5.수정종료\n선택 : ");
			scanf("%d", &i);
			switch (i)
			{
			case 1:
				printf("현재 이름 : %s\n", head->name);
				strcpy(na, head->name);
				printf("수정할 이름 : ");
				scanf("%s", head->name);
				printf("%s -> %s 로 이름 수정 완료\n", na, head->name);
				break;
			case 2:
				printf("현재 나이 : %d\n", head->age);
				ag = head->age;
				printf("수정할 나이 : ");
				scanf("%d", &head->age);
				printf("%d -> %d 로 이름 수정 완료\n", ag, head->age);
				break;
			case 3:
				printf("현재 주소 : %s\n", head->add);
				strcpy(ad, head->add);
				printf("수정할 주소 : ");
				scanf("%s", head->add);
				printf("%s -> %s 로 주소 수정 완료\n", ad, head->add);
				break;
			case 4:
				printf("현재 점수\n");
				printf("국어 : %d\t영어 : %d\t수학 : %d\n", head->kor, head->eng, head->mat);
				printf("수정할 국어 점수 : ");
				scanf("%d", &(head->kor));
				printf("수정할 영어 점수 : ");
				scanf("%d", &head->eng);
				printf("수정할 수학 점수 : ");
				scanf("%d", &head->mat);
				SetGrade(head);

				printf("점수 수정 완료\n");
				break;
			case 5:
				printf("수정을 종료합니다\n");
				return;
			}
			system("pause");
		}
	}
}
node* del(node* head, char* name)
{
	if (head == NULL)
	{
		printf("삭제할 사람 없음 \n");
		return NULL;
	}
	if (strcmp(head->name, name) == 0)
	{
		node* tmp = head; //? tmp로 받는 이유? 하나하나 지우는 것도 동적할당 해제 필요
		head = head->link;
		free(tmp);
		printf("삭제완료\n");
		return head;
	}
	head->link = del(head->link, name);
	return head;
}

void Release(node* Node)
{
	if (Node == NULL)
		return;
	Release(Node->link);
	free(Node);
}

void main() {
	node* head = 0;
	int i; //메뉴 선택
	char name[20];
	while (1) {
		system("cls");
		printf("< < < = = = = 메뉴 = = = = > > >\n\n");
		printf("1.학생 등록\n");
		printf("2.학생 검색\n");
		printf("3.학생 목록\n");
		printf("4.학생 수정\n");
		printf("5.학생 삭제\n");
		printf("6.종     료\n");
		printf("선  택 : ");
		scanf("%d", &i);
		switch (i) {
		case 1:
			head = insert(head);
			break;
		case 2:
			printf("학생 이름 입력 : ");
			scanf("%s", name);
			search(head, name); //함수 밖에서는 리턴값 사용 자유. 필수 아님
			break;
		case 3:
			printf("%10s%10s%10s\n", "학생이름", "학생나이", "학생주소");
			print(head);
			break;
		case 4:
			printf("수정할 학생 이름 : ");
			scanf("%s", name);
			modify(head, name);
			break;
		case 5:
			printf("학생 이름 입력 : ");
			scanf("%s", name);
			head = del(head, name);
			break;
		case 6:
			Release(head);
			return;
		}
		system("pause");
	}
}