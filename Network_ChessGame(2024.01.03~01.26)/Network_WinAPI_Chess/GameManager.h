#pragma once
#include "BitMapManager.h"
#include "PiecesManager.h"
#include <fstream>
#include <string>
#include <algorithm>



//�ڴ������� font������ init���� �ؼ� ��������� ���ϰ� �ִ´�.

//�� ���⿡ ����صΰ� �ߺ� ���� ���� ���
#define GMMgr GameManager::Get_Instance()
#define PiecesMgr PiecesManager::Get_Instance()
#define BitMapMgr BitMapManager::GetInstance()

enum BOARD
{
	BOARD_X = 8,
	BOARD_Y = 8,

	BOARD_SQUARE_SIZE = 60, //�簢�� �ϳ��� ũ�� //Sub
	BOARD_SQUARE_Sub_SIZE = BOARD_SQUARE_SIZE * 3, //Sub Promotion Window Draw�ϱ� ���� ũ��


	BOARD_LINE = 10, //x,y �ٴ� 10���� ���� �ʿ�
	BOARD_LINE_END = 8 * BOARD_SQUARE_SIZE,

};

enum FONTSIZE
{
	FONTSIZE_NUMBER,
	FONTSIZE_ORDER,
};

enum FONT
{
	VICTORY_FONTSIZE = 15,
	END_FONTSIZE = 13,
	//END_FONTSIZE = 20,

	RECT_EXIT_L = 210,
	RECT_EXIT_T = 250,
	RECT_EXIT_R = RECT_EXIT_L + 60,
	//RECT_EXIT_R = RECT_EXIT_L + 30,
	RECT_EXIT_B = RECT_EXIT_T + 30,
	//RECT_EXIT_B = RECT_EXIT_T + 15,
};

//--- Chess ��Ʈ��ũ �߰� ---
enum PLYAERSTATE
{
	WAIT_PLAYER,
	WAIT_TURN,
	MY_TURN,
};

class GameManager
{
private:
	static GameManager* m_pInstance;
	HWND m_HWND_Main;
	HWND m_HWND_Sub;
	HWND m_HWND_Sub_Promotion;

	//���� ���۸�
	RECT clientRect_Main;
	RECT clientRect_Sub;
	RECT clientRect_Sub_Promotion;
	HDC backDC_Main;
	HDC backDC_Sub;
	HDC backDC_Sub_Promotion;
	
	//�� BitMapManager�ν��� �ǹ̰� ����Ǿ���. �̱������� ���� ����ϴ� ���� ����. main�̳� sub�� ���ڸ� �־(?) �ش� BitMapManager�� ����ϵ���
	//BitMapManager* m_BitMapMgr_Main;
	//BitMapManager* m_BitMapMgr_Sub;
	//BitMapManager* m_BitMapMgr_Sub_Promotion;

	//SubPromotion ����ϱ� ����
	int nCmdShow;
	LPCTSTR IpszClassSub_Promotion;
	HINSTANCE hInstance;
	
	//CAMP_NONE = -1, CAMP_WHITE, CAMP_BLACK �� �̿��ؼ� �ش� ĭ�� ���� �ִ��� � ������ �Ǵ� ����
	CAMP m_Map[BOARD_X][BOARD_Y];
	//���� �÷��̾� �� Ȯ��
	CAMP m_PlayerTurn;
	bool m_GameStopCheck;
	bool m_GameEndCheck;
	RECT exitRect; //����

	//--- Chess ��Ʈ��ũ �߰� ---
	//�����̵Ǹ� �ݶ��̴� üũ(Ŭ��) ���ϰ� ���´�.
	//bool isWaitlayer, isDelay; 
	PLYAERSTATE m_PalyerState;
	int m_moved_iX, m_moved_iY; //���������� ������ ����_ �����̱� ���� ���� ��ġ.
	RECT m_moveRect; //���������� ������ ����_ ������ ��ġ

	bool isSend_Sever; //������ ������ ���� ���� üũ
	bool isPromotion;
	bool isWinCheck; //���а� ������ Ȯ��
	CAMP winTeam; //�¸��� ��
	//------------------------

	GameManager();

	//������ �׸���
	void BoardDraw(HDC hdc);
	void LineDraw(HDC hdc);
	void SquareDraw(HDC hdc);
public:
	~GameManager();

	static GameManager* Get_Instance()
	{
		if (NULL == m_pInstance)
			m_pInstance = new GameManager;
		return m_pInstance;
	}

	//void Init(BitMapManager* BitMapMgr_Main, BitMapManager* BitMapMgr_Sub, BitMapManager* BitMapMgr_Sub_Promtion, HWND hWnd_Main, HWND hWnd_Sub, int nCmdShow, LPCTSTR IpszClassSub_Promotion, HINSTANCE hInstance);
	void Init(HWND hWnd_Main, HWND hWnd_Sub, int nCmdShow, LPCTSTR IpszClassSub_Promotion, HINSTANCE hInstance);
	bool ColliderCheck(POINT point);
	bool ColliderCheck_SubPromotion(POINT point);
	void Draw(HDC hdc);
	void WinCheck(HDC hdc);
	void SubDraw(HDC backDC_Sub);
	void SubPromotionDraw(HDC hdc);
	void SubPromotion();

	HWND Get_HWND_Main() { return m_HWND_Main; }
	HWND Get_HWND_Sub() { return m_HWND_Sub; }
	HWND Get_HWND_Sub_Promotion() { return m_HWND_Sub_Promotion; }

	CAMP(*Get_Map())[BOARD_Y] { return m_Map; }
	//BitMapManager* Get_BitMapMain() { return m_BitMapMgr_Main; }
	CAMP Get_PlayerTurn() { return m_PlayerTurn; }
	bool Get_GameStopCheck() { return m_GameStopCheck; }
	bool Get_GameEndCheck() { return m_GameEndCheck; }

	void Set_Map(CAMP campColor, int x, int y) { m_Map[x][y] = campColor; }
	//���� �ϰ� �ݴ�Ǵ� ���� �������ش�.
	void Set_PlayerTurn() { m_PlayerTurn = (m_PlayerTurn == CAMP_WHITE) ? CAMP_BLACK : CAMP_WHITE; }
	void Set_GameStopCheck(bool check) { m_GameStopCheck = check; }
	void Set_GameEndCheck(bool check) { m_GameEndCheck = check; }

	HBITMAP MyCreateDIBSection(HDC hdc, int width, int height);


	//--- Chess ��Ʈ��ũ �߰� ---
	//���� ����
	void DelayAccess(CAMP playerTeam);
	//�� ����
	void SetDelayTurn(); 
	//�� ������ ��� ������ ����
	void SetTurn(CAMP nowTurn);



	PLYAERSTATE GetPlayerState() { return m_PalyerState; }
	
	//----------�� �����̴� ������ ���� ����------------
	void Set_moveData(int _x, int _y, RECT _moveRect) { m_moved_iX = _x; m_moved_iY = _y; m_moveRect = _moveRect; }
	

	//�����̱� �� ��ǥ + ������ ��ġ RECT �������� �����ֱ��
	void SetMoveData_ToServer(int& _x, int& _y, RECT& _moveRect)
	{
		_x = m_moved_iX; 
		_y = m_moved_iY; 
		_moveRect = m_moveRect; 
	}

	//����, ���� ���
	void DrawTurnState(HDC hdc_Main);

	

	//�÷��̾ ���� ������ �����͸� ������ �ѹ��� ������ ����
	bool Get_IsSend_Sever() { return isSend_Sever; }
	void Set_IsSend_Sever(bool _isSend_Sever) { isSend_Sever = _isSend_Sever; }

	//�̹� ���� ���� �����ϴ� ������ Ȯ��
	bool Get_IsPromotion() { return isPromotion; }
	void Set_IsPromotion(bool _isPromotion) { isPromotion = _isPromotion; }

	//�÷��̾� ���� üũ
	PLYAERSTATE Get_PalyerState() { return m_PalyerState; }


	//-----����------
	void Set_IsWinCheck(bool _isWinCheck) { isWinCheck = _isWinCheck; }
	bool Get_IsWinCheck() { return isWinCheck; }
	
	void Set_WinTeam(CAMP _winTeam) { winTeam = _winTeam; }


	//--���� �ڵ� ����--
	//���� ���۸� - ����(����)â ����
	RECT Get_ClientRect_Sub() { return clientRect_Sub; }
	//RECT Get_ClientRect_Sub_Promotion() { return clientRect_Sub_Promotion; }
};
