#include<stdio.h>
//fprintf "a" �ɼ�
void main()
{
	//FILE* f = fopen("c:\\test\\Test.txt", "a"); ����̺� ��ü�� �ٸ� ���
	FILE* f = fopen("Test.txt", "a");
	int Num = 123;
	fprintf(f, "�߰� ��� %d", Num);
	fclose(f);

	//��ΰ� �ٸ� �ÿ��� 
}