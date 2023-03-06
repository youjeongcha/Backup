#pragma once
#include "BaseGameEntity.h"

#define ORIGINAL 0x0007

//�ð�
#define NIGHTTIME 10000 //0~10000
#define DAYTIME 20000 //10001~20000

//���差
#define MAX_BLOOD 10 //�ִ� ���� ��
#define MAX_MAGI 10 //�ִ� ���� ����
#define MAX_FRUIT 5 //�δ� ������ ��(5�� ������ ����)

//����
#define BLOOD_OFPRODUCING_FRUIT 3 //������ �����ϴµ� �ʿ��� ��
#define MAGI_OFPRODUCING_FRUIT 3 //������ �����ϴµ� �ʿ��� ����

//Ž��
#define DETECTING_BLOOD 2 //Ž���� �����ϴ� ���� ��

//���� �� �̱�
#define BLOODDRAW_COUNT 3 //���̿��� �� ȸ �Ǹ� ���� �� �ִ°�
#define BLOODDRAW 5 //���̿��� �ѹ��� ���� �� �ִ� ��

class EvilPlant;
class State
{
public:
	virtual ~State() {}

	virtual void Enter(EvilPlant*) abstract;
	virtual void Excute(EvilPlant*) abstract;
	virtual void Exit(EvilPlant*) abstract;
};

class EvilPlant : public BaseGameEntity
{
private:
	State* m_CurrState;

	//������ ��
	int m_SavedBlood; 
	//������ ����
	int m_SavedMagi;
	//�����ִ� ����
	int m_Fruit;

	//���� ���� ������ �ɸ� ������ �ִ���
	bool m_AttackPossibleCheck;
	//������� ������ �ִ��� Ȯ��
	bool m_CaptiveAnimalCheck;
	//���� ���� �������Լ� �� ���� �� �ִ� Ƚ�� //�ΰ�, ���� ���� 
	int m_AnimalBlood_Count;

	//�޽ı� üũ
	bool m_RestCheck;
	//���� �ΰ� �� �޽ı� Ǯ�� ����
	bool m_MaxFruitRestCheck;

	//���� üũ
	bool m_LiveCheck;

	//���� �α� ���� üũ
	bool m_ProuduceFruitCheck;

public:
	EvilPlant(const int& id);
	virtual ~EvilPlant() {}

	bool Update() override;
	void ChangeState(State*);

	//��
	//void AddBlood(const int& value);
	bool LackBlood() const;
	bool EmptyBlood() const;
	int Get_Blood() const { return m_SavedBlood; }

	//����
	bool EmptyMagiCheck() const;
	bool LackMagi() const;
	int Get_Magi() const { return m_SavedMagi; }

	//���� ������ ������ ���� �ִ��� bool ����
	void Set_AttackPossibleCheck(const bool& value);
	bool AttackPossibleCheck() const { return m_AttackPossibleCheck; }

	//���� ����
	void CaptiveAnimal();
	//������� ���̰� �ִ��� Ȯ��
	bool CaptiveAnimalCheck() const { return m_CaptiveAnimalCheck; }
	//������ �Ǹ� ���� �� �ִ��� + ������ ���� ���� false ��ȯ
	bool DrawBloodCheck();
	//���� �� �̱�
	void DrawBlood();
	
	//���� ���� ���� ���� + ����
	bool ProuduceFruitCheck();
	//����3, ��3���� ���Ÿ� �����
	void ProuduceFruit();
	//������ �ִ� ������ ������ ����
	int CountFruit() const { return m_Fruit; }
	//5���� ���ִ��� Ȯ��
	bool MaxFruit() const;
	//���Ÿ� ������.
	void DropFruit() { m_Fruit = 0; }

	//�޽ı� ����
	void RestSetting(const bool& value) { m_RestCheck = value; }
	//�޽ı� ���� üũ
	bool RestCheck() const { return m_RestCheck; }
	//���� 5�� �޽ı� ���� or ����
	void MaxFruitRestSetting(const bool& value) { m_MaxFruitRestCheck = value; }
	//���� 5�� �޽ı� Ǯ üũ
	bool MaxFruitRestCheck() const { return m_MaxFruitRestCheck; }
	
	//���� üũ ��� �Լ� ���� ����
	void DeathSetting() { m_LiveCheck = false; };
	//���� üũ ��� �Լ� ����
	bool LiveCheck() const { return m_LiveCheck; };
};

