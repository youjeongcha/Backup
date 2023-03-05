#include<iostream>
#include<Windows.h>
using namespace std;

enum PLAYER
{
	PLAYER_START = 1,
	PLAYER_ARCHER = 1,
	PLAYER_MAGICIAN,
	PLAYER_WARRIOR,
	PLAYER_END = PLAYER_WARRIOR //������
};

enum PLAYPATTERN
{
	PLAYPATTERN_ATTACK = 1,
	PLAYPATTERN_MOVE,
	PLAYPATTERN_DEFENCE
};

struct Player
{
	PLAYER PlayerType;
	int Damage;
	int Speed;
	int Defend;
};

void Attack(Player p)
{
	switch (p.PlayerType)
	{
	case PLAYER_ARCHER:
		cout << "�ü��� ���Ÿ����� ȭ�����!(������:" << p.Damage << "(" << endl;
		break;
	case PLAYER_MAGICIAN:
		cout << "�����簡 ���Ÿ����� ��������!(������:" << p.Damage << "(" << endl;
		break;
	case PLAYER_WARRIOR:
		cout << "���簡 �ٰŸ����� ��������!(������:" << p.Damage << "(" << endl;
		break;
	}
}

void Move(Player p)
{
	switch (p.PlayerType)
	{
	case PLAYER_ARCHER:
		cout << "�ü��� �����Ͽ� �̵�(�̵��ӵ� :" << p.Speed << ")" << endl;
		break;
	case PLAYER_MAGICIAN:
		cout << "�����簡 �ڷ���Ʈ�Ͽ� �̵�(�̵��ӵ� :" << p.Speed << ")" << endl;
		break;
	case PLAYER_WARRIOR:
		cout << "���簡 �����Ͽ� �̵�(�̵��ӵ� :" << p.Speed << ")" << endl;
		break;
	}
}

void Defence(Player p)
{
	switch (p.PlayerType)
	{
	case PLAYER_ARCHER:
		cout << "�ü��� Ȱ���� ����Ͽ� ���(��ⵥ���� :" << p.Defend << ")" << endl;
		break;
	case PLAYER_MAGICIAN:
		cout << "�����簡 �������� ����Ͽ� ���(��ⵥ���� :" << p.Defend << ")" << endl;
		break;
	case PLAYER_WARRIOR:
		cout << "���簡 ���и� ����Ͽ� ���(��ⵥ���� :" << p.Defend << ")" << endl;
		break;
	}
}

void main()
{
	Player player;
	int Choice;
	while (1)
	{
		system("cls");
		cout << "=====���� ����=====" << endl;
		cout << "  1.�ü�" << endl;
		cout << "  2.������" << endl;
		cout << "  3.����" << endl;
		cout << "���� : ";
		cin >> Choice;
		if (Choice >= PLAYER_START && Choice <= PLAYER_END)
		{
			player.PlayerType = (PLAYER)Choice;
			break;
		}
		//PLAYER �� �ش� �� �ϸ�
		cout << "������ �߸� ���� �ϼ˽��ϴ�." << endl;
		system("pause");
	}
	switch (player.PlayerType)
	{
	case PLAYER_ARCHER:
		player.Damage = 50;
		player.Defend = 10;
		player.Speed = 50;
		break;
	case PLAYER_MAGICIAN:
		player.Damage = 100;
		player.Defend = 5;
		player.Speed = 30;
		break;
	case PLAYER_WARRIOR:
		player.Damage = 30;
		player.Defend = 20;
		player.Speed = 20;
		break;
	}
	while (1)
	{
		system("cls");
		cout << "=====�ൿ ����=====" << endl;
		cout << "  1.����" << endl;
		cout << "  2.�̵�" << endl;
		cout << "  3.���" << endl;
		cout << "���� : ";
		cin >> Choice;
		switch (Choice)
		{
		case PLAYPATTERN_ATTACK:
			Attack(player);
			break;
		case PLAYPATTERN_MOVE:
			Move(player);
			break;
		case PLAYPATTERN_DEFENCE:
			Defence(player);
			break;
		default:
			cout << "�߸� ���� �ϼ˽��ϴ�." << endl;
			break;
		}
		system("pause");
	}
}