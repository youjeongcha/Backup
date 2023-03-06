#include "EvilPlantOwnedStates.h"
#include "EntityNames.h"
#include "ConsoleUtils.h"
#include <time.h>


//void PrintState::PrintSaved(std::string ID, int blood, int magi)
//{
//	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
//	std::cout << ID << " : [���� : " + std::to_string(blood) + "  �� : " + std::to_string(magi) + "]" << std::endl;
//	SetTextColor(FOREGROUND_INTENSITY);
//}

//�޽ı�
//------------------------------------------------------------------------
BreakTime* BreakTime::Instance()
{//static���� �����ؼ� �Լ��� ������reutrn �ص� ��ü�� ������ static���� �����ִ�.
	static BreakTime instance;
	return &instance;
}

void BreakTime::Enter(EvilPlant* pEvilPlant)
{
	m_Sec = 3;
	m_OldClock = clock();
	pEvilPlant->RestSetting(true);

	std::cout << std::endl << GetNameOfEntity(pEvilPlant->ID()) << " : �޽ı⿡ ���." << std::endl;
}

void BreakTime::Excute(EvilPlant* pEvilPlant)
{
	if (!pEvilPlant->LiveCheck())
	{
		pEvilPlant->DeathSetting();
		std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : ����������� �ø��ø� �δٰ� �����Ʋ���� �׾���ȴ�." << std::endl << std::endl;
		return;
	}

	//������ ������ Ȯ�� 30%
	if (!m_Sec) //�� m_Sec == 0�� ���� ���X ���ϼ� ��Ű��
	{
		//���� 5�� �ΰ� �޽ı� Ǯ�� ���� bool�� false
		if (pEvilPlant->MaxFruitRestCheck())
			pEvilPlant->MaxFruitRestSetting(false);

		//Ǯ�� ���� ���̶��� ������ üũ�ؾ� �Ѵ�.
		if (pEvilPlant->ProuduceFruitCheck())
		{//���� �α� ����
			pEvilPlant->ChangeState(MakeFruit::Instance());
		}//ChangeState �Լ��� �� ���� ����� �ٽ� ���ƿ´�. �̰��ϰ� ���� ���ǿ� �ɸ���, ���� ������ ����
		else
		{//else�� �ȿ� �� ������ MakeFruit Enter->Exit ����ȴ�.
			pEvilPlant->ChangeState(DetectAnimal::Instance());
		}

		//if (pEvilPlant->LiveCheck())
		//{ //�޽ı� ���� �� ���������
		//	if (pEvilPlant->ProuduceFruitCheck())
		//	{//���� �α� ����
		//		pEvilPlant->ChangeState(MakeFruit::Instance());
		//	}//ChangeState �Լ��� �� ���� ����� �ٽ� ���ƿ´�. �̰��ϰ� ���� ���ǿ� �ɸ���, ���� ������ ����
		//	else
		//	{//else�� �ȿ� �� ������ MakeFruit Enter->Exit ����ȴ�.
		//		pEvilPlant->ChangeState(DetectAnimal::Instance());
		//	}
		//}
		//else
		//{//���� �Ұ� == ��� Ȯ��
		//	pEvilPlant->DeathSetting();
		//	std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : ����������� �ø��ø� �δٰ� �����Ʋ���� �׾���ȴ�." << std::endl << std::endl;
		//	return;
		//}
	}
	else
	{
		if (clock() - m_OldClock >= ONESEC)
		{
			if (pEvilPlant->MaxFruitRestCheck())
			{
				std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : ���Ÿ� �۶߸� �޽ı� " + std::to_string(m_Sec--) + "��" << std::endl;
			}
			else
			{
				std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : �޽ı� " + std::to_string(m_Sec--) + "��" << std::endl;

				//���� 5�� �ΰ� �� ���� �޽ı⿡���� ����X
				int probabilityofAppear = rand() % 10;

				//������ �������� > ���� ���
				if (probabilityofAppear >= 7) //30% Ȯ�� ���� ����
				{
					pEvilPlant->Set_AttackPossibleCheck(true);
					pEvilPlant->ChangeState(AttackMode::Instance());
				}
			}
			m_OldClock = clock();
		}
	}
}

void BreakTime::Exit(EvilPlant* pEvilPlant)
{
	//���� ���⿡�� ����� ��Ȳ�� �����Ƿ� Ž���� ���Ͱ� �ִ����� bool üũ
	//�޽ıⰡ ������ �ǵ� ���µ� ������ ����
	pEvilPlant->RestSetting(false);

	std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : �޽ı⸦ ������." << std::endl << std::endl;
	
	//if (pEvilPlant->LiveCheck()) //bool ������ ���� //��� Ȯ��
	//{
	//	std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : �޽ı⸦ ������." << std::endl << std::endl;
	//}
	//else
	//{
	//	std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : ����������� �ø��ø� �δٰ� �����Ʋ���� �׾���ȴ�.  EPOS.cpp Exit" << std::endl << std::endl;
	//}
}



//Ž�� ���
//------------------------------------------------------------------------
DetectAnimal::DetectAnimal() 
{//Ž���� Excute�� �ٷ� �����ϱ� ������ ������ �ʱ�ȭ �ʼ� 
	m_Sec = 5;
	m_OldClock = -1000; //�������ڸ��� 1�� ī��Ʈ �ȵǾ ���� ��� ���� �� ���� �� ����
}

DetectAnimal* DetectAnimal::Instance()
{//static���� �����ؼ� �Լ��� ������reutrn �ص� ��ü�� ������ static���� �����ִ�.
	static DetectAnimal instance;
	return &instance;
}

void DetectAnimal::Enter(EvilPlant* pEvilPlant)
{
	//1.���̰� ����
	//2.�ǰ� 2������ ��� == ���� �δ� ���� �ƴ� ���
	m_Sec = 5;
	m_OldClock = clock();
	
	std::cout << std::endl << GetNameOfEntity(pEvilPlant->ID()) << " : �������� �����ϴ� ��⸦ ���մ´�." << std::endl;
}

void DetectAnimal::Excute(EvilPlant* pEvilPlant)
{//������ ������ Ȯ�� 50%

	if (pEvilPlant->LiveCheck())
	{
		//Ž����
		if (clock() - m_OldClock >= ONESEC)
		{
			int probabilityofAppear = rand() % 10; //0 ~ 9

			std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : ��Ȥ�� " + std::to_string(m_Sec--) + "��" << std::endl;
			m_OldClock = clock();

			//Ž�� ���� > ���� ���� > �� �̱�
			if (probabilityofAppear >= 5) //50% Ȯ�� ���� ����
			{
				pEvilPlant->CaptiveAnimal(); //100% Ȯ�� ��ȹ
				pEvilPlant->ChangeState(DrawBlood::Instance());
			}
		}

		//Ž�� ���� > �޽ı�(�������)
		if (!m_Sec) //�� m_Sec == 0�� ���� ���X ���ϼ� ��Ű��
			pEvilPlant->ChangeState(BreakTime::Instance());
	}
	else
	{//���� �Ұ� == ��� Ȯ��
		pEvilPlant->DeathSetting();
		std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : ����������� �ø��ø� �δٰ� �����Ʋ���� �׾���ȴ�." << std::endl << std::endl;
		return;
	}
}

void DetectAnimal::Exit(EvilPlant* pEvilPlant)
{
	//�޽ıⰡ ������ �ǵ� ���µ� ������ ����
	if (pEvilPlant->CaptiveAnimalCheck())
		std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : ���� �ð� ã�ƿ� ���̸� �����Ҵ�." << std::endl << std::endl;
	else
		std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : �������� ���̰� ����." << std::endl << std::endl;
}



//���� ���
//------------------------------------------------------------------------
AttackMode* AttackMode::Instance()
{//static���� �����ؼ� �Լ��� ������reutrn �ص� ��ü�� ������ static���� �����ִ�.
	static AttackMode instance;
	return &instance;
}

void AttackMode::Enter(EvilPlant* pEvilPlant)
{
	// �� �̴� �߿� ���� �� ������ ����X. �񼱰� ����. �ΰ��� ���� �����ϸ� ����. ������ �ش� �ڵ忡���� �Ĺ��� ���� �����ϴ� ������ ������.
	std::cout << std::endl << GetNameOfEntity(pEvilPlant->ID()) << " : �������� ���̸� �����Ѵ�." << std::endl;
}

void AttackMode::Excute(EvilPlant* pEvilPlant)
{
	if (pEvilPlant->LiveCheck())
	{
		int captivePercent = rand() % 10; //������ ���� ��ȹ Ȯ�� 80%

		if (captivePercent >= 2)
		{//��ȹ ����
			pEvilPlant->CaptiveAnimal();
			pEvilPlant->ChangeState(DrawBlood::Instance());
		}//��ȹ ���� v
		else if (pEvilPlant->ProuduceFruitCheck())
		{//���� �α� ����
			pEvilPlant->ChangeState(MakeFruit::Instance());
		}
		else if (pEvilPlant->LackBlood())
		{//�޽ı�
			pEvilPlant->ChangeState(BreakTime::Instance());
		}
	}
	else
	{//���� �Ұ� == ��� Ȯ��
		pEvilPlant->DeathSetting();
		std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : ����������� �ø��ø� �δٰ� �����Ʋ���� �׾���ȴ�." << std::endl << std::endl;
		return;
	}
}

void AttackMode::Exit(EvilPlant* pEvilPlant)
{
	pEvilPlant->Set_AttackPossibleCheck(false);

	if (pEvilPlant->CaptiveAnimalCheck())
	{
		std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : ���� ����. ���̸� �����Ҵ�." << std::endl << std::endl;
	}
	else
	{
		std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : ���� ����. ���̰� �����ƴ�." << std::endl << std::endl;
	}
}


//�� �̱�
//------------------------------------------------------------------------
DrawBlood* DrawBlood::Instance()
{//static���� �����ؼ� �Լ��� ������reutrn �ص� ��ü�� ������ static���� �����ִ�.
	static DrawBlood instance;
	return &instance;
}

void DrawBlood::Enter(EvilPlant* pEvilPlant)
{
	//�Ǹ� �̴� �߿� �ΰ��� ���� ������ ���� ������� �ʴ´�.
	//�ش� �ڵ忡���� �Ĺ��� ���� �����ϴ� ��. 

	std::cout << std::endl << GetNameOfEntity(pEvilPlant->ID()) << " : ������ �Ǹ� �̴´�." << std::endl;
}

void DrawBlood::Excute(EvilPlant* pEvilPlant)
{
	pEvilPlant->DrawBlood();

	if (pEvilPlant->ProuduceFruitCheck())
	{//���� �α� ����
		pEvilPlant->ChangeState(MakeFruit::Instance());
	}
	else if (pEvilPlant->LackMagi() || pEvilPlant->LackBlood())
	{
		pEvilPlant->ChangeState(BreakTime::Instance());
	}
}

void DrawBlood::Exit(EvilPlant* pEvilPlant)
{
	std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : �Ǹ� 5 �̾Ҵ�." << std::endl;

	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : [���� : " + std::to_string(pEvilPlant->Get_Magi()) + "  �� : " + std::to_string(pEvilPlant->Get_Blood()) + "]" << std::endl;
	SetTextColor(FOREGROUND_INTENSITY);

	if (pEvilPlant->DrawBloodCheck() == false) 
	{
		std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : ���̰� ��ȭ�ƴ�." << std::endl << std::endl;
	}

	std::cout << std::endl;
}


//���� ����
//------------------------------------------------------------------------
MakeFruit* MakeFruit::Instance()
{//static���� �����ؼ� �Լ��� ������reutrn �ص� ��ü�� ������ static���� �����ִ�.
	static MakeFruit instance;
	return &instance;
}

void MakeFruit::Enter(EvilPlant* pEvilPlant)
{
	std::cout << std::endl << GetNameOfEntity(pEvilPlant->ID()) << " : ����Ҹ� �̿��� ���Ÿ� ������ �Ѵ�." << std::endl;
}

void MakeFruit::Excute(EvilPlant* pEvilPlant)
{
	if (pEvilPlant->ProuduceFruitCheck())
	{
		std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : ���Ÿ� �δ´�..." << std::endl;
		pEvilPlant->ProuduceFruit();

		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : [���� : " + std::to_string(pEvilPlant->Get_Magi()) + "  �� : " + std::to_string(pEvilPlant->Get_Blood()) + "]" << std::endl;
		SetTextColor(FOREGROUND_INTENSITY);
	}
	else
	{//�� Enter���� ���� ���� ���� ���� 3 > Update (���� -1) > ���� ���� �Ұ�.
		std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : ���Ÿ� �δµ� �ʿ��� ���Ⱑ Ȱ���� ���Ǿ� �����ϴ�." << std::endl;
	}

	if (pEvilPlant->LiveCheck())
	{
		int probabilityofAppear = rand() % 10; //������ ������ Ȯ�� 40%

		if (pEvilPlant->CountFruit() >= MAX_FRUIT)
		{//���Ű� 5�� ������ �޽ı⿡ ������.
			//std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : ���Ÿ� ������." << std::endl;
			pEvilPlant->ChangeState(BreakTime::Instance());
		}
		else if (!pEvilPlant->LackBlood() && !pEvilPlant->LackMagi())
		{//���Ÿ� ���� �� ���� ��� ��� �����.
			return;
		}
		else if (pEvilPlant->CaptiveAnimalCheck())
		{
			pEvilPlant->ChangeState(DrawBlood::Instance());
		}
		else if (probabilityofAppear >= 6) //40%
		{//������ ������ ��� ���� ��� ��ȯ
			pEvilPlant->Set_AttackPossibleCheck(true);
			pEvilPlant->ChangeState(AttackMode::Instance());
		}
		else if (pEvilPlant->LackBlood() || pEvilPlant->LackMagi())
		{//�޽ı�
			pEvilPlant->ChangeState(BreakTime::Instance());
		}
	}
	else
	{//���� �Ұ� == ��� Ȯ��
		pEvilPlant->DeathSetting();
		std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : ����������� �ø��ø� �δٰ� �����Ʋ���� �׾���ȴ�." << std::endl << std::endl;
		return;
	}
}

void MakeFruit::Exit(EvilPlant* pEvilPlant)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : [�����ִ� ���Ŵ� " + std::to_string(pEvilPlant->CountFruit()) + "��]" << std::endl;
	

	if (pEvilPlant->CountFruit() >= MAX_FRUIT)
	{ //���� 5���� �������� ��쿡�� 0�� �� �ִ�.
		pEvilPlant->DropFruit();
		pEvilPlant->MaxFruitRestSetting(true);

		std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : ���Ÿ� 5���� �۶߷ȴ�." << std::endl;

		std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : [�����ִ� ���Ŵ� " + std::to_string(pEvilPlant->CountFruit()) + "��]" << std::endl;
	}

	SetTextColor(FOREGROUND_INTENSITY);
	std::cout << std::endl;
}