#pragma once
#include "Singleton.h"
#include "Object.h"

enum UI_SELECT
{
	UI_SELECT_X = ENGINE::ClientSize_Width - 120,
	UI_SELECT_Y = ENGINE::ClientSize_Height - 120,
};

enum UI_INVENTORY
{
	//인벤토리 좌표 설정값
	UI_INVENTORY_X = ENGINE::ClientSize_Width / 8,
	UI_INVENTORY_Y = 25,
	//인벤토리 내에 아이템 사용/취소 좌표 설정값
	UI_INVENTORY_ITEMUSE_X = UI_INVENTORY_X + 200,
	UI_INVENTORY_ITEMUSE_Y = UI_INVENTORY_Y + 25,
	//인벤토리 내에 아이템 이미지 + 상세정보 좌표 설정값
	UI_INVENTORY_ITEMDETAIL_X = UI_INVENTORY_X + 5,
	UI_INVENTORY_ITEMDETAIL_Y = UI_INVENTORY_Y + 5,
	//인벤토리 내에 아이템 이미지 위치
	UI_INVENTORY_ITEMIMAGE_X = UI_INVENTORY_ITEMUSE_X - 105,
	UI_INVENTORY_ITEMIMAGE_Y = UI_INVENTORY_ITEMUSE_Y
};

enum FONT
{
	//FONT_GAMENAME,
	//FONT_START_EXIT,
	//FONT_STORY,
	FONT_SELECT,
	FONT_STATE,
	FONT_UNDERTXT,
	//FONT_NEXT,
	//FONT_CLOCK,
	//FONT_GAMECLEAR,

	FONT_COUNT,
};

enum FONT_XY
{
	//기본 선택지나 버튼의 텍스트
	FONT_SELECT_X = 40,
	FONT_SELECT_Y = 11,

	//인벤토리 > 아이템의 텍스트
	FONT_ITEM_DETAL_X = 100,
};

enum FONTSIZE
{
	/*FONTSIZE_GAMENAME = 50,
	FONTSIZE_START_EXIT = 18,
	FONTSIZE_STORY = 14,*/
	FONTSIZE_SELECT = 12,
	FONTSIZE_STATE = 11,
	FONTSIZE_UNDERTXT = 12,
	/*FONTSIZE_NEXT = 15,
	FONTSIZE_CLOCK = 25,
	FONTSIZE_GAMECLEAR = 25,*/
};


namespace ENGINE
{
	class GUIManager : public Singleton<GUIManager>
	{
	private:
		//BOOL isPause;
		UIImage* select_UI;
		HFONT font[FONT_COUNT]; //글자 크기 변경

		GUIManager();
	public:

		~GUIManager();
		void Initialize();
		void Clear();
		void Update();
		void Draw();


		//TODO::추가 진행중인 코드
		//플레이어와 겹치는 object 선택
		void SelectOptional(std::vector<Object*>* interObject);
		//플레이어와 겹치는 가로축 object의 index를 선택하는 양식
		void OptionalForm(std::vector<Object*>* interObject);

		void SelectBtnClickHandler(Object* interObject);
		void CancelBtnClickHandler();

		/*void Set_IsPause(bool pauseSet) { isPause = pauseSet; }
		bool Get_IsPause() { return isPause; }*/
		HFONT Get_Font(FONT fontStyle) { return font[fontStyle]; }
		friend Singleton;

	#define GUIMgr GUIManager::GetInstance()
	};
}