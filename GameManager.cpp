#include "GameManager.h"

GameManager* GameManager::m_pInstance = NULL;

GameManager::GameManager()
{
	m_scene = SCENE_MENU;

	//글자 크기 변경
	m_Font[FONT_STAGE] = CreateFont(FONT_STAGE_SIZE, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, L"궁서");
	m_Font[FONT_SCORE] = CreateFont(FONT_SCORE_SIZE, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, L"궁서");
	
	//m_Font[FONT_STAGE] = CreateFont(FONT_STAGE_SIZE, 0, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 0, 0, PROOF_QUALITY, 0, L"Times New Roman");
	//m_Font[FONT_SCORE] = CreateFont(FONT_SCORE_SIZE, 0, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 0, 0, PROOF_QUALITY, 0, L"Times New Roman");
}


GameManager::~GameManager()
{
	//삭제는 생성된 역순으로
	DeleteDC(m_backDC);
	ReleaseDC(m_HWND, m_frontDC);
}

void GameManager::init(HWND hWnd)
{
	RECT clientRect;

	m_HWND = hWnd;
	m_frontDC = GetDC(m_HWND);
	m_backDC = CreateCompatibleDC(m_frontDC);
	//CreateCompatibleDC 함수를 사용해서 DC를 생성하면 이 DC와 연결된 비트맵 객체에는 그림이 그려지지만 화면에는 출력이 되지 않는다.
	//CreateCompatibleDC 함수로 만들어진 DC를 'Memory DC'라고 부른다.
	GetClientRect(m_HWND, &clientRect); //윈도우의 클라이언트의 영역을 알려준다.
	m_Widht_Height.x = clientRect.right - clientRect.left;
	m_Widht_Height.y = clientRect.bottom - clientRect.top;

	BitMapMgr->Init(hWnd);

	//초기화
	m_Prev_MoveDistance = 0;
	m_Character.InitialSet(); //캐릭터
	m_UI.InitialSet(); //UI
	m_Map.InitialSet(); //배경 + M
	m_ObjectMgr.InitialSet(); //Goal + 장애물
}

void GameManager::Update(float deltaTime)
{
	float total_MoveDistance;

	switch (m_scene)
	{
	case SCENE_MENU:
		if (m_UI.UpdateMenu(deltaTime)) //엔터 누르면 씬 전환 //함수를 bool형으로 UI안에서 해결한다.
			m_scene = SCENE_GAME;

		break;
	case SCENE_GAME:
		//-------------------좌표 이동---------------------
		total_MoveDistance = m_Character.Update(deltaTime);
		m_UI.UpdateGame(deltaTime);

		m_Map.UpdateMap(total_MoveDistance, m_Prev_MoveDistance); //back 관중+코끼리 왼쪽 순회


		if (m_Map.MeterEnd_GoalActiveCheck() == true)
		{
			//active체크만 하고 초기 goal의 x 값은 meter의 오른쪽 화면에 숨어있을때의 세팅 값으로 해둔다.
			//+ 세팅은 생성자에서 처리를 하기로 한다.
			m_ObjectMgr.Set_Goal_ActiveCheck(true); //Goal이 그려짐+이동+충돌체크가 가능한 상태
			
		}
		else
			m_ObjectMgr.Set_Goal_ActiveCheck(false);

		m_ObjectMgr.Update(total_MoveDistance, m_Prev_MoveDistance);

		m_Prev_MoveDistance = total_MoveDistance;


		//--------------------Collider 체크---------------------
		//Goal 통과
		if (m_ObjectMgr.ColliderCheck_Goal(m_Character.Get_CharacterRect()))
		{
			m_scene = SCENE_GAMECLEAR;

			m_Character.Set_PerformanceMotion(); //캐릭터 IMG 변경
			m_Character.Set_XY_GoalMid();//캐릭터를 goal 중앙으로 이동시킨다.
		}

		//장애물 부딪힘
		if (m_ObjectMgr.ColliderCheck_Obstacle(m_Character.Get_CharacterRect()))  //TODO::이거 추가 필요
		{
			if (m_Character.ReductionLife_End()) //함수 내부 목숨 감소 > true면 GameOver
			{ //게임 세팅 초기화
				m_scene = SCENE_MENU; //씬 메인메뉴로
				
				//초기화
				m_Prev_MoveDistance = 0;
				m_Character.InitialSet(); //캐릭터
				m_UI.InitialSet(); //UI
				m_Map.InitialSet(); //배경 + M
				m_ObjectMgr.InitialSet(); //Goal + 장애물
			}
		}


		break;
	case SCENE_GAMECLEAR:
		m_Map.UpdateClapBack(deltaTime);
		m_Character.UpdatePerformance(deltaTime);
		break;
	}
}

//bool GameManager::GameVictoryCheck()
//{
//	//Win > 관중 박수 치기
//	if (m_ObjectMgr.ColliderCheck_Goal(m_Character.Get_CharacterRect()))
//		return true;
//	//GameOver
//	m_ObjectMgr.ColliderCheck_Obstacle(m_Character.Get_CharacterRect());
//		return true;
//	return false;
//}


/*GM의 Draw에서 backDC에 비트맵의 정보를 지정해서
MapDraw나 UI에서 backDC로 backBitmap에 그린다.(backDC는 붓)
BitMap에서 memDC(이미지 하나하나마다의 붓)*/
void GameManager::Draw()
{
	//더블 버퍼링
	HBITMAP backBitmap = MyCreateDIBSection(m_frontDC, m_Widht_Height.x, m_Widht_Height.y);

	SelectObject(m_backDC, backBitmap);

	switch (m_scene)
	{
	case SCENE_MENU:
		m_UI.DrawMenu(m_backDC);
		break;
	case SCENE_GAME:
		m_Map.DrawMap(m_backDC);	//배경
		m_UI.DrawGame(m_backDC);	//UI
		m_Character.Draw(m_backDC);	//캐릭터


		m_ObjectMgr.Draw(m_backDC);	//오브젝트
		break;
	case SCENE_GAMECLEAR:
		m_Map.DrawMap(m_backDC);
		m_UI.DrawGame(m_backDC);	//UI
		m_ObjectMgr.Draw(m_backDC);	//오브젝트
		m_Character.Draw(m_backDC);	//캐릭터
		break;
	}

	//더블 버퍼링
	BitBlt(m_frontDC, 0, 0, m_Widht_Height.x, m_Widht_Height.y, m_backDC, 0, 0, SRCCOPY);
	DeleteObject(backBitmap);
}

bool GameManager::GameClearCheck()
{
	switch (m_scene)
	{
	case SCENE_MENU:
	case SCENE_GAME:
		return false;
	case SCENE_GAMECLEAR:
		return true;
	}
}





//더블 버퍼링
HBITMAP GameManager::MyCreateDIBSection(HDC hdc, int width, int height)
{
	BITMAPINFO bm_info;
	ZeroMemory(&bm_info.bmiHeader, sizeof(BITMAPINFOHEADER));

	bm_info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	//color bits : 1, 4, 8, 16, 24, 32
	//1:흑백, 4:16색, 8:256색, 16:2^15색, 24,31:2^24색
	bm_info.bmiHeader.biBitCount = 24;
	bm_info.bmiHeader.biWidth = width; //너비, 비트맵의 가로 픽셀 수
	bm_info.bmiHeader.biHeight = height; //높이, 비트맵의 세로 픽셀 수
	bm_info.bmiHeader.biPlanes = 1; //1로 고정, 반드시 1이어야 한다

	LPVOID pBits;
	return CreateDIBSection(hdc, &bm_info, DIB_RGB_COLORS, (void**)&pBits, NULL, 0);
}