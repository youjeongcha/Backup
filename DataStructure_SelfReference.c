#include <stdio.h>
#include <Windows.h> //system("cls");
#include <stdlib.h> //동적할당 malloc

typedef struct Point
{
	int number;
	int x, y;
	struct Point* Next; //next의 주소 *Point로 하면 이중 포인터 //구조체라는 형식명과 구조체 이름을 하나로 취급
}Point;

void Menu(int icount)
{
	printf("좌표 갯수 = %d\n", icount);
	printf("1.좌표추가\n");
	printf("2.좌표보기\n");
	printf("3.종료\n");
	printf("입력 = ");
}

void Release(Point* Node)
{//1234321로 돌아오는 구조라서 4부터 동적할당 해제. 1먼저 하면 뒤에 주소 다 날라감
	if (Node == NULL)
		return;
	Release(Node->Next); //1234로 들어감

	printf("%d번째 좌표 메모리 해제\n", Node->number);
	free(Node); //4321나오는 길에 해제
}

Point* Insert(Point* pt, int count) //함수 선언을 구조체로 하고 *포인터 붙이는거 - 포인터로 받는 거 맞고 Next는 이중 포인터?
{//★반환자료형으로 리턴을 받기 때문에★ Point* pt를 받기 위해서는 동일해야 함
	if (pt == NULL)
	{
		pt = (Point*)malloc(sizeof(Point)); //동적할당을 매 좌표마다
		printf("x = ");
		scanf("%d", &pt->x); //&pt->x는 주소에 받는 것 원래 인자는 주소를 지정해서 받는다.
		printf("y = ");
		scanf("%d", &pt->y);
		pt->number = count;
		pt->Next = NULL; //다음 pt의 주소에 있는 쓰레기 값을 비워준다
	}
	else //next로 다음 pt의 주소를 연결하는데. 이전에 입력받은 주소가 있으면 다음 주소로 넘어가는 코드
		pt->Next = Insert(pt->Next, count);
	return pt;
}

void Print(Point* pt)
{
	if (pt == NULL)
		return;
	printf("%d번째 좌표\nx = %d\ny = %d\n", pt->number, pt->x, pt->y);
	printf("=======================\n\n");
	Print(pt->Next);
}

void main()
{
	int icount = 0; //좌표의 수
	int num;
	Point* pt = NULL; //좌표 생성 //Point 이름으로 받는 것 주의
	while (1)
	{
		system("cls");
		Menu(icount);
		scanf("%d", &num);
		switch (num)
		{
		case 1: //좌표 추가
			icount++;
			pt = Insert(pt, icount);
			break;
		case 2: //좌표보기
			Print(pt);
			system("pause");
			break;
		case 3: //종료
			Release(pt);
			return;
		}
	}
}

/* 31번째 줄
count 1
1의 next에 null

count12
1의 next에 2의 주소
2의 next에 null

재귀함수 들어갔다 나오는거
123이렇게 들어가서 마지막에 next가 비어있는 null이 나오면
if문으로 들어가서 리턴 받고
재귀함수 풀면서 나오는데
3에 null
2에 3의 주소
1에 2의 주소를
return으로 받으면서 나온다.*/