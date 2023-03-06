#include "GameManager.h"

#define CM CardManager::Get_Instance()
//CardManager:: //private 제대로 작동 안 하니 걱정X

GameManager* GameManager::m_pInstance = NULL;

GameManager::GameManager() 
{
	srand(time(NULL));

	LoadStory();
	
	//폰트 설정
	font[FONT_GAMENAME] = CreateFont(FONTSIZE_GAMENAME, 0, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 0, 0, PROOF_QUALITY, 0, L"Times New Roman");
	font[FONT_START_EXIT] = CreateFont(FONTSIZE_START_EXIT, 0, 0, 0, FW_SEMIBOLD, 0, 0, 0, HANGEUL_CHARSET, 0, 0, PROOF_QUALITY, 0, L"Times New Roman");
	font[FONT_STORY] = CreateFont(FONTSIZE_STORY, 0, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 0, 0, PROOF_QUALITY, 0, L"Times New Roman");
	font[FONT_NEXT] = CreateFont(FONTSIZE_NEXT, 0, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 0, 0, PROOF_QUALITY, 0, L"Times New Roman");
	font[FONT_CLOCK] = CreateFont(FONTSIZE_CLOCK, 0, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 0, 0, PROOF_QUALITY, 0, L"Times New Roman");
	font[FONT_GAMECLEAR] = CreateFont(FONTSIZE_GAMECLEAR, 0, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 0, 0, PROOF_QUALITY, 0, L"궁서");

	cardSame = true;
	changeIMG_Sec = SEC_CHANGE_IMG;
}
GameManager::~GameManager() 
{
	for (int i = 0; i < FONT_COUNT; i++)
		DeleteObject(font[i]);
}

void GameManager::Init(BitMapManager* BitMapMgr_Main, BitMapManager* BitMapMgr_Sub, HWND hWnd_Main, HWND hWnd_Sub)
{
	scene = SEQUENCE_MENU;

	m_HWND_Main = hWnd_Main;
	m_HWND_Sub = hWnd_Sub;

	m_BitMapMgr_Main = BitMapMgr_Main;
	m_BitMapMgr_Sub = BitMapMgr_Sub;

	BitMapMgr_Main->Init(hWnd_Main);
	BitMapMgr_Sub->Init(hWnd_Sub); //★원래 비트맵 Mgr 하나만 존재하는 게 맞는데. 간편하게 만들기 위해서 이번만 이렇게 사용

	click.X = MENUCLICK_X;
	click.Y = MENUCLICK_Y;

	startRect.left = RECT_START_L;
	startRect.top = RECT_START_T;
	startRect.right = RECT_START_R;
	startRect.bottom = RECT_START_B;

	exitRect.left = RECT_EXIT_L;
	exitRect.top = RECT_EXIT_T;
	exitRect.right = RECT_EXIT_R;
	exitRect.bottom = RECT_EXIT_B;

	nextRect.left = RECT_NEXT_L;
	nextRect.top = RECT_NEXT_T;
	nextRect.right = RECT_NEXT_R;
	nextRect.bottom = RECT_NEXT_B;

	timerRect.left = RECT_Timer_L;
	timerRect.top = RECT_Timer_T;
	timerRect.right = RECT_Timer_R;
	timerRect.bottom = RECT_Timer_B;
}

bool GameManager::ColliderCheck(POINT point)
{
	switch (scene)
	{
	case SEQUENCE_MENU:
		if (PtInRect(&startRect, point))
		{
			CM->CardInit(m_BitMapMgr_Main);
			scene = SEQUENCE_STROY;
			//scene = SEQUENCE_CLEAR;
			return true;
		}
		else if (PtInRect(&exitRect, point))
			PostQuitMessage(0);
		break;
	case SEQUENCE_STROY:
		if (PtInRect(&nextRect, point))
		{
			scene = SEQUENCE_RABBIT;
			return true;
		}
		break;
	case SEQUENCE_RABBIT:
		if (PtInRect(&nextRect, point))
		{		
			scene = SEQUENCE_SHOWCARD;
			//카드 순서 보여주기 전 초기 설정
			CM->CardOrderSet();
			//타이머 설정
			SetTimer(m_HWND_Main, TIMER_ID_CARD_ORDER, TIMER_CARD_ODER_SEC, NULL); //카드 하나씩 뒤집기 시간 체크
			SetTimer(m_HWND_Main, TIMER_ID_SCENE, TIMER_SCENE_SEC, NULL); //화면 보여주기 할 시간 체크
			second = SEC_SCENE_SHOWCARD; //화면 보여주기할 시간
			return true;
		}
		break;
	case SEQUENCE_CARDGAME:
		//카드 순서대로 뒤집는 중에는 콜라이더 체크를 막아놔야 한다.
		if (CM->CardList_ColliderCheck(point, m_HWND_Main, TIMER_ID_CARD_ALL, TIMER_CARD_ALL_SEC, NULL))
			return true;
		break;
	case SEQUENCE_GAMEOVER:
		if (PtInRect(&exitRect, point))
			PostQuitMessage(0);
		break;
	case SEQUENCE_CLEAR:
		if (PtInRect(&nextRect, point))
			PostQuitMessage(0);
		break;
	default:
		break;
	}
	return false;
}

void GameManager::Draw(HDC hdc, HINSTANCE g_hInst)
{
	switch (scene)
	{
	case SEQUENCE_MENU:
		m_BitMapMgr_Main->GetBGImage(IMG_BG::IMG_BG_MAIN)->DrawBackGroundIMG(hdc);
		MainMenu(hdc, g_hInst);
		break;
	case SEQUENCE_STROY: 
		m_BitMapMgr_Main->GetBGImage(IMG_BG::IMG_BG_STORY)->DrawBackGroundIMG(hdc);
		//스토리
		Story(hdc, STORY_INTRO, STORY_INTRO_LINE, STORY_INTRO_X, STORY_INTRO_Y); 
		break;
	case SEQUENCE_RABBIT:
		m_BitMapMgr_Main->GetBGImage(IMG_BG::IMG_BG_RABBIT)->DrawBackGroundIMG(hdc);
		Story(hdc, STORY_RABBIT, STORY_RABBIT_LINE, STORY_RABBIT_X, STORY_RABBIT_Y);//스토리
		break;
	case SEQUENCE_SHOWCARD:
		m_BitMapMgr_Main->GetBGImage(IMG_BG::IMG_BG_CARDGAME)->DrawBackGroundIMG(hdc);
		CM->ShowCard_XY(hdc);
		PrintTimer(hdc, std::to_wstring(second));
		PrintAdvice(hdc);
		break;
	case SEQUENCE_CARD_ORDERTURN:
		m_BitMapMgr_Main->GetBGImage(IMG_BG::IMG_BG_CARDGAME)->DrawBackGroundIMG(hdc);
		CM->ShowCard_Index(hdc);
		PrintTimer(hdc, std::to_wstring(second));
		break;
	case SEQUENCE_CARDGAME:
		m_BitMapMgr_Main->GetBGImage(IMG_BG::IMG_BG_CARDGAME)->DrawBackGroundIMG(hdc);
		if (second <= changeIMG_Sec) //다 깨진 이미지로 변경
		{
			CM->Front_IMG_Change(m_BitMapMgr_Main);
			changeIMG_Sec = -1;
		}

		CM->ShowCard_Index(hdc);

		if (CM->EmptyCardCheck())
			scene = SEQUENCE_CLEAR;

		PrintTimer(hdc, std::to_wstring(second));
		break;
	case SEQUENCE_GAMEOVER:
		m_BitMapMgr_Main->GetBGImage(IMG_BG::IMG_BG_GAMEOVER)->DrawBackGroundIMG(hdc);
		GameOver(hdc);
		break;
	case SEQUENCE_CLEAR:
		m_BitMapMgr_Main->GetBGImage(IMG_BG::IMG_BG_GAMECLEAR)->DrawBackGroundIMG(hdc);
		GameClear(hdc);
		break;
	default:
		break;
	}
}

void GameManager::PrintTimer(HDC hdc, std::wstring wstrSec)
{
	if (second >= 0)
	{
		//font 배열로만들어서 사용
		//(HFONT)SelectObject(hdc, font[FONT_CLOCK]); //(HFONT)는 리턴형으로 받아서 Old 저장할 때 사용한다.
		SelectObject(hdc, font[FONT_CLOCK]);
		SetBkColor(hdc, RGB(0, 0, 0));
		//SetBkMode(hdc, TRANSPARENT); //글자 뒷배경 투명화
		SetTextColor(hdc, RGB(255, 0, 0)); //글자 색 변경

		//타이머 출력
		std::wstring wstr = L"00 : ";

		if (second < 10)
			wstr += L"0";
		wstr += wstrSec;

		DrawText(hdc, wstr.c_str(), -1, &timerRect, DT_WORDBREAK);

		//2개의 카드가 다른 경우 2초 감소 Print
		if (!cardSame)
		{
			if (keep_sec - second >= SEC_MINUS_PRINT) //1s 동안 출력되도록
				cardSame = true;

			wstr = L"- 2s";

			//SetBkColor(hdc, RGB(0, 0, 0));
			SetBkMode(hdc, TRANSPARENT); //글자 뒷배경 투명화
			SetTextColor(hdc, RGB(255, 0, 0)); //글자 색 변경
			TextOut(hdc, SEC_MINUS_PRINT_X, SEC_MINUS_PRINT_Y, wstr.c_str(), wstr.length()); //TODO::인자 따로 받아서 사용
		}
	}
}



void GameManager::MainMenu(HDC hdc, HINSTANCE g_hInst)
{
	//HDC hdc = BeginPaint(hWnd, &ps); //BeginPaint는 WM_Paint에서만 쓴다.

	std::wstring str;

	//글자 크기 변경
	SelectObject(hdc, font[FONT_GAMENAME]);
	//oldfont = (HFONT)SelectObject(hdc, font);
	SetBkMode(hdc, TRANSPARENT); //글자 뒷배경 투명화
	//SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(245, 250, 245)); //글자 색 변경


	str = L"F O R E S T";
	TextOut(hdc, click.X, click.Y, str.c_str(), str.length());

	SelectObject(hdc, font[FONT_START_EXIT]);
	//oldfont = (HFONT)SelectObject(hdc, font);
	SetTextColor(hdc, RGB(50, 20, 20));

	str = L"S t a r t";
	DrawText(hdc, str.c_str(), -1, &startRect, DT_CENTER | DT_WORDBREAK);

	str = L"E x i t";
	DrawText(hdc, str.c_str(), -1, &exitRect, DT_CENTER | DT_WORDBREAK);
}

void GameManager::Story(HDC hdc, STORY storyType, STORY storyLine, STORY x, STORY y)
{
	std::wstring str;
	std::vector<std::string> printStoryList = storyList[storyType];

	SelectObject(hdc, font[FONT_STORY]);
	//oldfont = (HFONT)SelectObject(hdc, font);
	//SetBkMode(hdc, TRANSPARENT); //글자 뒷배경 투명화
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(245, 250, 245)); //글자 색 변경

	for (int i = 0; i < storyLine; i++)
		TextOutA(hdc, x, y + i * 1.2 * FONTSIZE_STORY, printStoryList[i].c_str(), printStoryList[i].length());

	SelectObject(hdc, font[FONT_NEXT]);

	switch (storyType)
	{
	case STORY_CLEAR:
		str = L"E N D ◇";
		break;
	default:
		str = L"N e x t ☞";
		break;
	}
		
	DrawText(hdc, str.c_str(), -1, &nextRect, DT_WORDBREAK);
}

void GameManager::PrintAdvice(HDC hdc)
{
	std::wstring str;

	//글자 크기 변경
	SelectObject(hdc, font[FONT_STORY]);
	SetBkMode(hdc, TRANSPARENT); //글자 뒷배경 투명화
	//SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(245, 250, 245)); //글자 색 변경
	//SetTextColor(hdc, RGB(000, 051, 051)); //글자 색 변경

	str = L"동물들이 순서대로 모습을 드러낸다.";
	TextOut(hdc, click.X, STORY_ADVICE_Y, str.c_str(), str.length());
}

void GameManager::GameOver(HDC hdc)
{
	std::wstring wstr;

	//글자 크기 변경
	SelectObject(hdc, font[FONT_GAMENAME]);
	//oldfont = (HFONT)SelectObject(hdc, font);
	SetBkMode(hdc, TRANSPARENT); //글자 뒷배경 투명화
	SetTextColor(hdc, RGB(245, 250, 245)); //글자 색 변경
	//SetTextColor(hdc, RGB(000, 051, 051)); //글자 색 변경

	wstr = L"G A M E  O V E R";//TODO:: 그림으로 변경
	TextOut(hdc, click.X - 30, click.Y, wstr.c_str(), wstr.length()); //TODO::인자 따로 받아서 사용

	SelectObject(hdc, font[FONT_START_EXIT]);
	SetTextColor(hdc, RGB(245, 250, 245));
	wstr = L"E n d";
	DrawText(hdc, wstr.c_str(), -1, &exitRect, DT_CENTER | DT_WORDBREAK);
}

void GameManager::GameClear(HDC hdc)
{
	//KillTimer(m_HWND_Main, TIMER_ID_SCENE);
	//KillTimer(m_HWND_Main, TIMER_ID_CARD_ORDER); //사실상 순서 보여주기에는 이미지가 10개라 여기서 해제
	Kill_AllTimer();

	std::wstring wstr;

	//글자 크기 변경
	(HFONT)SelectObject(hdc, font[FONT_GAMECLEAR]);
	SetBkMode(hdc, TRANSPARENT); //글자 뒷배경 투명화
	SetTextColor(hdc, RGB(245, 250, 245)); //글자 색 변경
	//SetTextColor(hdc, RGB(000, 051, 051)); //글자 색 변경

	wstr = L"E S C A P E";
	TextOut(hdc, click.X - 60, click.Y, wstr.c_str(), wstr.length());

	Story(hdc, STORY_CLEAR, STORY_CLEAR_LINE, STORY_CLEAR_X, STORY_CLEAR_Y);//스토리
}


void GameManager::LoadStory()
{
	std::ifstream load;
	std::string storyTmp; //wstring으로 변환 위해
	std::vector<std::string> tmpStoryList;

	load.open("IntroStory.txt");
	if (load.is_open())
	{
		for (int i = 0; i < STORY_INTRO_LINE; i++)
		{
			getline(load, storyTmp);
			tmpStoryList.push_back(storyTmp);
		}

		storyList.insert({ STORY_INTRO, tmpStoryList });
		tmpStoryList.clear();
		load.close();
	}

	load.open("RabbitStory.txt");
	if (load.is_open())
	{
		for (int i = 0; i < STORY_RABBIT_LINE; i++)
		{
			getline(load, storyTmp);
			tmpStoryList.push_back(storyTmp);
		}

		storyList.insert({ STORY_RABBIT, tmpStoryList });
		tmpStoryList.clear();
		load.close();
	}

	load.open("ClearStory.txt");
	if (load.is_open())
	{
		for (int i = 0; i < STORY_CLEAR_LINE; i++)
		{
			getline(load, storyTmp);
			tmpStoryList.push_back(storyTmp);
		}

		storyList.insert({ STORY_CLEAR, tmpStoryList });
		tmpStoryList.clear();
		load.close();
	}
}

bool GameManager::Timer(WPARAM wParam)
{
	InvalidateRect(m_HWND_Main, NULL, true);

	switch (wParam)
	{
	case TIMER_ID_SCENE:
		second--;

		if (second < 0)
		{
			//카드 순서 보여주기 끝나고 처리할 거
			//MessageBeep(MB_ICONHAND); //경고음 출력
			CM->CardTurn_All(CARD_FRONT); //카드 앞면으로 뒤집기
			//KillTimer(m_HWND_Main, TIMER_ID_SCENE);
			//KillTimer(m_HWND_Main, TIMER_ID_CARD_ORDER); //사실상 순서 보여주기에는 이미지가 10개라 여기서 해제
			Kill_AllTimer();

			switch (scene)
			{
			case SEQUENCE_SHOWCARD:
				//본 가드 게임 넘어가기 전 초기세팅
				scene = SEQUENCE_CARD_ORDERTURN;
				CM->CardShuffleMix(); //카드 랜덤 생성한 배열에 따라 XY 배치

				//본 카드 게임 카드 보여주는 순간부터:: 게임 플레이 제한 시간 
				SetTimer(m_HWND_Main, TIMER_ID_CARD_ORDER, TIMER_CARD_ODER_SEC, NULL); //이렇게 안 하면 다음 시작때 카드 하나 이미 가려짐
				SetTimer(m_HWND_Main, TIMER_ID_SCENE, TIMER_SCENE_SEC, NULL); //화면 보여주기 할 시간 체크
				second = SEC_SCENE_CARDGMAE; //화면 보여주기할 시간

				break;
			case SEQUENCE_CARDGAME:
				//타임오버로 GAME OVER
				scene = SEQUENCE_GAMEOVER;
				break;
			default:
				break;
			}
			return true;
		}
		break;
	case TIMER_ID_CARD_ORDER: //카드 순서 보여주기, 본 카드 게임 카드 보여주기
		if (!CM->CardTurn_Order(scene)) //이 씬에선 카드가 다 뒷면이 될때까지 뒤집기 //모든 카드 아님 절반인 5개
		{
			if (scene == SEQUENCE_CARD_ORDERTURN)
			{
				scene = SEQUENCE_CARDGAME;
				CM->Set_TurnNextID_To_0();
			}

			KillTimer(m_HWND_Main, TIMER_ID_CARD_ORDER);
		}
		break;
	case TIMER_ID_CARD_ALL:
		cardSame = CM->CardInactiveCheck();
		if (!cardSame) //순서 + 같은 카드 확인 후 없으면 출력 안 하기
		{
			second -= SEC_MINUS; //카드가 틀릴 경우 2초 감소
			keep_sec = second; //감소 표시 일정 시간 띄워두기 위해
		}
		CM->CardTurn_All(CARD_REAR); //앞 > 뒷 한번에 //같은 카드 비활성화 해도 FrontCount 값이 있어서 함수 필요.

		KillTimer(m_HWND_Main, TIMER_ID_CARD_ALL);
		break;
	default:
		break;
	}

	return false;
}


void GameManager::SubDraw(HDC hdc)
{
	switch (scene)
	{
	case SEQUENCE_SHOWCARD:
	case SEQUENCE_CARD_ORDERTURN:
	case SEQUENCE_CARDGAME:
		m_BitMapMgr_Sub->GetBGImage(IMG_BG::SUB_IMG_BG_FIRST)->Draw(hdc, 0, 0, SUB_W, SUB_H);
		break;
	case SEQUENCE_GAMEOVER:
		MoveWindow(m_HWND_Sub, MAIN_X, MAIN_Y, MAIN_W, MAIN_H, true);
		m_BitMapMgr_Sub->GetBGImage(IMG_BG::SUB_IMG_BG_END)->DrawBackGroundIMG(hdc);
		//서브 Window가 앞으로 오게
		SetForegroundWindow(m_HWND_Sub); //컴퓨터 그래픽스 ppt 확인

		//화면 보여주기 할 시간 체크
		SetTimer(m_HWND_Sub, TIMER_ID_SCENE, TIMER_SCENE_SEC, NULL); 
		second = SEC_SCENE_GAMEOVERE; //2초 동안 띄우고 없애기
		break;
	case SEQUENCE_CLEAR:
		break;
	default:
		break;
	}
}

void GameManager::Kill_AllTimer()
{
	KillTimer(m_HWND_Main, TIMER_ID_SCENE);
	KillTimer(m_HWND_Main, TIMER_ID_CARD_ORDER);
	KillTimer(m_HWND_Main, TIMER_ID_CARD_ALL);
}