#include "GUIManager.h"
#include "ObjectManager.h"
//#include "UIManager.h"

namespace ENGINE
{
	GUIManager::GUIManager()
	{
		/*font[FONT_GAMENAME] = CreateFont(FONTSIZE_GAMENAME, 0, 0, 0, FW_THIN, 0, 0, 0, HANGEUL_CHARSET, 0, 0, PROOF_QUALITY, 0, L"Times New Roman");
		font[FONT_START_EXIT] = CreateFont(FONTSIZE_START_EXIT, 0, 0, 0, FW_SEMIBOLD, 0, 0, 0, HANGEUL_CHARSET, 0, 0, PROOF_QUALITY, 0, L"Times New Roman");
		font[FONT_STORY] = CreateFont(FONTSIZE_STORY, 0, 0, 0, FW_THIN, 0, 0, 0, HANGEUL_CHARSET, 0, 0, PROOF_QUALITY, 0, L"Times New Roman");*/
		font[FONT_SELECT] = CreateFont(FONTSIZE_SELECT, 0, 0, 0, FW_THIN, 0, 0, 0, HANGEUL_CHARSET, 0, 0, PROOF_QUALITY, 0, L"Times New Roman");
		font[FONT_STATE] = CreateFont(FONTSIZE_STATE, 0, 0, 0, FW_THIN, 0, 0, 0, HANGEUL_CHARSET, 0, 0, PROOF_QUALITY, 0, L"Times New Roman");
		font[FONT_UNDERTXT] = CreateFont(FONTSIZE_UNDERTXT, 0, 0, 0, FW_THIN, 0, 0, 0, HANGEUL_CHARSET, 0, 0, PROOF_QUALITY, 0, L"Times New Roman");
		//font[FONT_NEXT] = CreateFont(FONTSIZE_NEXT, 0, 0, 0, FW_THIN, 0, 0, 0, HANGEUL_CHARSET, 0, 0, PROOF_QUALITY, 0, L"Times New Roman");
		//font[FONT_CLOCK] = CreateFont(FONTSIZE_CLOCK, 0, 0, 0, FW_THIN, 0, 0, 0, HANGEUL_CHARSET, 0, 0, PROOF_QUALITY, 0, L"Times New Roman");
		//font[FONT_GAMECLEAR] = CreateFont(FONTSIZE_GAMECLEAR, 0, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 0, 0, PROOF_QUALITY, 0, L"궁서");
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
	void GUIManager::SelectOptional(std::vector<Object*>* interObject)
	{
		OptionalForm(interObject);
		select_UI->SetEnable(TRUE);

		//TODO::선택에 따라 리턴값 다르게

		//return 0;
	}


	void GUIManager::OptionalForm(std::vector<Object*>* interObject)
	{
		//std::vector<Object*>* interObject 포인터를 역참조한 후에 멤버 함수에 접근
		int interCount = (*interObject).size();

		// 기존의 선택지 UI 삭제
		//if (select_UI)
		//{
		//	UIMgr->Remove(select_UI->GetName());
		//	select_UI = nullptr;
		//}

		switch (interCount)
		{
		case 1:
			UIMgr->Remove("Optional Form_2");
			select_UI = nullptr;
			select_UI = UIMgr->AddUI<UIImage>("Optional Form_2");
			select_UI->Initialize("Select_Panel_2.bmp", DrawType::Transparent);
			break;
		case 2:
			UIMgr->Remove("Optional Form_3");
			select_UI = nullptr;
			select_UI = UIMgr->AddUI<UIImage>("Optional Form_3");
			select_UI->Initialize("Select_Panel_3.bmp", DrawType::Transparent);
			break;
		case 3:
			UIMgr->Remove("Optional Form_4");
			select_UI = nullptr;
			select_UI = UIMgr->AddUI<UIImage>("Optional Form_4");
			select_UI->Initialize("Select_Panel_4.bmp", DrawType::Transparent);
			break;
		}


		if (select_UI)
		{
			int i, selectBtn_X, selectBtn_Y;
			isPause = TRUE;

			//select_UI->Initialize("base_panel.bmp", DrawType::Transparent);
			//>
			//select_UI->SetPosition(SceneMgr->GetWidth() * 0.5f, SceneMgr->GetHeight() * 0.5f + 50, TRUE);
			select_UI->SetPosition(UI_SELECT_X, UI_SELECT_Y, false);

			selectBtn_X = select_UI->GetSize().cx * 0.5f;
			selectBtn_Y = 17;
			//selectBtn_Y = select_UI->GetSize().cy * 0.25f;


			for (i = 0; i < interCount; i++)
			{
				//버튼-선택지
				UIButton* btn_select = UIMgr->AddUI<UIButton>("Optional " + std::to_string(i + 1) + "_" + (*interObject)[i]->GetObjectName() + " Btn", select_UI); //파일 이름으로 구분 ex.Home_Flowerpot.bmp
				//UIButton* btn_select = UIMgr->AddUI<UIButton>("Optional " + interObject[i]->GetObjectName() + " Btn", select_UI); //파일 이름으로 구분 ex.Home_Flowerpot.bmp
				btn_select->Initialize("Select_Btn_Normal.bmp", "Select_Btn_Pressed.bmp", "", "", DrawType::Transparent);
				btn_select->SetLocalPosition(selectBtn_X, selectBtn_Y, true);
				/*btn_select->SetListener([this, interObject, i]() {
					SelectBtnClickHandler((*interObject)[i]);
					});*/
				btn_select->SetListener(std::bind(&GUIManager::SelectBtnClickHandler, this, (*interObject)[i]));

				//선택지 문구
				UILabel* btn_txt = UIMgr->AddUI<UILabel>((*interObject)[i]->GetObjectName() + "Txt", btn_select);
				btn_txt->SetLocalPosition(FONT_SELECT_X, FONT_SELECT_Y, true);
				btn_txt->Initialize((*interObject)[i]->GetEachObjectIndex().name, RGB(255, 255, 205), font[FONT_SELECT]);

				selectBtn_Y += 25;
				//btn_select->SetListener(std::bind(&GUIManager::SelectBtnClickHandler, this, i));
			}



			///

			UIButton* btn_Cancel = UIMgr->AddUI<UIButton>("CancelBtn_Panel_" + std::to_string(i + 1), select_UI);
			btn_Cancel->Initialize("Select_Btn_Normal.bmp", "Select_Btn_Pressed.bmp", "", "", DrawType::Transparent);
			//btn_Cancel->Initialize("pause_normal.bmp", "pause_normal.bmp", "", "", DrawType::Transparent);
			btn_Cancel->SetLocalPosition(selectBtn_X, selectBtn_Y, true);
			btn_Cancel->SetListener(std::bind(&GUIManager::CancelBtnClickHandler, this));

			//선택지 문구
			UILabel* btnCancel_txt = UIMgr->AddUI<UILabel>("Cancel_Txt" + std::to_string(i + 1), btn_Cancel);
			btnCancel_txt->SetLocalPosition(FONT_SELECT_X, FONT_SELECT_Y, true);
			btnCancel_txt->Initialize("취소", RGB(255, 255, 255), font[FONT_SELECT]);
			//btnCancel_txt->SetText("취소");

			//select_UI->SetEnable(FALSE);
		}
	}



	void GUIManager::SelectBtnClickHandler(Object* interObject)
	{
		//ObjectMgr->ChangeActiveState(interObject);
		interObject->DetailSelectForm();

		//TODO::상세 선택지 쪽으로 이사가야함? 아닐 것으로 봄
		select_UI->SetEnable(FALSE);
		//isPause = FALSE;
	}

	void GUIManager::CancelBtnClickHandler()
	{
		select_UI->SetEnable(FALSE);
		//pauseBtn->SetInteracterble(TRUE);
		isPause = FALSE;
	}
}