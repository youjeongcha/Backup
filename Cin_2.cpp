#include<iostream>
//�Է� ���۴� \n�� ������ �Էµ� ������ �Է� ���� �������� ��������
//space�� \n�� �ܾ �ϳ��� �Ǵ�(scanf�� cin ����)
//�� ���� ���X
//�ѹ� cin�Ŀ� ���� cin ����
//��
//��������
void main()
{
	char name[20];
	std::cout << "�̸��� �Է��ϼ���! ";
	std::cin >> name;
	std::cout << "���� �̸��� " << name << "�Դϴ�." << std::endl;
	std::cin >> name;
	std::cout << "���� �̸��� " << name << "�Դϴ�." << std::endl;
	return;
}