#include <stdio.h>
#include <Windows.h>
#include <time.h>
//clock[] �Լ�
//���� ���α׷��� ������ �� ����� �ð��� �����ִ� �Լ� <time.h>
//sleep �� ���α׷� ��ü�� ��������� �ð�üũ�� ����

#define SEC 1000
#define MAX_COUNT 3

int main()
{
	printf("��ȭ �Ŵ��� ��");
	int oldClock = clock();
	int count = 0;
	while (count <= MAX_COUNT)
	{
		if (clock() - oldClock >= SEC)
		{
			count++;
			if (count > MAX_COUNT)
			{
				count = 0;
				system("cls");
				printf("��ȭ �Ŵ��� ��");
			}
			else
			{
				printf(".");
			}
			oldClock = clock();
		}
	}
}