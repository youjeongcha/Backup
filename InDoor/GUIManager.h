#pragma once
#include "Singleton.h"
#include "UIManager.h"
#include "Object.h"

namespace ENGINE
{
	class GUIManager : public Singleton<GUIManager>
	{
	private:
		UIImage* select_UI;


		GUIManager();
	public:
		~GUIManager();
		//TODO::�߰� �������� �ڵ�
		//�÷��̾�� ��ġ�� object ����
		int SelectOptional(Object** objectIndexs, int inter_Count);
		//�÷��̾�� ��ġ�� ������ object�� index�� �����ϴ� ���
		void OptionalForm(Object** objectIndexs, int inter_Count);

		void SelectBtnClickHandler(Object** objectIndexs, int select);
		void CancelBtnClickHandler();


		friend Singleton;

	#define GUIMgr GUIManager::GetInstance()
	};
}