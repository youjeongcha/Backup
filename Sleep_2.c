#include <stdio.h>
#include <Windows.h>

//Sleep �Լ�
//���� ���α׷��� Millisecond ������ ��� �����.
//�ʿ� ������� <Windows.h>
int main()
{
	printf("��ȭ �Ŵ��� ��");
	for (int i = 0; i < 3; i++)
	{
		Sleep(1000); //1000�� 1�� 500�̸� 0.5��
		printf(".");
	}
	Sleep(1000); //����Ǳ� ������ 1��

	return 0;
}