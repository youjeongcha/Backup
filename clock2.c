#include <stdio.h>
#include <Windows.h>
#include <time.h>
//clock[] �Լ�
//���� ���α׷��� ������ �� ����� �ð��� �����ִ� �Լ� <time.h
//sleep �� ���α׷� ��ü�� ��������� �ð�üũ�� ����

#define SEC 1000

int main()
{
	printf("��ȭ �Ŵ��� ��");
	int oldClock = clock(); //���α׷��� ������ �������� �ʸ� ���� �����Ѵ�.
							//clock()���� ������ �޾Ƽ�
	int count = 0; 
	while (count <= 3)
	{
		if (clock() - oldClock >= SEC) //���� clock���� ������ ũ�� 
									   //oldClock�� 1�̶�� clock()�� 1001�� �Ǿ��� ������ ����
		{
			count++;
			printf(".");
			oldClock = clock(); //if���� ����� �������κ��� �ٽ� ������ �Ǿ
		}
	}
	return 0;
}