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
		///-----------------------------�߰� ��������------------------------------------------

		pauseWindow = UIMgr->AddUI<UIImage>("Optional Form");
		if (pauseWindow)
		{
			pauseWindow->Initialize("base_panel.bmp", DrawType::Transparent);
			//>
			pauseWindow->SetPosition(bounds * 0.5f, SceneMgr->GetHeight() * 0.5f, TRUE);

			UIButton* Btn_1st = UIMgr->AddUI<UIButton>("Optional 1 Btn", pauseWindow);
			Btn_1st->Initialize("continue_normal.bmp", "continue_pressed.bmp", "", "", DrawType::Transparent); //TODO::�ӽ÷� ����Ѵ�. �� �̹��� �����ð�.
			Btn_1st->SetLocalPosition(pauseWindow->GetSize().cx * 0.5f, pauseWindow->GetSize().cy * 0.5f - 100, true); //TODO::�̰� ������ �������� ��ġ �޶����� ��
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