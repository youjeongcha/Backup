#include "EvilPlantOwnedStates.h"
#include "EntityNames.h"
#include "ConsoleUtils.h"
#include <time.h>


//void PrintState::PrintSaved(std::string ID, int blood, int magi)
//{
//	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
//	std::cout << ID << " : [마기 : " + std::to_string(blood) + "  피 : " + std::to_string(magi) + "]" << std::endl;
//	SetTextColor(FOREGROUND_INTENSITY);
//}

//휴식기
//------------------------------------------------------------------------
BreakTime* BreakTime::Instance()
{//static으로 선언해서 함수가 끝나고reutrn 해도 객체가 여전히 static으로 남아있다.
	static BreakTime instance;
	return &instance;
}

void BreakTime::Enter(EvilPlant* pEvilPlant)
{
	m_Sec = 3;
	m_OldClock = clock();
	pEvilPlant->RestSetting(true);

	std::cout << std::endl << GetNameOfEntity(pEvilPlant->ID()) << " : 휴식기에 든다." << std::endl;
}

void BreakTime::Excute(EvilPlant* pEvilPlant)
{
	if (!pEvilPlant->LiveCheck())
	{
		pEvilPlant->DeathSetting();
		std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : 영양부족으로 시름시름 앓다가 말라비틀어져 죽어버렸다." << std::endl << std::endl;
		return;
	}

	//동물이 지나갈 확률 30%
	if (!m_Sec) //★ m_Sec == 0와 병행 사용X 통일성 지키기
	{
		//열매 5개 맺고 휴식기 풀로 쉬는 bool값 false
		if (pEvilPlant->MaxFruitRestCheck())
			pEvilPlant->MaxFruitRestSetting(false);

		//풀로 쉬는 값이랑은 별도로 체크해야 한다.
		if (pEvilPlant->ProuduceFruitCheck())
		{//열매 맺기 가능
			pEvilPlant->ChangeState(MakeFruit::Instance());
		}//ChangeState 함수를 다 돌고 여기로 다시 돌아온다. 이걸하고 다음 조건에 걸리면, 다음 조건이 실행
		else
		{//else문 안에 안 넣으면 MakeFruit Enter->Exit 실행된다.
			pEvilPlant->ChangeState(DetectAnimal::Instance());
		}

		//if (pEvilPlant->LiveCheck())
		//{ //휴식기 끝난 후 살아있으면
		//	if (pEvilPlant->ProuduceFruitCheck())
		//	{//열매 맺기 가능
		//		pEvilPlant->ChangeState(MakeFruit::Instance());
		//	}//ChangeState 함수를 다 돌고 여기로 다시 돌아온다. 이걸하고 다음 조건에 걸리면, 다음 조건이 실행
		//	else
		//	{//else문 안에 안 넣으면 MakeFruit Enter->Exit 실행된다.
		//		pEvilPlant->ChangeState(DetectAnimal::Instance());
		//	}
		//}
		//else
		//{//생존 불가 == 사망 확정
		//	pEvilPlant->DeathSetting();
		//	std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : 영양부족으로 시름시름 앓다가 말라비틀어져 죽어버렸다." << std::endl << std::endl;
		//	return;
		//}
	}
	else
	{
		if (clock() - m_OldClock >= ONESEC)
		{
			if (pEvilPlant->MaxFruitRestCheck())
			{
				std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : 열매를 퍼뜨린 휴식기 " + std::to_string(m_Sec--) + "초" << std::endl;
			}
			else
			{
				std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : 휴식기 " + std::to_string(m_Sec--) + "초" << std::endl;

				//열매 5개 맺고 난 뒤의 휴식기에서는 실행X
				int probabilityofAppear = rand() % 10;

				//동물이 지나가면 > 공격 모드
				if (probabilityofAppear >= 7) //30% 확률 동물 등장
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
	//죽을 위기에서 벗어나는 상황이 있으므로 탐지된 몬스터가 있는지도 bool 체크
	//휴식기가 지나고 피도 마력도 없으면 죽음
	pEvilPlant->RestSetting(false);

	std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : 휴식기를 끝낸다." << std::endl << std::endl;
	
	//if (pEvilPlant->LiveCheck()) //bool 변경후 리턴 //사망 확정
	//{
	//	std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : 휴식기를 끝낸다." << std::endl << std::endl;
	//}
	//else
	//{
	//	std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : 영양부족으로 시름시름 앓다가 말라비틀어져 죽어버렸다.  EPOS.cpp Exit" << std::endl << std::endl;
	//}
}



//탐색 모드
//------------------------------------------------------------------------
DetectAnimal::DetectAnimal() 
{//탐지의 Excute로 바로 시작하기 때문에 생성자 초기화 필수 
	m_Sec = 5;
	m_OldClock = -1000; //시작하자마자 1초 카운트 안되어서 상태 출력 한턴 더 도는 걸 방지
}

DetectAnimal* DetectAnimal::Instance()
{//static으로 선언해서 함수가 끝나고reutrn 해도 객체가 여전히 static으로 남아있다.
	static DetectAnimal instance;
	return &instance;
}

void DetectAnimal::Enter(EvilPlant* pEvilPlant)
{
	//1.먹이가 없고
	//2.피가 2이하인 경우 == 열매 맺는 중이 아닌 경우
	m_Sec = 5;
	m_OldClock = clock();
	
	std::cout << std::endl << GetNameOfEntity(pEvilPlant->ID()) << " : 동물들이 좋아하는 향기를 내뿜는다." << std::endl;
}

void DetectAnimal::Excute(EvilPlant* pEvilPlant)
{//동물이 지나갈 확률 50%

	if (pEvilPlant->LiveCheck())
	{
		//탐지중
		if (clock() - m_OldClock >= ONESEC)
		{
			int probabilityofAppear = rand() % 10; //0 ~ 9

			std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : 현혹중 " + std::to_string(m_Sec--) + "초" << std::endl;
			m_OldClock = clock();

			//탐지 성공 > 동물 잡음 > 피 뽑기
			if (probabilityofAppear >= 5) //50% 확률 동물 등장
			{
				pEvilPlant->CaptiveAnimal(); //100% 확률 포획
				pEvilPlant->ChangeState(DrawBlood::Instance());
			}
		}

		//탐지 실패 > 휴식기(가사상태)
		if (!m_Sec) //★ m_Sec == 0와 병행 사용X 통일성 지키기
			pEvilPlant->ChangeState(BreakTime::Instance());
	}
	else
	{//생존 불가 == 사망 확정
		pEvilPlant->DeathSetting();
		std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : 영양부족으로 시름시름 앓다가 말라비틀어져 죽어버렸다." << std::endl << std::endl;
		return;
	}
}

void DetectAnimal::Exit(EvilPlant* pEvilPlant)
{
	//휴식기가 지나고 피도 마력도 없으면 죽음
	if (pEvilPlant->CaptiveAnimalCheck())
		std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : 향을 맡고 찾아온 먹이를 사로잡았다." << std::endl << std::endl;
	else
		std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : 지나가는 먹이가 없다." << std::endl << std::endl;
}



//공격 모드
//------------------------------------------------------------------------
AttackMode* AttackMode::Instance()
{//static으로 선언해서 함수가 끝나고reutrn 해도 객체가 여전히 static으로 남아있다.
	static AttackMode instance;
	return &instance;
}

void AttackMode::Enter(EvilPlant* pEvilPlant)
{
	// 피 뽑는 중에 먹이 더 만나도 공격X. 비선공 몬스터. 인간이 먼저 공격하면 공격. 하지만 해당 코드에서는 식물이 먼저 공격하는 것으로 제한함.
	std::cout << std::endl << GetNameOfEntity(pEvilPlant->ID()) << " : 지나가는 먹이를 공격한다." << std::endl;
}

void AttackMode::Excute(EvilPlant* pEvilPlant)
{
	if (pEvilPlant->LiveCheck())
	{
		int captivePercent = rand() % 10; //공격을 통한 포획 확률 80%

		if (captivePercent >= 2)
		{//포획 성공
			pEvilPlant->CaptiveAnimal();
			pEvilPlant->ChangeState(DrawBlood::Instance());
		}//포획 실패 v
		else if (pEvilPlant->ProuduceFruitCheck())
		{//열매 맺기 가능
			pEvilPlant->ChangeState(MakeFruit::Instance());
		}
		else if (pEvilPlant->LackBlood())
		{//휴식기
			pEvilPlant->ChangeState(BreakTime::Instance());
		}
	}
	else
	{//생존 불가 == 사망 확정
		pEvilPlant->DeathSetting();
		std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : 영양부족으로 시름시름 앓다가 말라비틀어져 죽어버렸다." << std::endl << std::endl;
		return;
	}
}

void AttackMode::Exit(EvilPlant* pEvilPlant)
{
	pEvilPlant->Set_AttackPossibleCheck(false);

	if (pEvilPlant->CaptiveAnimalCheck())
	{
		std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : 공격 성공. 먹이를 사로잡았다." << std::endl << std::endl;
	}
	else
	{
		std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : 공격 실패. 먹이가 도망쳤다." << std::endl << std::endl;
	}
}


//피 뽑기
//------------------------------------------------------------------------
DrawBlood* DrawBlood::Instance()
{//static으로 선언해서 함수가 끝나고reutrn 해도 객체가 여전히 static으로 남아있다.
	static DrawBlood instance;
	return &instance;
}

void DrawBlood::Enter(EvilPlant* pEvilPlant)
{
	//피를 뽑는 중에 인간이 먼저 공격할 경우는 고려하지 않는다.
	//해당 코드에서는 식물이 먼저 공격하는 것. 

	std::cout << std::endl << GetNameOfEntity(pEvilPlant->ID()) << " : 먹이의 피를 뽑는다." << std::endl;
}

void DrawBlood::Excute(EvilPlant* pEvilPlant)
{
	pEvilPlant->DrawBlood();

	if (pEvilPlant->ProuduceFruitCheck())
	{//열매 맺기 가능
		pEvilPlant->ChangeState(MakeFruit::Instance());
	}
	else if (pEvilPlant->LackMagi() || pEvilPlant->LackBlood())
	{
		pEvilPlant->ChangeState(BreakTime::Instance());
	}
}

void DrawBlood::Exit(EvilPlant* pEvilPlant)
{
	std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : 피를 5 뽑았다." << std::endl;

	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : [마기 : " + std::to_string(pEvilPlant->Get_Magi()) + "  피 : " + std::to_string(pEvilPlant->Get_Blood()) + "]" << std::endl;
	SetTextColor(FOREGROUND_INTENSITY);

	if (pEvilPlant->DrawBloodCheck() == false) 
	{
		std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : 먹이가 소화됐다." << std::endl << std::endl;
	}

	std::cout << std::endl;
}


//열매 생성
//------------------------------------------------------------------------
MakeFruit* MakeFruit::Instance()
{//static으로 선언해서 함수가 끝나고reutrn 해도 객체가 여전히 static으로 남아있다.
	static MakeFruit instance;
	return &instance;
}

void MakeFruit::Enter(EvilPlant* pEvilPlant)
{
	std::cout << std::endl << GetNameOfEntity(pEvilPlant->ID()) << " : 영양소를 이용해 열매를 만들기로 한다." << std::endl;
}

void MakeFruit::Excute(EvilPlant* pEvilPlant)
{
	if (pEvilPlant->ProuduceFruitCheck())
	{
		std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : 열매를 맺는다..." << std::endl;
		pEvilPlant->ProuduceFruit();

		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : [마기 : " + std::to_string(pEvilPlant->Get_Magi()) + "  피 : " + std::to_string(pEvilPlant->Get_Blood()) + "]" << std::endl;
		SetTextColor(FOREGROUND_INTENSITY);
	}
	else
	{//낮 Enter에는 먹이 생성 가능 마기 3 > Update (마기 -1) > 먹이 생성 불가.
		std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : 열매를 맺는데 필요한 마기가 활동에 사용되어 부족하다." << std::endl;
	}

	if (pEvilPlant->LiveCheck())
	{
		int probabilityofAppear = rand() % 10; //동물이 지나갈 확률 40%

		if (pEvilPlant->CountFruit() >= MAX_FRUIT)
		{//열매가 5개 맺히면 휴식기에 접어든다.
			//std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : 열매를 떨군다." << std::endl;
			pEvilPlant->ChangeState(BreakTime::Instance());
		}
		else if (!pEvilPlant->LackBlood() && !pEvilPlant->LackMagi())
		{//열매를 만들 수 있을 경우 계속 만든다.
			return;
		}
		else if (pEvilPlant->CaptiveAnimalCheck())
		{
			pEvilPlant->ChangeState(DrawBlood::Instance());
		}
		else if (probabilityofAppear >= 6) //40%
		{//동물이 지나갈 경우 공격 모드 전환
			pEvilPlant->Set_AttackPossibleCheck(true);
			pEvilPlant->ChangeState(AttackMode::Instance());
		}
		else if (pEvilPlant->LackBlood() || pEvilPlant->LackMagi())
		{//휴식기
			pEvilPlant->ChangeState(BreakTime::Instance());
		}
	}
	else
	{//생존 불가 == 사망 확정
		pEvilPlant->DeathSetting();
		std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : 영양부족으로 시름시름 앓다가 말라비틀어져 죽어버렸다." << std::endl << std::endl;
		return;
	}
}

void MakeFruit::Exit(EvilPlant* pEvilPlant)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : [맺혀있는 열매는 " + std::to_string(pEvilPlant->CountFruit()) + "개]" << std::endl;
	

	if (pEvilPlant->CountFruit() >= MAX_FRUIT)
	{ //열매 5개를 떨구었을 경우에만 0일 수 있다.
		pEvilPlant->DropFruit();
		pEvilPlant->MaxFruitRestSetting(true);

		std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : 열매를 5개를 퍼뜨렸다." << std::endl;

		std::cout << GetNameOfEntity(pEvilPlant->ID()) << " : [맺혀있는 열매는 " + std::to_string(pEvilPlant->CountFruit()) + "개]" << std::endl;
	}

	SetTextColor(FOREGROUND_INTENSITY);
	std::cout << std::endl;
}