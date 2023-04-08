#include "GameManager.h"

GameManager* GameManager::m_pInstance = NULL;

GameManager::GameManager()
{
	m_Scene = SCENE_MENU;

	//���� ũ�� ����
	m_Font[FONT_STAGE] = CreateFont(FONT_STAGE_SIZE, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, L"�ü�");
	m_Font[FONT_SCORE] = CreateFont(FONT_SCORE_SIZE, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, L"�ü�");
}


GameManager::~GameManager()
{
	//������ ������ ��������
	DeleteDC(m_backDC);
	ReleaseDC(m_HWND, m_frontDC);
}

void GameManager::init(HWND hWnd)
{
	RECT clientRect;

	m_HWND = hWnd;
	m_frontDC = GetDC(m_HWND);
	m_backDC = CreateCompatibleDC(m_frontDC);
	//CreateCompatibleDC �Լ��� ����ؼ� DC�� �����ϸ� �� DC�� ����� ��Ʈ�� ��ü���� �׸��� �׷������� ȭ�鿡�� ����� ���� �ʴ´�.
	//CreateCompatibleDC �Լ��� ������� DC�� 'Memory DC'��� �θ���.
	GetClientRect(m_HWND, &clientRect); //�������� Ŭ���̾�Ʈ�� ������ �˷��ش�.
	m_Widht_Height.x = clientRect.right - clientRect.left;
	m_Widht_Height.y = clientRect.bottom - clientRect.top;

	BitMapMgr->Init(hWnd);

	//�ʱ�ȭ
	m_Prev_MoveDistance = 0;
	m_Character.InitialSet(SET_INIT); //ĳ����
	m_UI.InitialSet(SET_INIT); //UI
	m_Map.InitialSet(SET_INIT); //��� + M
	m_ObjectMgr.InitialSet(); //Goal + ��ֹ�
}

void GameManager::Update(float deltaTime)
{ //��ǥ�̵��� ������ ��� return���� �Լ��� ������.
	float total_MoveDistance;

	switch (m_Scene)
	{
	case SCENE_MENU:
		if (m_UI.UpdateMenu(deltaTime)) //���� ������ �� ��ȯ //�Լ��� bool������ UI�ȿ��� �ذ��Ѵ�.
			m_Scene = SCENE_GAME;

		return;
	case SCENE_GAME:
		//--------------------Collider üũ---------------------
		switch (m_ObjectMgr.ColliderCheck(m_Character.Get_CharacterRect()))
		{
		case BUMP_GOAL: //Goal ���
			m_Scene = SCENE_GAMECLEAR;

			m_Character.Set_Bump_Check(BUMP_GOAL); //ĳ������ �ε��� �Ǻ� ���� ����
			m_Character.Set_PerformanceMotion(); //ĳ���� IMG ����
			m_Character.Set_XY_GoalMid();//ĳ���͸� goal �߾����� �̵���Ų��.
			return;

		case BUMP_OBSTACLE: //��ֹ� �ε���
			m_Character.Set_Bump_Check(BUMP_OBSTACLE); //ĳ������ �ε��� �Ǻ� ���� ����
			m_Character.Update_Animation(deltaTime); //ĳ���� �ִϸ��̼Ǹ� �۵�

			//ĳ���Ͱ� ���� �ð� �̻� �ε��� Animation�� ����� ���� ó��
			if (m_Character.Get_Bump_Check() == BUMP_NONE)
			{
				//TODO:: �׽�Ʈ ���� �ּ�ó��
				
				if (m_Character.ReductionLife_End()) //�Լ� ���� ��� ���� > true�� GameOver
				{ //���� ���� �ʱ�ȭ
					m_Scene = SCENE_MENU; //�� ���θ޴���

					//�ʱ�ȭ
					//m_Prev_MoveDistance = 0;
					m_Character.InitialSet(SET_INIT); //ĳ����
					m_UI.InitialSet(SET_INIT); //UI
					m_Map.InitialSet(SET_INIT); //��� + M
					//m_ObjectMgr.InitialSet(); //Goal + ��ֹ�
				}
				else
				{
					//���� M ���� ������
					//m_Prev_MoveDistance = 0;
					m_Character.InitialSet(SET_RESPAWN); //ĳ����
					m_UI.InitialSet(SET_RESPAWN); //UI						
					m_Map.InitialSet(SET_RESPAWN); //��� + M				//TODO::M�� ����
					//m_ObjectMgr.InitialSet(); //Goal + ��ֹ�
				}
				m_Prev_MoveDistance = 0;
				m_ObjectMgr.InitialSet(); //Goal + ��ֹ�
			}
			return;
		case BUMP_SCORE: //Score Rect�� �浹
			if (BUMP_NONE == m_Character.Get_Bump_Check()) //ĳ���� �ε��� ���°� �ٲ�� �������� score 100
				m_UI.ScoreUp();

			m_Character.Set_Bump_Check(BUMP_SCORE);
			break;
		case BUMP_NONE:
			m_Character.Set_Bump_Check(BUMP_NONE); //ĳ������ �ε��� �Ǻ� ���� ����

			break;
		}
		break;
	case SCENE_GAMECLEAR:
		m_Map.UpdateClapBack(deltaTime);
		m_Character.Update_Animation(deltaTime);
		return;
	}

	//-------------------��ǥ �̵�---------------------
	total_MoveDistance = m_Character.Update(deltaTime);
	m_UI.UpdateGame(deltaTime);

	m_Map.UpdateMap(total_MoveDistance, m_Prev_MoveDistance); //back ����+�ڳ��� ���� ��ȸ


	if (m_Map.MeterEnd_GoalActiveCheck() == true)
	{
		//activeüũ�� �ϰ� �ʱ� goal�� x ���� meter�� ������ ȭ�鿡 ������������ ���� ������ �صд�.
		//+ ������ �����ڿ��� ó���� �ϱ�� �Ѵ�.
		m_ObjectMgr.Set_Goal_ActiveCheck(true); //Goal�� �׷���+�̵�+�浹üũ�� ������ ����

	}
	else
		m_ObjectMgr.Set_Goal_ActiveCheck(false);

	m_ObjectMgr.Update(deltaTime, total_MoveDistance, m_Prev_MoveDistance);

	m_Prev_MoveDistance = total_MoveDistance;

}


/*GM�� Draw���� backDC�� ��Ʈ���� ������ �����ؼ�
MapDraw�� UI���� backDC�� backBitmap�� �׸���.(backDC�� ��)
BitMap���� memDC(�̹��� �ϳ��ϳ������� ��)*/
void GameManager::Draw()
{
	//���� ���۸�
	HBITMAP backBitmap = MyCreateDIBSection(m_frontDC, m_Widht_Height.x, m_Widht_Height.y);

	SelectObject(m_backDC, backBitmap);

	switch (m_Scene)
	{
	case SCENE_MENU:
		m_UI.DrawMenu(m_backDC);
		break;
	case SCENE_GAME:
		m_Map.DrawMap(m_backDC);	//���
		m_UI.DrawGame(m_backDC);	//UI
		m_Character.Draw(m_backDC);	//ĳ����

		//TODO::���� �� > ĳ���� > ������ ��????
		m_ObjectMgr.Draw(m_backDC);	//������Ʈ
		break;
	case SCENE_GAMECLEAR:
		m_Map.DrawMap(m_backDC);
		m_UI.DrawGame(m_backDC);	//UI
		m_ObjectMgr.Draw(m_backDC);	//������Ʈ
		m_Character.Draw(m_backDC);	//ĳ����
		break;
	}

	//���� ���۸�
	BitBlt(m_frontDC, 0, 0, m_Widht_Height.x, m_Widht_Height.y, m_backDC, 0, 0, SRCCOPY);
	DeleteObject(backBitmap);
}

bool GameManager::GameClearCheck()
{
	switch (m_Scene)
	{
	case SCENE_MENU:
	case SCENE_GAME:
		return false;
	case SCENE_GAMECLEAR:
		return true;
	}
}


//���� ���۸�
HBITMAP GameManager::MyCreateDIBSection(HDC hdc, int width, int height)
{
	BITMAPINFO bm_info;
	ZeroMemory(&bm_info.bmiHeader, sizeof(BITMAPINFOHEADER));

	bm_info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	//color bits : 1, 4, 8, 16, 24, 32
	//1:���, 4:16��, 8:256��, 16:2^15��, 24,31:2^24��
	bm_info.bmiHeader.biBitCount = 24;
	bm_info.bmiHeader.biWidth = width; //�ʺ�, ��Ʈ���� ���� �ȼ� ��
	bm_info.bmiHeader.biHeight = height; //����, ��Ʈ���� ���� �ȼ� ��
	bm_info.bmiHeader.biPlanes = 1; //1�� ����, �ݵ�� 1�̾�� �Ѵ�

	LPVOID pBits;
	return CreateDIBSection(hdc, &bm_info, DIB_RGB_COLORS, (void**)&pBits, NULL, 0);
}