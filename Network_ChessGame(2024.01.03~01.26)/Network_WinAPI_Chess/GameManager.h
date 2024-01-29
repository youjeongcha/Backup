#pragma once
#include "BitMapManager.h"
#include "PiecesManager.h"
#include <fstream>
#include <string>
#include <algorithm>



//★다음에는 font생성을 init에서 해서 멤버변수로 지니고 있는다.

//★ 여기에 기록해두고 중복 선언 없이 사용
#define GMMgr GameManager::Get_Instance()
#define PiecesMgr PiecesManager::Get_Instance()
#define BitMapMgr BitMapManager::GetInstance()

enum BOARD
{
	BOARD_X = 8,
	BOARD_Y = 8,

	BOARD_SQUARE_SIZE = 60, //사각형 하나의 크기 //Sub
	BOARD_SQUARE_Sub_SIZE = BOARD_SQUARE_SIZE * 3, //Sub Promotion Window Draw하기 위한 크기


	BOARD_LINE = 10, //x,y 줄다 10개의 선이 필요
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

//--- Chess 네트워크 추가 ---
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

	//더블 버퍼링
	RECT clientRect_Main;
	RECT clientRect_Sub;
	RECT clientRect_Sub_Promotion;
	HDC backDC_Main;
	HDC backDC_Sub;
	HDC backDC_Sub_Promotion;
	
	//★ BitMapManager로써의 의미가 퇴색되었다. 싱글톤으로 만들어서 사용하는 것을 권장. main이나 sub나 인자를 넣어서(?) 해당 BitMapManager를 사용하도록
	//BitMapManager* m_BitMapMgr_Main;
	//BitMapManager* m_BitMapMgr_Sub;
	//BitMapManager* m_BitMapMgr_Sub_Promotion;

	//SubPromotion 등록하기 위해
	int nCmdShow;
	LPCTSTR IpszClassSub_Promotion;
	HINSTANCE hInstance;
	
	//CAMP_NONE = -1, CAMP_WHITE, CAMP_BLACK 을 이용해서 해당 칸에 말이 있는지 어떤 팀인지 판단 가능
	CAMP m_Map[BOARD_X][BOARD_Y];
	//현재 플레이어 턴 확인
	CAMP m_PlayerTurn;
	bool m_GameStopCheck;
	bool m_GameEndCheck;
	RECT exitRect; //메인

	//--- Chess 네트워크 추가 ---
	//딜레이되면 콜라이더 체크(클릭) 못하게 막는다.
	//bool isWaitlayer, isDelay; 
	PLYAERSTATE m_PalyerState;
	int m_moved_iX, m_moved_iY; //마지막으로 움직인 말의_ 움직이기 전의 말의 위치.
	RECT m_moveRect; //마지막으로 움직인 말의_ 움직인 위치

	bool isSend_Sever; //서버에 데이터 보낼 순간 체크
	bool isPromotion;
	bool isWinCheck; //승패가 났는지 확인
	CAMP winTeam; //승리한 팀
	//------------------------

	GameManager();

	//보드판 그리기
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
	//현재 턴과 반대되는 턴을 세팅해준다.
	void Set_PlayerTurn() { m_PlayerTurn = (m_PlayerTurn == CAMP_WHITE) ? CAMP_BLACK : CAMP_WHITE; }
	void Set_GameStopCheck(bool check) { m_GameStopCheck = check; }
	void Set_GameEndCheck(bool check) { m_GameEndCheck = check; }

	HBITMAP MyCreateDIBSection(HDC hdc, int width, int height);


	//--- Chess 네트워크 추가 ---
	//접속 지연
	void DelayAccess(CAMP playerTeam);
	//턴 지연
	void SetDelayTurn(); 
	//내 턴인지 상대 턴인지 설정
	void SetTurn(CAMP nowTurn);



	PLYAERSTATE GetPlayerState() { return m_PalyerState; }
	
	//----------말 움직이는 데이터 전달 위해------------
	void Set_moveData(int _x, int _y, RECT _moveRect) { m_moved_iX = _x; m_moved_iY = _y; m_moveRect = _moveRect; }
	

	//움직이기 전 좌표 + 움직일 위치 RECT 서버측에 보내주기로
	void SetMoveData_ToServer(int& _x, int& _y, RECT& _moveRect)
	{
		_x = m_moved_iX; 
		_y = m_moved_iY; 
		_moveRect = m_moveRect; 
	}

	//순서, 접속 대기
	void DrawTurnState(HDC hdc_Main);

	

	//플레이어가 턴을 끝내고 데이터를 서버에 한번만 보내기 위해
	bool Get_IsSend_Sever() { return isSend_Sever; }
	void Set_IsSend_Sever(bool _isSend_Sever) { isSend_Sever = _isSend_Sever; }

	//이번 턴이 승진 진행하는 턴인지 확인
	bool Get_IsPromotion() { return isPromotion; }
	void Set_IsPromotion(bool _isPromotion) { isPromotion = _isPromotion; }

	//플레이어 상태 체크
	PLYAERSTATE Get_PalyerState() { return m_PalyerState; }


	//-----승패------
	void Set_IsWinCheck(bool _isWinCheck) { isWinCheck = _isWinCheck; }
	bool Get_IsWinCheck() { return isWinCheck; }
	
	void Set_WinTeam(CAMP _winTeam) { winTeam = _winTeam; }


	//--기존 코드 수정--
	//더블 버퍼링 - 순서(서브)창 관련
	RECT Get_ClientRect_Sub() { return clientRect_Sub; }
	//RECT Get_ClientRect_Sub_Promotion() { return clientRect_Sub_Promotion; }
};
