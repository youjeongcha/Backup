#include"PhoneNumber.h"

void PhoneNumber::AddDash(int first, int second)
{
	//string* tmp = new string;//[length]; //�����Ҵ� 
	//lenght�� ����� 0�� ���´�. > string�� char�� �ٸ��� ���� ����
	//stirng���� �� ������ ����.
	//���� �ϳ��ϳ��� string���� �����ؼ� string �迭�μ�
	//�����Ҵ絵 �� ������ ����.

	string tmp;
	int j = 0;

	for (int i = 0; ph.length() > i; i++)//j���⿡ ���Ե� ����.
	{
		if (i + j == first || i + j == second)
		{
			tmp += "-";
			j++;
		}
		tmp += ph[i];
	}
	setDPh(tmp);
}

void PhoneNumber::Main()
{
	while (true)
	{
		cout << "��ȭ��ȣ �Է� : ";
		cin >> ph;
		if (ph.length() == EOUL_LEN || ph.length() == AREA_LEN || ph.length() == MPH_LEN)//9(����)//10(����)//11(�޴���)
		{
			if ((ph.length() == EOUL_LEN) && (ph[1] == '2'))
			{
				AddDash(2, 6);
				return;
			}
			else if ((ph.length() == AREA_LEN) && (ph[1] == '3' || ph[1] == '4' || ph[1] == '5' || ph[1] == '6'))
			{
				AddDash(3, 7);
				return;
			}
			else if ((ph.length() == MPH_LEN) && (ph[1] == '1'))
			{
				AddDash(3, 8);
				return;
			} 
		}
		cout << "��ȣ�� �߸� �Է��ϼ̽��ϴ�.\n";
		system("pause");
		system("cls");
	}
}
