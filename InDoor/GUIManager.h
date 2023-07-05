#pragma once
#include "Singleton.h"
#include "Object.h"

enum UI_SELECT
{
	UI_SELECT_X = ENGINE::ClientSize_Width - 10,
	UI_SELECT_Y = ENGINE::ClientSize_Height - 40,
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
		~GUIManager();
		void Initialize();
		void Clear();
		void Update();
		void Draw();


		//TODO::�߰� �������� �ڵ�
		//�÷��̾�� ��ġ�� object ����
		void SelectOptional(std::vector<Object>& interObject);
		//�÷��̾�� ��ġ�� ������ object�� index�� �����ϴ� ���
		void OptionalForm(std::vector<Object>& interObject);

		void SelectBtnClickHandler(Object* objectIndexs, int select);
		void CancelBtnClickHandler();

		bool Get_IsPause() { return isPause; }
		friend Singleton;

	#define GUIMgr GUIManager::GetInstance()
	};
}