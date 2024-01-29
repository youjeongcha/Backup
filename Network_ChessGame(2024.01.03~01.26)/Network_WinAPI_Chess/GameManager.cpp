#include "GameManager.h"
//�ڰ��� ����� GMMgr���� ����
//�ڴ������� font������ init���� �ؼ� ��������� ���ϰ� �ִ´�.

#define PiecesMgr PiecesManager::Get_Instance()

GameManager* GameManager::m_pInstance = NULL; //�ʱ�ȭ �ʼ�

GameManager::GameManager()
{
	memset(m_Map, CAMP_NONE, sizeof(m_Map));
	m_PlayerTurn = CAMP_WHITE; //���� ȭ�� ������� �ϱ� ����
	//isWaitlayer = true;
	//isDelay = true;
	m_PalyerState = WAIT_PLAYER;
	m_GameStopCheck = false;
	m_GameEndCheck = false;
	isSend_Sever = false;
}

GameManager::~GameManager()
{
}


void GameManager::Init(HWND hWnd_Main, HWND hWnd_Sub,int _nCmdShow, LPCTSTR _IpszClassSub_Promotion, HINSTANCE _hInstance)
{
	m_HWND_Main = hWnd_Main;
	m_HWND_Sub = hWnd_Sub;

	nCmdShow = _nCmdShow;
	IpszClassSub_Promotion = _IpszClassSub_Promotion;
	hInstance = _hInstance;

	BitMapMgr->Init(hWnd_Main);
	PiecesMgr->Init(BitMapMgr);

	//BitMapMgr_Main->Init(hWnd_Main);
	//BitMapMgr_Sub->Init(hWnd_Sub); //�ڿ��� ��Ʈ�� Mgr �ϳ��� �����ϴ� �� �´µ�. �����ϰ� ����� ���ؼ� �̹��� �̷��� ���


	//�ʱ� map ���¸� CAMP�� �ʱ�ȭ�Ѵ�.
	for (int x = 0; x <= ONELINE_PIECES_COUNT; x++)
	{
		m_Map[x][0] = CAMP_BLACK;
		m_Map[x][1] = CAMP_BLACK;
		m_Map[x][6] = CAMP_WHITE;
		m_Map[x][7] = CAMP_WHITE;
	}

	exitRect.left = RECT_EXIT_L;
	exitRect.top = RECT_EXIT_T;
	exitRect.right = RECT_EXIT_R;
	exitRect.bottom = RECT_EXIT_B;

	//���� ���۸�
	HDC hdc = GetDC(hWnd_Main);
	backDC_Main = CreateCompatibleDC(hdc);
	GetClientRect(m_HWND_Main, &clientRect_Main);
	ReleaseDC(hWnd_Main, hdc);

	hdc = GetDC(hWnd_Sub);
	backDC_Sub = CreateCompatibleDC(hdc);	
	GetClientRect(m_HWND_Sub, &clientRect_Sub);
	ReleaseDC(hWnd_Sub, hdc);
}


bool GameManager::ColliderCheck(POINT point)
{
	if (m_GameEndCheck == true)
	{
		//���� �����Ǿ������� exitRect�� �߰� ����ȴ�.
		if (PtInRect(&exitRect, point))
			PostQuitMessage(0);
	}

	if (m_PalyerState == MY_TURN)
	{
		if (PiecesMgr->ColliderCheck(point))
			return true;
	}

	return false;
}

bool GameManager::ColliderCheck_SubPromotion(POINT point)
{
	if ((m_GameStopCheck == true) && (m_GameEndCheck == false))
	{
		//���� Piece ������ ���
		if (PiecesMgr->ColliderCheck_SubPromotion(point))
		{
			m_GameStopCheck = false;
			InvalidateRect(m_HWND_Sub, NULL, false);

			return true;
		}
	}
	return false;
}



void GameManager::Draw(HDC hdc)
{
	//---------������۸�----------
	//RECT clientRect;
	//GetClientRect(m_HWND_Main, &clientRect);
	
	HBITMAP backBitmap = MyCreateDIBSection(hdc, clientRect_Main.right + 1, clientRect_Main.bottom + 1);
	SelectObject(backDC_Main, backBitmap);

	//------------------------------

	BoardDraw(backDC_Main);

	PiecesMgr->DrawPices(backDC_Main);
	//����::���ʿ��� �ݺ��� ���� �� ����?
	PiecesMgr->DrawMoveable(backDC_Main);

	//���� �¸��� ó��
	WinCheck(backDC_Main);

	//---------������۸�----------
	BitBlt(hdc, 0, 0, clientRect_Main.right + 1, clientRect_Main.bottom + 1, backDC_Main, 0, 0, SRCCOPY);
	DeleteObject(backBitmap);
}

void GameManager::BoardDraw(HDC hdc)
{
	SquareDraw(hdc);
	LineDraw(hdc);
}

void GameManager::LineDraw(HDC hdc)
{
	for (int x = 0; x <= BOARD_X; x++)
	{
		MoveToEx(hdc, x * BOARD_SQUARE_SIZE, 0, NULL);
		LineTo(hdc, x * BOARD_SQUARE_SIZE, BOARD_LINE_END);
	}

	for (int y = 0; y <= BOARD_Y; y++)
	{
		MoveToEx(hdc, 0, y * BOARD_SQUARE_SIZE, NULL);
		LineTo(hdc, BOARD_LINE_END, y * BOARD_SQUARE_SIZE);
	}
}

void GameManager::SquareDraw(HDC hdc)
{
	for (int x = 0; x <= BOARD_X; x++)
	{
		for (int y = 0; y <= BOARD_Y; y++)
		{
			if (((y & 1) == 0 && (x & 1) == 0) ||
				((y & 1) == 1 && (x & 1) == 1))
				//x�� y�� �Ѵ� ¦���� 
				BitMapMgr->GetImage(IMG::IMG_BG_WHITE)->DrawBG(hdc, x * BOARD_SQUARE_SIZE, y * BOARD_SQUARE_SIZE, BOARD_SQUARE_SIZE, BOARD_SQUARE_SIZE);
			else
				BitMapMgr->GetImage(IMG::IMG_BG_BLACK)->DrawBG(hdc, x * BOARD_SQUARE_SIZE, y * BOARD_SQUARE_SIZE, BOARD_SQUARE_SIZE, BOARD_SQUARE_SIZE);
		}
	}
}



void GameManager::WinCheck(HDC hdc)
{
	if (m_GameEndCheck)
	{
		std::wstring str;
		HFONT font;

		//���� �̹��� ���� ������ ������ ������ �˸�
		BitMapMgr->GetImage(IMG::IMG_BG_BLACK)->DrawTransparent(hdc, 0, 0, BOARD_SQUARE_SIZE * BOARD_X, BOARD_SQUARE_SIZE * BOARD_Y);

		//���� ũ�� ����
		font = CreateFontW(VICTORY_FONTSIZE, 0, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 0, 0, PROOF_QUALITY, 0, L"Times New Roman");
		SelectObject(hdc, font);
		SetBkMode(hdc, TRANSPARENT); //���� �޹�� ����ȭ
		//SetBkColor(hdc, RGB(0, 0, 0));
		SetTextColor(hdc, RGB(255, 255, 255)); //���� �� ����

		switch (winTeam)
		{
		case CAMP_BLACK:
			str = L"B L A C K";
			break;
		case CAMP_WHITE:
			str = L"W H I T E";
			break;
		}

		str += L"  W I N";
		TextOutW(hdc, RECT_EXIT_L - 32, MAIN_H / 3 + 10, str.c_str(), str.length());

		font = CreateFontW(END_FONTSIZE, 0, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 0, 0, PROOF_QUALITY, 0, L"Times New Roman");
		SelectObject(hdc, font);
		str = L"E n d";
		DrawTextW(hdc, str.c_str(), str.length(), &exitRect, DT_CENTER | DT_WORDBREAK);
	}
}



void GameManager::SubDraw(HDC backDC_Sub)
{
	switch (m_PlayerTurn)
	{
	case CAMP_BLACK:
		BitMapMgr->GetImage(IMG::IMG_BG_BLACK)->DrawSubWin(backDC_Sub, 0, 0, BOARD_SQUARE_SIZE, BOARD_SQUARE_SIZE);
		break;
	case CAMP_WHITE:
		BitMapMgr->GetImage(IMG::IMG_BG_WHITE)->DrawSubWin(backDC_Sub, 0, 0, BOARD_SQUARE_SIZE, BOARD_SQUARE_SIZE);
		break;
	}
}

void GameManager::SubPromotionDraw(HDC hdc)
{
	if ((m_GameStopCheck == true) && (m_GameEndCheck == false))
	{
		/*switch (m_PlayerTurn)
		{
		case CAMP_BLACK:
			BitMapMgr->GetImage(IMG::IMG_BG_BLACK)->DrawSubWin(hdc, 0, 0, BOARD_SQUARE_SIZE, BOARD_SQUARE_Sub_SIZE);
			break;
		case CAMP_WHITE:
			BitMapMgr->GetImage(IMG::IMG_BG_WHITE)->DrawSubWin(hdc, 0, 0, BOARD_SQUARE_SIZE, BOARD_SQUARE_Sub_SIZE);
			break;
		}*/

		PiecesMgr->DrawPawnPromotion(hdc);
	}
}

void GameManager::SubPromotion()
{
	//���� ���� �ܰ谡 ������ ����ϵ���(Pawn ����)
	m_HWND_Sub_Promotion = CreateWindow(IpszClassSub_Promotion, IpszClassSub_Promotion, WS_OVERLAPPED | WS_MINIMIZEBOX, SUB_PROMOTION_X, SUB_PROMOTION_Y, SUB_PROMOTION_W, SUB_PROMOTION_H,
		NULL, (HMENU)NULL, hInstance, NULL);

	HDC hdc = GetDC(m_HWND_Sub_Promotion);
	backDC_Sub_Promotion = CreateCompatibleDC(hdc);
	GetClientRect(m_HWND_Sub_Promotion, &clientRect_Sub_Promotion);

	ReleaseDC(m_HWND_Sub_Promotion, hdc);

	ShowWindow(m_HWND_Sub_Promotion, nCmdShow);
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


//--- Chess ��Ʈ��ũ �߰� ---

void GameManager::DelayAccess(CAMP playerTeam)
{
	m_PlayerTurn = playerTeam; ///  TODO::���� â�� ���� �ߴ��� Ȯ��
	m_PalyerState = WAIT_PLAYER;
}

void GameManager::SetDelayTurn()
{
	m_PalyerState = WAIT_TURN;
}

void GameManager::SetTurn(CAMP nowTurn)
{
	if (m_PlayerTurn == nowTurn)
		m_PalyerState = MY_TURN;
	else
		GMMgr->SetDelayTurn();
}




void GameManager::DrawTurnState(HDC hdc_Sub)
{
	//std::wstring str;
	std::string str;
	RECT textRect;
	textRect.left = PROMOTION_RECT_L;
	textRect.top = PROMOTION_RECT_GAP / 1.25f;
	textRect.right = PROMOTION_RECT_R;
	textRect.bottom = PROMOTION_RECT_B + PROMOTION_RECT_GAP;


	//HFONT font = CreateFont(PROMOTION_FONTSIZE, 0, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 0, 0, PROOF_QUALITY, 0, L"Times New Roman");
	HFONT font = CreateFont(PROMOTION_FONTSIZE, 0, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 0, 0, PROOF_QUALITY, 0, "Times New Roman");


	//���� ũ�� ����
	SelectObject(hdc_Sub, font);
	//oldfont = (HFONT)SelectObject(hdc, font);
	SetBkMode(hdc_Sub, TRANSPARENT); //���� �޹�� ����ȭ
	//SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc_Sub, RGB(128, 128, 128)); //���� �� ����

	switch (m_PalyerState)
	{
	case WAIT_PLAYER:
		str = "Wait for Player";
		break;
	case WAIT_TURN:
		str = "Wait for Turn";
		break;
	case MY_TURN:
		str = "Your Turn";
		break;
	default:
		break;
	}
	

	//DrawText(hdc_SubPromotion, str.c_str(), -1, &m_promotionRect[i], DT_CENTER | DT_WORDBREAK);
	DrawText(hdc_Sub, (LPCSTR)str.c_str(), -1, &textRect, DT_CENTER | DT_WORDBREAK);
}



