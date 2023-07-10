#pragma once
#include "Singleton.h"
#include "Object.h"

enum UI_SELECT
{
	UI_SELECT_X = ENGINE::ClientSize_Width - 120,
	UI_SELECT_Y = ENGINE::ClientSize_Height - 120,
};

enum FONT
{
	FONT_GAMENAME,
	FONT_START_EXIT,
	FONT_STORY,
	FONT_SELECT,
	FONT_NEXT,
	FONT_CLOCK,
	FONT_GAMECLEAR,

	FONT_COUNT,
};

enum FONT_XY
{
	FONT_SELECT_X = 40,
	FONT_SELECT_Y = 11,
};

enum FONTSIZE
{
	FONTSIZE_GAMENAME = 50,
	FONTSIZE_START_EXIT = 18,
	FONTSIZE_STORY = 14,
	FONTSIZE_SELECT = 12,
	FONTSIZE_NEXT = 15,
	FONTSIZE_CLOCK = 25,
	FONTSIZE_GAMECLEAR = 25,
};


namespace ENGINE
{
	class GUIManager : public Singleton<GUIManager>
	{
	private:
		BOOL isPause;
		UIImage* select_UI;

		GUIManager();
	public:
		HFONT font[FONT_COUNT]; //글자 크기 변경

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

		void Set_IsPause(bool pauseSet) { isPause = pauseSet; }
		bool Get_IsPause() { return isPause; }
		friend Singleton;

	#define GUIMgr GUIManager::GetInstance()
	};
}