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
	//�κ��丮 ��ǥ ������
	UI_INVENTORY_X = ENGINE::ClientSize_Width / 8,
	UI_INVENTORY_Y = 25,
	//�κ��丮 ���� ������ ���/��� ��ǥ ������
	UI_INVENTORY_ITEMUSE_X = UI_INVENTORY_X + 200,
	UI_INVENTORY_ITEMUSE_Y = UI_INVENTORY_Y + 25,
	//�κ��丮 ���� ������ �̹��� + ������ ��ǥ ������
	UI_INVENTORY_ITEMDETAIL_X = UI_INVENTORY_X + 5,
	UI_INVENTORY_ITEMDETAIL_Y = UI_INVENTORY_Y + 5,
	//�κ��丮 ���� ������ �̹��� ��ġ
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
	//�⺻ �������� ��ư�� �ؽ�Ʈ
	FONT_SELECT_X = 40,
	FONT_SELECT_Y = 11,

	//�κ��丮 > �������� �ؽ�Ʈ
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
		HFONT font[FONT_COUNT]; //���� ũ�� ����

		GUIManager();
	public:

		~GUIManager();
		void Initialize();
		void Clear();
		void Update();
		void Draw();


		//TODO::�߰� �������� �ڵ�
		//�÷��̾�� ��ġ�� object ����
		void SelectOptional(std::vector<Object*>* interObject);
		//�÷��̾�� ��ġ�� ������ object�� index�� �����ϴ� ���
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