#include <stdio.h>
#include <Windows.h>

//Sleep �Լ�
//���� ���α׷��� Millisecond ������ ��� �����.
//�ʿ� ������� <Windows.h>
int main()
{
	while (1)
	{
		system("cls");
		printf("��ȭ �Ŵ��� ��");
		for (int i = 0; i < 3; i++)
		{
			Sleep(1000);
			printf(".");
		}
		Sleep(1000);
	}

	return 0;
}