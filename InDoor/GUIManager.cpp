#include "GUIManager.h"
#include "ObjectManager.h"
#include "UIManager.h"

namespace ENGINE
{
	GUIManager::GUIManager()
	{

	}


	GUIManager::~GUIManager()
	{

	}


	void GUIManager::Initialize()
	{
		UIMgr->Initialize();
	}
	void GUIManager::Clear()
	{
		UIMgr->Clear();
	}
	void GUIManager::Update()
	{
		UIMgr->Update();
	}
	void GUIManager::Draw()
	{
		UIMgr->Draw();
	}

	//TODO::void로 변경
	void GUIManager::SelectOptional(std::vector<Object>& interObject)
	{
		OptionalForm(interObject);
		select_UI->SetEnable(TRUE);

		//TODO::선택에 따라 리턴값 다르게

		//return 0;
	}


	void GUIManager::OptionalForm(std::vector<Object>& interObject)
	{
		///-----------------------------추가 진행중인------------------------------------------
		int interCount = interObject.size();

		switch (interCount)
		{
		case 1:
			select_UI = UIMgr->AddUI<UIImage>("Optional Form_2");
			break;
		case 2:
			select_UI = UIMgr->AddUI<UIImage>("Optional Form_3");
			break;
		case 3:
			select_UI = UIMgr->AddUI<UIImage>("Optional Form_4");
			break;
		}


		 
		if (select_UI)
		{
			int i, selectBtn_X, selectBtn_Y;
			isPause = TRUE;

			switch (interCount)
			{
			case 1:
				select_UI->Initialize("Select_Panel_2.bmp", DrawType::Transparent);
				break;
			case 2:
				select_UI->Initialize("Select_Panel_3.bmp", DrawType::Transparent);
				break;
			case 3:
				select_UI->Initialize("Select_Panel_4.bmp", DrawType::Transparent);
				break;
			}

			//select_UI->Initialize("base_panel.bmp", DrawType::Transparent);
			//>
			//select_UI->SetPosition(SceneMgr->GetWidth() * 0.5f, SceneMgr->GetHeight() * 0.5f + 50, TRUE);
			select_UI->SetPosition(UI_SELECT_X - 60, UI_SELECT_Y - 40, TRUE);

			selectBtn_X = select_UI->GetSize().cx * 0.5f;
			selectBtn_Y = select_UI->GetSize().cy * 0.5f - 25;


			for (i = 0; i < interCount; i++)
			{
				//UIButton* btn_select = UIMgr->AddUI<UIButton>("Optional " + std::to_string(i) + " Btn", select_UI);
				UIButton* btn_select = UIMgr->AddUI<UIButton>("Optional " + interObject[i].GetObjectName() + " Btn", select_UI); //파일 이름으로 구분 ex.Home_Flowerpot.bmp
				btn_select->Initialize("Select_Btn_Normal.bmp", "Select_Btn_Pressed.bmp", "", "", DrawType::Transparent);
				btn_select->SetLocalPosition(selectBtn_X, selectBtn_Y, true);
				btn_select->SetListener(std::bind(&GUIManager::SelectBtnClickHandler, this, &interObject[i], i));

				selectBtn_Y += 25;
				//btn_select->SetListener(std::bind(&GUIManager::SelectBtnClickHandler, this, i));
			}



			///

			UIButton* btn_Cancel = UIMgr->AddUI<UIButton>("Cancel Btn", select_UI);
			btn_Cancel->Initialize("Select_Btn_Normal.bmp", "Select_Btn_Pressed.bmp", "", "", DrawType::Transparent);
			//btn_Cancel->Initialize("pause_normal.bmp", "pause_normal.bmp", "", "", DrawType::Transparent);
			btn_Cancel->SetLocalPosition(selectBtn_X, selectBtn_Y, true);
			btn_Cancel->SetListener(std::bind(&GUIManager::CancelBtnClickHandler, this));

			//select_UI->SetEnable(FALSE);
		}
	}



	void GUIManager::SelectBtnClickHandler(Object* objectIndexs, int select)
	{
		//objectIndexs[select].
		ObjectMgr->ChangeActiveState(objectIndexs[select]);
		isPause = FALSE;
		//PostQuitMessage(0);
	}

	void GUIManager::CancelBtnClickHandler()
	{
		select_UI->SetEnable(FALSE);
		//pauseBtn->SetInteracterble(TRUE);
		isPause = FALSE;
	}

}