#include "GUIManager.h"
#include "ObjectManager.h"

namespace ENGINE
{
	GUIManager::GUIManager()
	{

	}


	GUIManager::~GUIManager()
	{

	}

	int GUIManager::SelectOptional(Object** objectIndexs, int inter_Count)
	{
		OptionalForm(objectIndexs, inter_Count);

		//TODO::���ÿ� ���� ���ϰ� �ٸ���

		return 0;
	}


	void GUIManager::OptionalForm(Object** objectIndexs, int inter_Count)
	{
		///-----------------------------�߰� ��������------------------------------------------

		select_UI = UIMgr->AddUI<UIImage>("Optional Form");

		if (select_UI)
		{
			int i;

			select_UI->Initialize("base_panel.bmp", DrawType::Transparent);
			//>
			select_UI->SetPosition(SceneMgr->GetWidth() * 0.5f, SceneMgr->GetHeight() * 0.5f, TRUE);


			for (i = 0; i < inter_Count; i++)
			{
				UIButton* btn_1st = UIMgr->AddUI<UIButton>("Optional " + std::to_string(i) + " Btn", select_UI);
				btn_1st->Initialize("continue_normal.bmp", "continue_pressed.bmp", "", "", DrawType::Transparent); //TODO::�ӽ÷� ����Ѵ�. �� �̹��� �����ð�.
				btn_1st->SetLocalPosition(select_UI->GetSize().cx * 0.5f, select_UI->GetSize().cy * 0.5f - 100, true); //TODO::�̰� ������ �������� ��ġ �޶����� ��
				btn_1st->SetListener(std::bind(&GUIManager::SelectBtnClickHandler, this, objectIndexs, i));
				//btn_1st->SetListener(std::bind(&GUIManager::SelectBtnClickHandler, this, i));
			}



			///

			UIButton* btn_Cancel = UIMgr->AddUI<UIButton>("Cancel Btn", select_UI);
			btn_Cancel->Initialize("continue_normal.bmp", "continue_pressed.bmp", "", "", DrawType::Transparent);
			btn_Cancel->SetLocalPosition(select_UI->GetSize().cx * 0.5f, select_UI->GetSize().cy * 0.5f - 100, true);
			btn_Cancel->SetListener(std::bind(&GUIManager::CancelBtnClickHandler, this));

			select_UI->SetEnable(FALSE);
		}
	}



	void GUIManager::SelectBtnClickHandler(Object** objectIndexs, int select)
	{
		//objectIndexs[select].

		ObjectMgr->ChangeActiveState(objectIndexs[select]);
		//PostQuitMessage(0);
	}

	void GUIManager::CancelBtnClickHandler()
	{
		//pauseWindow->SetEnable(FALSE);
		//pauseBtn->SetInteracterble(TRUE);
		//isPause = FALSE;
	}

}