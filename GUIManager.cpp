#include "GUIManager.h"

namespace ENGINE
{
	GUIManager::GUIManager()
	{

	}


	GUIManager::~GUIManager()
	{

	}


	void GUIManager::OptionalForm()
	{
		///-----------------------------추가 진행중인------------------------------------------

		pauseWindow = UIMgr->AddUI<UIImage>("Optional Form");
		if (pauseWindow)
		{
			pauseWindow->Initialize("base_panel.bmp", DrawType::Transparent);
			//>
			pauseWindow->SetPosition(bounds * 0.5f, SceneMgr->GetHeight() * 0.5f, TRUE);

			UIButton* Btn_1st = UIMgr->AddUI<UIButton>("Optional 1 Btn", pauseWindow);
			Btn_1st->Initialize("continue_normal.bmp", "continue_pressed.bmp", "", "", DrawType::Transparent); //TODO::임시로 사용한다. 새 이미지 만들어올것.
			Btn_1st->SetLocalPosition(pauseWindow->GetSize().cx * 0.5f, pauseWindow->GetSize().cy * 0.5f - 100, true); //TODO::이거 선택지 개수별로 수치 달라져야 함
			Btn_1st->SetListener(std::bind(&DemoScene::ContinueBtnClickHandler, this));


			///

			UIButton* continueBtn = UIMgr->AddUI<UIButton>("Continue Btn", pauseWindow);
			continueBtn->Initialize("continue_normal.bmp", "continue_pressed.bmp", "", "", DrawType::Transparent);
			continueBtn->SetLocalPosition(pauseWindow->GetSize().cx * 0.5f, pauseWindow->GetSize().cy * 0.5f - 100, true);
			continueBtn->SetListener(std::bind(&DemoScene::ContinueBtnClickHandler, this));

			UIButton* quitBtn = UIMgr->AddUI<UIButton>("Quit Btn", pauseWindow);
			quitBtn->Initialize("quit_normal.bmp", "quit_pressed.bmp", "", "", DrawType::Transparent);
			quitBtn->SetLocalPosition(pauseWindow->GetSize().cx * 0.5f, pauseWindow->GetSize().cy * 0.5f + 50, true);
			quitBtn->SetListener(std::bind(&DemoScene::QuitBtnClickHandler, this));

			pauseWindow->SetEnable(FALSE);
		}
	}
}