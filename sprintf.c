#include <stdio.h>

void main()
{
	char buf[40];
	int age = 20;
	char Name[10] = "������";
	sprintf(buf, "%s���� ���̴� %d���Դϴ�.", Name, age);
	//sprintf�� printf�� ������
	//sprintf ������ ���ڿ� ����
	printf("%s", buf);

}