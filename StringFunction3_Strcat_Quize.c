//���ڿ� �Լ� 
//Strcat ���ڿ��� �߰����ִ� �Լ�
#include <stdio.h>
#include <string.h>

void Strcat(char* str, char* add)
{//for ���Ƽ� null ���� ã��
	//if��  null�̸� �ٸ� ���� null�� ã��
	int endStr = 1, endAdd = 1;
	for (int  i = 0; str[i] != NULL; i++)
	{
		if (str[endStr] == NULL)
		{
			for (int j = 0; add[j] != NULL; j++)
			{
				str[endStr + j] = add[j];
				if (add[endAdd] == NULL)
				{
					str[endStr + endAdd] = NULL;
					return;
				}
				endAdd++;
			}
		}
		endStr++;
	}

	//int len = strlen(str);
	//int empty = 0;
	//for (int i = 0; add[i] != NULL; i++)
	//{
	//	str[len + i] = add[i]; 
	//	empty++;
	//}
	//str[len + empty] = NULL; //�߰��ϴ� �� ���� �� �� �ϳ��� �ε��� 0�� ����Ѵ�

}

void main()
{
	char str[20] = "Hello";
	char add[10] = "^^";
	printf("%s\n", str);
	//strcat(str, "^^");
	Strcat(str, add);
	printf("%s\n", str);
}