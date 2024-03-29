#include "GameManager.h"

GameManager::GameManager()
{
	Inventory_UI = nullptr;
	Inventory_UI_ItemDetaiInfo = nullptr;
	Inventory_UI_ItemUseSelect = nullptr;
	underTxt_Section = nullptr;


	//TXT 파일 읽어오기
	LoadData();
	LoadUnderTxt();
	LoadCook();

	//이미지 리소스 로드 : 인벤토리 + 아이템
	ENGINE::ResourceMgr->Load("Inventory_panel.bmp");
	ENGINE::ResourceMgr->Load("Inventory_Btn_Pressed.bmp");
	ENGINE::ResourceMgr->Load("Inventory_Btn_Normal.bmp");
	ENGINE::ResourceMgr->Load("Inventory_panel_Select.bmp");
	ENGINE::ResourceMgr->Load("Inventory_panel_Detail.bmp");

	//밤낮
	ENGINE::ResourceMgr->Load("Night.bmp");
	/*window_Night = ENGINE::ResourceMgr->GetBitmap("Night.bmp");
	window_Night->SetDrawSize(ENGINE::SceneMgr->GetWidth(), ENGINE::SceneMgr->GetHeight());*/

	window_Night = ENGINE::UIMgr->AddUI<ENGINE::UIButton>("Night.Btn");
	window_Night->Initialize("Night.bmp", "Night.bmp", "", "", ENGINE::DrawType::Transparent);
	window_Night->SetLocalPosition(0, 0, false);
	window_Night->SetListener(std::bind(&GameManager::CancelShowWindow, this));
	/*window_Night = ENGINE::SceneMgr->GetWidth() - window_Night->GetSize().cx * 1.55;
	window_Night = ENGINE::SceneMgr->GetHeight() / 2 - window_Night->GetSize().cy;*/

	ENGINE::ResourceMgr->Load("Morning.bmp");
	window_Morning = ENGINE::UIMgr->AddUI<ENGINE::UIButton>("Morning.Btn");
	window_Morning->Initialize("Morning.bmp", "Morning.bmp", "", "", ENGINE::DrawType::Transparent);
	window_Morning->SetLocalPosition(0, 0, false);
	window_Morning->SetListener(std::bind(&GameManager::CancelShowWindow, this));
	//window_Morning = ENGINE::ResourceMgr->GetBitmap("Morning.bmp");
	//window_Morning->SetDrawSize(ENGINE::SceneMgr->GetWidth(), ENGINE::SceneMgr->GetHeight());

	//Night and GameOver and Sleep
	ENGINE::ResourceMgr->Load("Black.bmp");
	night = ENGINE::ResourceMgr->GetBitmap("Black.bmp");
	night->SetDrawSize(ENGINE::SceneMgr->GetWidth(), ENGINE::SceneMgr->GetHeight());

	//ENGINE::ResourceMgr->Load("UnderSection.bmp");
	//underSection = ENGINE::ResourceMgr->GetBitmap("UnderSection.bmp");
	//underSection->SetDrawSize(ENGINE::SceneMgr->GetWidth(), 30);

	//시간 체크
	timeLabel = ENGINE::UIMgr->AddUI<ENGINE::UILabel>("Time Label");
	timeLabel->Initialize("", RGB(255, 255, 255), ENGINE::GUIMgr->Get_Font(FONT_STATE));
	timeLabel->SetPosition(10, 10); // 원하는 위치로 설정

	ENGINE::ResourceMgr->Load("UnderSection.bmp");
	underTxt_Section = ENGINE::UIMgr->AddUI<ENGINE::UIButton>("Under Btn"); //파일 이름으로 구분
	underTxt_Section->Initialize("UnderSection.bmp", "UnderSection.bmp", "", "", ENGINE::DrawType::AlphaBlend);
	underTxt_Section->SetLocalPosition(0, ENGINE::SceneMgr->GetHeight() - underTxt_Section->GetSize().cy, false);
	underTxt_Section->SetListener(std::bind(&GameManager::NextShowUnderSection, this, false));

	//하단 텍스트 문구
	txtLabel = ENGINE::UIMgr->AddUI<ENGINE::UILabel>("Txt Label", underTxt_Section);
	txtLabel->Initialize("", RGB(255, 255, 255), ENGINE::GUIMgr->Get_Font(FONT_UNDERTXT));
	txtLabel->SetPosition(ENGINE::SceneMgr->GetWidth() / 3, ENGINE::SceneMgr->GetHeight() - 20); // 원하는 위치로 설정


	//GameOver
	ENGINE::ResourceMgr->Load("GameOver.bmp");
	gameOver = ENGINE::ResourceMgr->GetBitmap("GameOver.bmp");
	//좌표
	gameOver_X = ENGINE::SceneMgr->GetWidth() - gameOver->GetSize().cx * 1.55;
	gameOver_Y = ENGINE::SceneMgr->GetHeight() / 2 - gameOver->GetSize().cy;


	//게임 오버 선택지
	ENGINE::ResourceMgr->Load("Select_Panel.bmp");
	ENGINE::UIMgr->Remove("Optional Form_GameOver");
	select_Restart = ENGINE::UIMgr->AddUI<ENGINE::UIImage>("Optional Form_GameOver");
	select_Restart->Initialize("Select_Panel.bmp", ENGINE::DrawType::Transparent);
	select_Restart->SetLocalPosition(ENGINE::SceneMgr->GetWidth() - select_Restart->GetSize().cx * 1.95, gameOver_Y + 55, true);

	int selectBtn_X, selectBtn_Y;
	selectBtn_X = select_Restart->GetSize().cx * 0.5f;
	selectBtn_Y = 13;

	//재시작 - 버튼
	ENGINE::ResourceMgr->Load("Btn_Restart_Normal.bmp");
	ENGINE::ResourceMgr->Load("Btn_Restart_Pressed.bmp");
	ENGINE::UIButton* btn_Restart = ENGINE::UIMgr->AddUI<ENGINE::UIButton>("Optional Restart Btn", select_Restart);
	btn_Restart->Initialize("Btn_Restart_Normal.bmp", "Btn_Restart_Pressed.bmp", "", "", ENGINE::DrawType::Transparent);
	btn_Restart->SetLocalPosition(selectBtn_X, selectBtn_Y, true);
	btn_Restart->SetListener(std::bind(&GameManager::Restart, this));

	//재시작 - 선택지 문구
	ENGINE::UILabel* btn_Restarttxt = ENGINE::UIMgr->AddUI<ENGINE::UILabel>("Restart Txt", btn_Restart);
	btn_Restarttxt->SetLocalPosition(FONT_SELECT_X, FONT_SELECT_Y, true);
	btn_Restarttxt->Initialize("재시작", RGB(255, 255, 255), ENGINE::GUIMgr->Get_Font(FONT_SELECT));


	//----게임 오버 선택지----
	ENGINE::UIMgr->Remove("Optional Form_End");
	select_End = ENGINE::UIMgr->AddUI<ENGINE::UIImage>("Optional Form_End");
	select_End->Initialize("Select_Panel.bmp", ENGINE::DrawType::Transparent);
	select_End->SetLocalPosition(ENGINE::SceneMgr->GetWidth() - select_End->GetSize().cx * 1.95, gameOver_Y + 55, true);

	//게임 종료
	ENGINE::UIButton* btn_GameEnd = ENGINE::UIMgr->AddUI<ENGINE::UIButton>("Optional GameEnd Btn", select_End);
	//btn_GameEnd->Initialize("Btn_Restart_Normal.bmp", "Btn_Restart_Pressed.bmp", "", "", ENGINE::DrawType::Transparent);
	btn_GameEnd->Initialize("Inventory_Btn_Normal.bmp", "Inventory_Btn_Pressed.bmp", "", "", ENGINE::DrawType::Transparent);
	btn_GameEnd->SetLocalPosition(selectBtn_X, selectBtn_Y, true);
	btn_GameEnd->SetListener(std::bind(&GameManager::GameEnd, this));

	//종료 - 선택지 문구
	ENGINE::UILabel* btn_GameEndtxt = ENGINE::UIMgr->AddUI<ENGINE::UILabel>("GameEnd Txt", btn_GameEnd);
	btn_GameEndtxt->SetLocalPosition(FONT_SELECT_X, FONT_SELECT_Y, true);
	btn_GameEndtxt->Initialize("종료", RGB(255, 255, 255), ENGINE::GUIMgr->Get_Font(FONT_SELECT));


	//--------인벤토리--------
	ENGINE::UIMgr->Remove("Inventory");
	Inventory_UI = ENGINE::UIMgr->AddUI<ENGINE::UIImage>("Inventory");
	Inventory_UI->Initialize("Inventory_panel.bmp", ENGINE::DrawType::AlphaBlend); //투명도 조절 가능하게끔
	Inventory_UI->Set_Transparency(INVENTORY_TRANSPARENCY); //투명화 원하는 값(0 ~ 255)

	int cancel_X = Inventory_UI->GetSize().cx * 0.5f;
	int cancel_Y = Inventory_UI->GetSize().cy - 15;

	//----취소 버튼----
	ENGINE::UIButton* btn_Cancel = ENGINE::UIMgr->AddUI<ENGINE::UIButton>("CancelBtn_Panel", Inventory_UI);
	btn_Cancel->Initialize("Inventory_Btn_Normal.bmp", "Inventory_Btn_Pressed.bmp", "", "", ENGINE::DrawType::Transparent);
	btn_Cancel->SetLocalPosition(cancel_X, cancel_Y, true);
	btn_Cancel->SetListener(std::bind(&GameManager::Cancel_InventoryBtnClickHandler, this));
	//취소 문구
	ENGINE::UILabel* btnCancel_txt = ENGINE::UIMgr->AddUI<ENGINE::UILabel>("InventoryCancel_Txt", btn_Cancel);
	btnCancel_txt->SetLocalPosition(FONT_SELECT_X, FONT_SELECT_Y, true);
	btnCancel_txt->Initialize("취소", RGB(255, 255, 255), ENGINE::GUIMgr->Get_Font(FONT_SELECT));

	//----이전 버튼----
	ENGINE::UIButton* btn_Prev = ENGINE::UIMgr->AddUI<ENGINE::UIButton>("Inventory_PrevPage_Btn", Inventory_UI);
	btn_Prev->Initialize("Inventory_Btn_Normal.bmp", "Inventory_Btn_Pressed.bmp", "", "", ENGINE::DrawType::Transparent);
	btn_Prev->SetLocalPosition(cancel_X - btn_Prev->GetSize().cx - 10, cancel_Y, true);
	btn_Prev->SetListener(std::bind(&GameManager::ShowInventoryNextPage, this, false));
	//이전 문구
	ENGINE::UILabel* btnPrev_txt = ENGINE::UIMgr->AddUI<ENGINE::UILabel>("Inventory_PrevPage_Txt", btn_Prev);
	btnPrev_txt->SetLocalPosition(FONT_SELECT_X, FONT_SELECT_Y, true);
	btnPrev_txt->Initialize("이전", RGB(255, 255, 255), ENGINE::GUIMgr->Get_Font(FONT_SELECT));

	//----다음 버튼----
	ENGINE::UIButton* btn_Next = ENGINE::UIMgr->AddUI<ENGINE::UIButton>("Inventory_NextPage_Btn", Inventory_UI);
	btn_Next->Initialize("Inventory_Btn_Normal.bmp", "Inventory_Btn_Pressed.bmp", "", "", ENGINE::DrawType::Transparent);
	btn_Next->SetLocalPosition(cancel_X + btn_Next->GetSize().cx + 10, cancel_Y, true);
	btn_Next->SetListener(std::bind(&GameManager::ShowInventoryNextPage, this, true));
	//다음 문구
	ENGINE::UILabel* btnNext_txt = ENGINE::UIMgr->AddUI<ENGINE::UILabel>("Inventory_NextPage_Txt", btn_Next);
	btnNext_txt->SetLocalPosition(FONT_SELECT_X, FONT_SELECT_Y, true);
	btnNext_txt->Initialize("다음", RGB(255, 255, 255), ENGINE::GUIMgr->Get_Font(FONT_SELECT));

	//---------------------
	//로드해온 Object 데이터 각 Scene마다 Object 관리하는 변수에 세팅
	Restart();
}

GameManager::~GameManager()
{
	// mDoorObject 해제
	for (std::vector<Object*>::iterator iter = mDoorObject.begin(); iter != mDoorObject.end(); ++iter)
	{
		delete* iter;
	}
	mDoorObject.clear();

	// mKitchenObject 해제
	for (std::vector<Object*>::iterator iter = mKitchenObject.begin(); iter != mKitchenObject.end(); ++iter)
	{
		delete* iter;
	}
	mKitchenObject.clear();

	// mBedRoomObject 해제
	for (std::vector<Object*>::iterator iter = mBedRoomObject.begin(); iter != mBedRoomObject.end(); ++iter)
	{
		delete* iter;
	}
	mBedRoomObject.clear();

	// mUnderTxt 해제
	mUnderTxt.clear();

	// player_ItemList 해제
	player_ItemList.clear();


	//// mDoorObject 해제
	//for (std::map<std::string, std::vector<Object*>>::iterator iter = mDoorObject.begin(); iter != mDoorObject.end(); ++iter)
	//{
	//	for (Object* obj : iter->second)
	//	{
	//		delete obj;
	//	}
	//	iter->second.clear();
	//}
	//mDoorObject.clear();

	//// mKitchenObject 해제
	//for (std::map<std::string, std::vector<Object*>>::iterator iter = mKitchenObject.begin(); iter != mKitchenObject.end(); ++iter)
	//{
	//	for (Object* obj : iter->second)
	//	{
	//		delete obj;
	//	}
	//	iter->second.clear();
	//}
	//mKitchenObject.clear();

	//// mBedRoomObject 해제
	//for (std::map<std::string, std::vector<Object*>>::iterator iter = mBedRoomObject.begin(); iter != mBedRoomObject.end(); ++iter)
	//{
	//	for (Object* obj : iter->second)
	//	{
	//		delete obj;
	//	}
	//	iter->second.clear();
	//}
	//mBedRoomObject.clear();

	//// mUnderTxt 해제
	//mUnderTxt.clear();

	//// player_ItemList 해제
	//player_ItemList.clear();
}

void GameManager::Reset_SceneObject()
{

	if (mDoorObject.size() > 0)
	{
		for (std::vector<Object*>::iterator iter = mDoorObject.begin(); iter != mDoorObject.end(); iter++)
		//for (std::map<std::string, std::vector<Object*>>::iterator iter = mDoorObject.begin(); iter != mDoorObject.end(); iter++)
		{
			(*iter)->Initialize();
			//for (Object* obj : iter->second)
			//{
			//	delete obj;
			//}
			//iter->second.clear();
		}
	}
	mDoorObject.clear();

	if (mKitchenObject.size() > 0)
	{
		for (std::vector<Object*>::iterator iter = mKitchenObject.begin(); iter != mKitchenObject.end(); iter++)
		{
			(*iter)->Initialize();
		}
	}
	mKitchenObject.clear();

	if (mBedRoomObject.size() > 0)
	{
		for (std::vector<Object*>::iterator iter = mBedRoomObject.begin(); iter != mBedRoomObject.end(); iter++)
		//for (std::map<std::string, std::vector<Object*>>::iterator iter = mBedRoomObject.begin(); iter != mBedRoomObject.end(); iter++)
		{
			(*iter)->Initialize();
			//iter->second.clear();
		}
	}
	mBedRoomObject.clear();
}

void GameManager::Restart()
{
	isGameOver = false;
	isGameClear = false;
	isReset_OneTime = false;

	isDark = false;
	isShowUnderTxt = false;
	isShowWindow = false;

	timeLabel->SetEnable(true);
	select_Restart->SetEnable(false);
	select_End->SetEnable(false);
	underTxt_Section->SetEnable(false);
	window_Night->SetEnable(false);
	window_Morning->SetEnable(false);
	Inventory_UI->SetEnable(false);
	Inventory_UI->GetChild(Inventory_Page_CancelBtn)->SetEnable(false);
	Inventory_UI->GetChild(Inventory_Page_PrevBtn)->SetEnable(false);
	Inventory_UI->GetChild(Inventory_Page_NextBtn)->SetEnable(false);


	//하단 텍스트 감지 위해 초기 세팅값
	nowShowUnderTxt = UNDERTXT_NONE;
	prevShowUnderTxt = UNDERTXT_NONE;

	//수치 상태
	m_health = 20;
	//m_hunger = 100;
	m_hunger = 30;
	m_thirst = 50;
	m_fatigue = 20;

	//경과 시간
	m_elapsedSec = 0;
	m_elapsedMin = 0;

	//시간 체크
	m_elapsedSec = 0.0f;
	nowTimeLine = TimeLine_MORING; oldTimeLine = TimeLine_MORING;
	//m_Clock.hour = TimeLine_NIGHT - 1;
	m_Clock.hour = TimeLine_MORING + 2;
	m_Clock.min = 0;

	//로드해온 Object 데이터 각 Scene마다 Object 관리하는 변수에 세팅
	Reset_SceneObject();
	//인벤토리 리셋
	player_ItemList.clear();
	Initialize();

	//현재 보여줄 인벤토리 페이지의 인덱스
	Inventory_Index = 0;
}




void GameManager::Initialize()
{
	//멤버 변수 세팅
	InitSceneData(SCENE_DOOR, mDoorObject);
	InitSceneData(SCENE_KITCHEN, mKitchenObject);
	InitSceneData(SCENE_BEDROOM, mBedRoomObject);
}

void GameManager::Draw()
{
	if (isGameOver)
	{
		night->StretchBlt(0, 0);
		gameOver->StretchBlt(gameOver_X, gameOver_Y);
		select_Restart->Draw();
		return;
	}


	//창밖 보기 상태일 경우
	if (isShowWindow)
	{
		if (isDark)
			window_Night->SetEnable(true);
		else
			window_Morning->SetEnable(true);
		return;
	}

	if (isShowUnderTxt)
		ShowUnderSectionTxt(); //선택지를 선택하면 해당 함수에서 세팅을 하고 이쪽으로 들어온다.

	if (isDark)
		night->AlphaBlendBlt(0, 0, ENGINE::SceneMgr->GetHeight() - 30);
}




void GameManager::Update(const FLOAT& deltaTime)
{
	if (isGameOver || isShowWindow)
		return;

	// 시간 표시
	char timeStr[100];
	sprintf_s(timeStr, sizeof(timeStr), "%02d:%02d  건강:%d  허기:%d  갈증:%d  피로:%d", m_Clock.hour, m_Clock.min, GameMgr->GetHealth(), GameMgr->GetHunger(), GameMgr->GetThirst(), GameMgr->GetFatigue());
	timeLabel->SetText(timeStr);

	//시간 경과 카운트
	//경과 시간 업데이트(1초가 게임상 1분)
	m_elapsedSec += deltaTime;
	if (m_elapsedSec >= 1.0f)
	{
		m_elapsedSec -= 1.0f;
		m_elapsedMin += 1.0f;
		m_Clock.min += 1;

		if (m_Clock.min >= 60)
		{
			m_Clock.min -= 60;
			m_Clock.hour += 1;
		}

		//----------플레이어 관련--------------
		// 피로, 허기, 갈증이 100이 되면 > 건강이 1초마다 1씩 깎인다.
		if ((m_fatigue == 100) || (m_thirst == 100) || (m_hunger == 100))
		{
			m_health -= 1;

			//최소치 고정
			if (m_health < 0)
				m_health = 0;
		}
	}


	//24시간 경과 갱신
	if (m_Clock.hour >= TimeLine_ONEDAY)
		m_Clock.hour -= TimeLine_ONEDAY;


	//시간대 기록(낮 밤)
	if ((m_Clock.hour >= TimeLine_MORING) && (m_Clock.hour < TimeLine_NIGHT))
		nowTimeLine = TimeLine_MORING;
	else
		nowTimeLine = TimeLine_NIGHT;




	//낮밤 전환에 따라 단순 BitpMap 바뀌는 요소들
	if ((nowTimeLine == TimeLine_NIGHT) && (oldTimeLine == TimeLine_MORING))
	{//낮 > 밤
		isDark = true;
		ENGINE::ObjectMgr->MoringNight_TimeChangeBitmap();
	}
	else if ((nowTimeLine == TimeLine_MORING) && (oldTimeLine == TimeLine_NIGHT))
	{//밤 > 낮
		isDark = false;
		ENGINE::ObjectMgr->MoringNight_TimeChangeBitmap();
	}


	if (isGameEnd)
	{
		select_End->SetEnable(true);
		return;
	}

	//----------플레이어 관련--------------

	//30분마다 피로, 갈증, 허기 증가
	if (m_elapsedMin >= 30) {
		m_elapsedMin = 0; //경과 시간 초기화

		//피로, 갈증, 허기 증가
		m_fatigue += 5;
		m_thirst += 5;
		m_hunger += 5;

		//피로, 허기, 갈증이 90 이상이 되면 > 건강이 30초마다 5씩 깎인다.
		if ((m_fatigue >= 90) || (m_thirst >= 90) || (m_hunger >= 90))
			m_health -= 5;

		//수치가 최대 최소가 되지 않도록 조정
		if (m_health < 0)
			m_health = 0;
		if (m_fatigue > 100)
			m_fatigue = 100;
		if (m_thirst > 100)
			m_thirst = 100;
		if (m_hunger > 100)
			m_hunger = 100;
	}

	//-------GameOver   or   GameClear(문 열기 가능 체크)-------
	if (m_health == 0)
	{
		isGameOver = true;
		isReset_OneTime = true; //게임오버되고 게임 리셋 함수(맵, 플레이어 위치) 1회 실행
		select_Restart->SetEnable(true);
		timeLabel->SetEnable(false);
	}
	else if (m_health == 100)
		isGameClear = true;
	else //건강이 100미만인 경우
		isGameClear = false;

	oldTimeLine = nowTimeLine;
}

void GameManager::LoadUnderTxt()
{
	// 파일 스트림 열기
	std::ifstream load("Data/UnderTxt.txt");

	// 파일이 성공적으로 열렸는지 확인
	if (load.is_open()) {
		int i = UNDERTXT_START;
		int lineCount;

		while (load >> lineCount && i < UNDERTXT_COUNT) {
			std::string line;
			std::getline(load, line); // 개행 문자 처리

			std::vector<std::string> txt;
			for (int j = 0; j < lineCount; ++j) {
				std::getline(load, line);
				txt.push_back(line);
			}

			mUnderTxt[static_cast<UNDERTXT>(i)] = txt;
			i++;
		}

		// 파일 스트림 닫기
		load.close();
	}
}

void GameManager::ShowUnderSectionTxt()
{ //첫번째 텍스트 뜰때 무조건 거쳐가게 된다.

	//이전 prevShowUnderTxt값과 nowShowUnderTxt 값이 다르면 출력 텍스트가 변화한것이다. 인덱스 카운트 위해 초기 세팅 필요
	if (prevShowUnderTxt != nowShowUnderTxt)
	{
		//이전 값과 현재 값이 달라지는 처음의 순간만 필요
		prevShowUnderTxt = nowShowUnderTxt;

		//출력 시작하는 텍스트 유형과 인덱스
		indexShowUnderTxt = 0;
	}


	//텍스트 사이즈와 현재 출력 인덱스를 비교해서 세팅 해준다.
		//마지막 텍스트 출력
	if (mUnderTxt.find(nowShowUnderTxt)->second.size() == (indexShowUnderTxt + 1)) //size는 1부터 시작 indexShowUnderTxt는 0부터 시작이므로
		underTxt_Section->SetListener(std::bind(&GameManager::NextShowUnderSection, this, false));
	else
		//한줄로 끝내는 텍스트 아니면 이어서 출력하도록 재세팅이 필요하다.
		underTxt_Section->SetListener(std::bind(&GameManager::NextShowUnderSection, this, true));



	//텍스트창을 누르기 전까지 창과 텍스트 유지

	//하단 텍스트창
	underTxt_Section->SetEnable(true);

	underTxt_Section->Set_Transparency(UNDER_SECTION_TRANSPARENCY); //투명화 원하는 값(0 ~ 255)
	underTxt_Section->Draw();

	//하단 텍스트 표시
	txtLabel->SetEnable(true);

	char timeStr[100];
	//sprintf_s(timeStr, sizeof(timeStr), "하단 텍스트를 띄운다.");
	sprintf_s(timeStr, sizeof(timeStr), mUnderTxt.find(nowShowUnderTxt)->second[indexShowUnderTxt].c_str());
	txtLabel->SetText(timeStr);
}

//void GameManager::DisableUnderSection()
void GameManager::NextShowUnderSection(bool isNextTxt)
{ //하단창(버튼)을 누르게 되면 들어오게 되는함수. 한줄 > isNextTxt false / 여러줄 > isNextText true로
	//다음 텍스트 없음 - Object 하단 창
	if (!isNextTxt)
	{
		indexShowUnderTxt = 0;
		isShowUnderTxt = false;
		underTxt_Section->SetEnable(false);
		txtLabel->SetEnable(false);
		Set_IsPause(false);
	}
	else //다음 텍스트 있음 - NPC 하단 창
	{
		//하단창 텍스트 출력 > 첫번째 인덱스 출력하고 다음 인덱스 출력해야할때 해당 함수에 들어온다
		indexShowUnderTxt++;

		char timeStr[100];
		//해당 텍스트 순서 기억해두고 출력해야 한다. indexShowUnderTxt로 인덱스 관리한다
		sprintf_s(timeStr, sizeof(timeStr), mUnderTxt.find(nowShowUnderTxt)->second[indexShowUnderTxt].c_str());
		txtLabel->SetText(timeStr);
	}
}


//void GameManager::RenewalSceneData(SCENE saveScene, const std::map<std::string, std::vector<Object*>>& nowSceneObject)
void GameManager::RenewalSceneData(SCENE saveScene, const std::vector<Object*>& nowSceneObject)
{
	switch (saveScene)
	{
	case SCENE_DOOR:
		DeepCopyMap(mDoorObject, nowSceneObject); // 깊은 복사 수행
		break;
	case SCENE_KITCHEN:
		DeepCopyMap(mKitchenObject, nowSceneObject); // 깊은 복사 수행
		break;
	case SCENE_BEDROOM:
		DeepCopyMap(mBedRoomObject, nowSceneObject); // 깊은 복사 수행
		break;
	}
}

void GameManager::DeepCopyMap(std::vector<Object*>& saveData, const std::vector<Object*>& nowSceneObject)
{
	saveData.clear();

	for (Object* srcObject : nowSceneObject)
	{
		Object* newObj = nullptr;

		// 추상 클래스인 Object 대신 동일한 타입으로 객체를 생성하여 캐스팅
		if (dynamic_cast<Door*>(srcObject))
		{
			newObj = new Door(*dynamic_cast<Door*>(srcObject));
		}
		else if (dynamic_cast<Window*>(srcObject))
		{
			newObj = new Window(*dynamic_cast<Window*>(srcObject));
		}
		else if (dynamic_cast<Drawer*>(srcObject))
		{
			newObj = new Drawer(*dynamic_cast<Drawer*>(srcObject));
		}
		else if (dynamic_cast<Flowerbundle_Blue*>(srcObject))
		{
			newObj = new Flowerbundle_Blue(*dynamic_cast<Flowerbundle_Blue*>(srcObject));
		}
		else if (dynamic_cast<Bed*>(srcObject))
		{
			newObj = new Bed(*dynamic_cast<Bed*>(srcObject));
		}
		else if (dynamic_cast<Shelf_Book*>(srcObject))
		{
			newObj = new Shelf_Book(*dynamic_cast<Shelf_Book*>(srcObject));
		}
		else if (dynamic_cast<Table_Vertical*>(srcObject))
		{
			newObj = new Table_Vertical(*dynamic_cast<Table_Vertical*>(srcObject));
		}
		else if (dynamic_cast<Curtain_Red*>(srcObject))
		{
			newObj = new Curtain_Red(*dynamic_cast<Curtain_Red*>(srcObject));
		}
		else if (dynamic_cast<Closet*>(srcObject))
		{
			newObj = new Closet(*dynamic_cast<Closet*>(srcObject));
		}
		else if (dynamic_cast<Table_Red*>(srcObject))
		{
			newObj = new Table_Red(*dynamic_cast<Table_Red*>(srcObject));
		}
		else if (dynamic_cast<Bookcase*>(srcObject))
		{
			newObj = new Bookcase(*dynamic_cast<Bookcase*>(srcObject));
		}
		else if (dynamic_cast<Stove*>(srcObject))
		{
			newObj = new Stove(*dynamic_cast<Stove*>(srcObject));
		}
		else if (dynamic_cast<KitchenCounter*>(srcObject))
		{
			newObj = new KitchenCounter(*dynamic_cast<KitchenCounter*>(srcObject));
		}
		else if (dynamic_cast<FirePot*>(srcObject))
		{
			newObj = new FirePot(*dynamic_cast<FirePot*>(srcObject));
		}
		else if (dynamic_cast<Sideboard*>(srcObject))
		{
			newObj = new Sideboard(*dynamic_cast<Sideboard*>(srcObject));
		}
		else if (dynamic_cast<WallHanging*>(srcObject))
		{
			newObj = new WallHanging(*dynamic_cast<WallHanging*>(srcObject));
		}
		else if (dynamic_cast<WaterCup*>(srcObject))
		{
			newObj = new WaterCup(*dynamic_cast<WaterCup*>(srcObject));
		}
		else if (dynamic_cast<OneCandle*>(srcObject))
		{
			newObj = new OneCandle(*dynamic_cast<OneCandle*>(srcObject));
		}
		else if (dynamic_cast<Flowerbundle_Red*>(srcObject))
		{
			newObj = new Flowerbundle_Red(*dynamic_cast<Flowerbundle_Red*>(srcObject));
		}
		else if (dynamic_cast<Flowerbundle_Orange*>(srcObject))
		{
			newObj = new Flowerbundle_Orange(*dynamic_cast<Flowerbundle_Orange*>(srcObject));
		}
		else if (dynamic_cast<Flowerbundle_Yellow*>(srcObject))
		{
			newObj = new Flowerbundle_Yellow(*dynamic_cast<Flowerbundle_Yellow*>(srcObject));
		}

		if (newObj)
		{
			saveData.push_back(newObj);
		}
	}
}


//std::map<std::string, std::vector<Object*>> GameManager::ApplySceneData(SCENE applyScene)
std::vector<Object*> GameManager::ApplySceneData(SCENE applyScene)
{
	switch (applyScene)
	{
	case SCENE_DOOR:
		return mDoorObject;
	case SCENE_KITCHEN:
		return mKitchenObject;
	case SCENE_BEDROOM:
		return mBedRoomObject;
	}

	return std::vector<Object*>();
}






//------파일 입출력 관련--------


void GameManager::LoadData()
{
	FileRead("Door");
	FileRead("Window");
	FileRead("Drawer");
	FileRead("Flowerbundle_Blue");
	FileRead("Bed");
	FileRead("Shelf_Book");
	FileRead("Table_Vertical");
	FileRead("Curtain_Red");
	FileRead("Closet");
	FileRead("Table_Red");
	FileRead("Bookcase");
	FileRead("Stove");
	FileRead("KitchenCounter");
	FileRead("FirePot");
	FileRead("Sideboard");
	FileRead("WallHanging");
	FileRead("WaterCup");
	FileRead("OneCandle");
	FileRead("Flowerbundle_Red");
	FileRead("Flowerbundle_Orange");
	FileRead("Flowerbundle_Yellow");


}


void GameManager::FileRead(const std::string& file) {

	std::ifstream load("Data/" + file + ".txt");

	//오브젝트 객체 하나당 데이터 설정값
	ObjectData tmpObjectData; //하나의 가구 종류

	if (load.is_open()) {
		std::string line;

		// 읽어올 데이터가 있는지 확인
		if (std::getline(load, line)) {
			//오브젝트 명칭(파일명과 동일)
			tmpObjectData.objectName = file;

			// 사용 타입
			std::istringstream typeStream(line);

			std::string typeCheckValue;
			for (int i = 0; i < TYPE_COUNT; i++) {
				typeStream >> typeCheckValue;
				if (typeCheckValue == "true") //문자열을 전부 false로 판단
					tmpObjectData.typeCheck[static_cast<OBJECT_TYPE>(i)] = true;
				else
					tmpObjectData.typeCheck[static_cast<OBJECT_TYPE>(i)] = false;
			}

			// 스플릿 분리 xy
			std::getline(load, line);
			std::istringstream splitStream(line);
			splitStream >> tmpObjectData.spritesX;
			splitStream >> tmpObjectData.spritesY;

			// 이미지 파일
			std::getline(load, line);
			tmpObjectData.fileName = line;

			//상세 선택지
			std::string sTmp;
			std::getline(load, line);
			std::istringstream selectStream(line);
			selectStream >> tmpObjectData.detailSelectCount;
			for (int i = 0; i < tmpObjectData.detailSelectCount; i++)
			{
				selectStream >> sTmp;
				tmpObjectData.sDetailSelect.push_back(sTmp);
			}


			// 총 수량
			std::getline(load, line);
			std::istringstream countStream(line);
			countStream >> tmpObjectData.objectCount;

			// 오브젝트 객체 하나당 데이터 설정값
			for (int i = 0; i < tmpObjectData.objectCount; ++i)
			{
				std::getline(load, line);
				std::istringstream objStream(line);
				EachObject tmpEachObject; //가구 한 종류 안에서 객체들 관리

				//이름
				objStream >> tmpEachObject.objectIndex.name;

				// 사용 맵의 인덱스
				objStream >> tmpEachObject.objectIndex.mapIndex;
				//맵마다 해당 오브젝트가 몇번째 번호인지
				objStream >> tmpEachObject.objectIndex.eachObjectIndex;

				// 현재 상태
				bool bTmp;

				std::string typeCheckValue;
				for (int i = 0; i < 4; i++) {

					objStream >> typeCheckValue;

					if (typeCheckValue == "true") //문자열을 전부 false로 판단
						bTmp = true;
					else
						bTmp = false;

					switch (i)
					{
					case 0:
						tmpEachObject.Available = bTmp;
						break;
					case 1:
						tmpEachObject.isMove = bTmp;
						break;
					case 2:
						tmpEachObject.isAnim = bTmp;
						break;
					case 3:
						tmpEachObject.isActive = bTmp;
						break;
					}
				}

				// 좌표
				objStream >> tmpEachObject.x;
				objStream >> tmpEachObject.y;
				// 위치 이동 정도
				objStream >> tmpEachObject.move_X;
				objStream >> tmpEachObject.move_Y;
				objStream >> tmpEachObject.move_Speed;


				tmpObjectData.eachObject.push_back(new EachObject(tmpEachObject));
			}
		}
		objectData.insert({ file, tmpObjectData }); //pair로 만들기
		load.close();
	}

	//saveObjectData = objectData;
}




//void GameManager::InitSceneData(int _mapIndex, std::map <std::string, std::vector<Object*>>& _Object)
void GameManager::InitSceneData(int _mapIndex, std::vector<Object*>& tmpObject)
{ //로드해온 Object 데이터 각 Scene마다 Object 관리하는 변수에 세팅

	//Door
	//std::vector<Object*> tmpObject;

	ObjectData data = objectData.find("Door")->second;
	for (int i = 0; i < data.objectCount; i++)
	{
		//해당 맵에 배치된 Object 인지 판별
		if (_mapIndex == data.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new Door(data, i));
	}
	//_Object.push_back(tmpObject);
	//_Object.insert({ "Door", tmpObject }); //pair로 만들기

	//tmpObject.clear();

	//Window
	for (int i = 0; i < objectData.find("Window")->second.objectCount; i++)
	{
		//해당 맵에 배치된 Object 인지 판별
		if (_mapIndex == objectData.find("Window")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new Window(objectData.find("Window")->second, i));
	}
	//_Object.insert({ "Window", tmpObject }); //pair로 만들기

	//tmpObject.clear();

	//Drawer
	for (int i = 0; i < objectData.find("Drawer")->second.objectCount; i++)
	{
		//해당 맵에 배치된 Object 인지 판별
		if (_mapIndex == objectData.find("Drawer")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new Drawer(objectData.find("Drawer")->second, i));
	}
	//_Object.insert({ "Drawer", tmpObject }); //pair로 만들기

	//tmpObject.clear();


	//Flowerbundle_Blue
	for (int i = 0; i < objectData.find("Flowerbundle_Blue")->second.objectCount; i++)
	{
		//해당 맵에 배치된 Object 인지 판별
		if (_mapIndex == objectData.find("Flowerbundle_Blue")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new Flowerbundle_Blue(objectData.find("Flowerbundle_Blue")->second, i));
	}
	//_Object.insert({ "Flowerpot", tmpObject }); //pair로 만들기

	//tmpObject.clear();

	//Bed
	for (int i = 0; i < objectData.find("Bed")->second.objectCount; i++)
	{
		//해당 맵에 배치된 Object 인지 판별
		if (_mapIndex == objectData.find("Bed")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new Bed(objectData.find("Bed")->second, i));
	}
	//_Object.insert({ "Bed", tmpObject }); //pair로 만들기

	//tmpObject.clear();

	//Shelf_Book
	for (int i = 0; i < objectData.find("Shelf_Book")->second.objectCount; i++)
	{
		//해당 맵에 배치된 Object 인지 판별
		if (_mapIndex == objectData.find("Shelf_Book")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new Shelf_Book(objectData.find("Shelf_Book")->second, i));
	}
	//_Object.insert({ "Shelf_Book", tmpObject }); //pair로 만들기

	//tmpObject.clear();

	//Table_Vertical
	for (int i = 0; i < objectData.find("Table_Vertical")->second.objectCount; i++)
	{
		//해당 맵에 배치된 Object 인지 판별
		if (_mapIndex == objectData.find("Table_Vertical")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new Table_Vertical(objectData.find("Table_Vertical")->second, i));
	}
	//_Object.insert({ "Table_Vertical", tmpObject }); //pair로 만들기

	//tmpObject.clear();

	//Curtain_Red
	for (int i = 0; i < objectData.find("Curtain_Red")->second.objectCount; i++)
	{
		//해당 맵에 배치된 Object 인지 판별
		if (_mapIndex == objectData.find("Curtain_Red")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new Curtain_Red(objectData.find("Curtain_Red")->second, i));
	}
	//_Object.insert({ "Curtain_Red", tmpObject }); //pair로 만들기

	//tmpObject.clear();

	//Closet
	for (int i = 0; i < objectData.find("Closet")->second.objectCount; i++)
	{
		//해당 맵에 배치된 Object 인지 판별
		if (_mapIndex == objectData.find("Closet")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new Closet(objectData.find("Closet")->second, i));
	}
	//_Object.insert({ "Closet", tmpObject }); //pair로 만들기

	//tmpObject.clear();

	//Table_Red
	for (int i = 0; i < objectData.find("Table_Red")->second.objectCount; i++)
	{
		//해당 맵에 배치된 Object 인지 판별
		if (_mapIndex == objectData.find("Table_Red")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new Table_Red(objectData.find("Table_Red")->second, i));
	}
	//_Object.insert({ "Table_Red", tmpObject }); //pair로 만들기

	//tmpObject.clear();	

	//Bookcase
	for (int i = 0; i < objectData.find("Bookcase")->second.objectCount; i++)
	{
		//해당 맵에 배치된 Object 인지 판별
		if (_mapIndex == objectData.find("Bookcase")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new Bookcase(objectData.find("Bookcase")->second, i));
	}
	//_Object.insert({ "Bookcase", tmpObject }); //pair로 만들기

	//tmpObject.clear();	

	//Stove
	for (int i = 0; i < objectData.find("Stove")->second.objectCount; i++)
	{
		//해당 맵에 배치된 Object 인지 판별
		if (_mapIndex == objectData.find("Stove")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new Stove(objectData.find("Stove")->second, i));
	}
	//_Object.insert({ "Stove", tmpObject }); //pair로 만들기

	//tmpObject.clear();

	//KitchenCounter
	for (int i = 0; i < objectData.find("KitchenCounter")->second.objectCount; i++)
	{
		//해당 맵에 배치된 Object 인지 판별
		if (_mapIndex == objectData.find("KitchenCounter")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new KitchenCounter(objectData.find("KitchenCounter")->second, i));
	}
	//_Object.insert({ "KitchenCounter", tmpObject }); //pair로 만들기

	//tmpObject.clear();

	//FirePot
	for (int i = 0; i < objectData.find("FirePot")->second.objectCount; i++)
	{
		//해당 맵에 배치된 Object 인지 판별
		if (_mapIndex == objectData.find("FirePot")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new FirePot(objectData.find("FirePot")->second, i));
	}
	//_Object.insert({ "FirePot", tmpObject }); //pair로 만들기

	//tmpObject.clear();

	//Sideboard
	for (int i = 0; i < objectData.find("Sideboard")->second.objectCount; i++)
	{
		//해당 맵에 배치된 Object 인지 판별
		if (_mapIndex == objectData.find("Sideboard")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new Sideboard(objectData.find("Sideboard")->second, i));
	}
	//_Object.insert({ "Sideboard", tmpObject }); //pair로 만들기

	//tmpObject.clear();

	//Sideboard
	for (int i = 0; i < objectData.find("WallHanging")->second.objectCount; i++)
	{
		//해당 맵에 배치된 Object 인지 판별
		if (_mapIndex == objectData.find("WallHanging")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new WallHanging(objectData.find("WallHanging")->second, i));
	}
	//	_Object.insert({ "WallHanging", tmpObject }); //pair로 만들기

		//tmpObject.clear();	

		//WaterCup
	for (int i = 0; i < objectData.find("WaterCup")->second.objectCount; i++)
	{
		//해당 맵에 배치된 Object 인지 판별
		if (_mapIndex == objectData.find("WaterCup")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new WaterCup(objectData.find("WaterCup")->second, i));
	}
	//	_Object.insert({ "WaterCup", tmpObject }); //pair로 만들기

		//tmpObject.clear();

		//OneCandle
	for (int i = 0; i < objectData.find("OneCandle")->second.objectCount; i++)
	{
		//해당 맵에 배치된 Object 인지 판별
		if (_mapIndex == objectData.find("OneCandle")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new OneCandle(objectData.find("OneCandle")->second, i));
	}
	//	_Object.insert({ "OneCandle", tmpObject }); //pair로 만들기

		//tmpObject.clear();

		//Flowerbundle_Red
	for (int i = 0; i < objectData.find("Flowerbundle_Red")->second.objectCount; i++)
	{
		//해당 맵에 배치된 Object 인지 판별
		if (_mapIndex == objectData.find("Flowerbundle_Red")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new Flowerbundle_Red(objectData.find("Flowerbundle_Red")->second, i));
	}

	//Flowerbundle_Orange
	for (int i = 0; i < objectData.find("Flowerbundle_Orange")->second.objectCount; i++)
	{
		//해당 맵에 배치된 Object 인지 판별
		if (_mapIndex == objectData.find("Flowerbundle_Orange")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new Flowerbundle_Orange(objectData.find("Flowerbundle_Orange")->second, i));
	}

	//Flowerbundle_Yellow
	for (int i = 0; i < objectData.find("Flowerbundle_Yellow")->second.objectCount; i++)
	{
		//해당 맵에 배치된 Object 인지 판별
		if (_mapIndex == objectData.find("Flowerbundle_Yellow")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new Flowerbundle_Yellow(objectData.find("Flowerbundle_Yellow")->second, i));
	}
}

void GameManager::SetPlusHour(int plusHour)
{
	m_Clock.hour += plusHour;

	//24시간 경과 갱신
	if (m_Clock.hour >= TimeLine_ONEDAY)
		m_Clock.hour -= TimeLine_ONEDAY;

	//시간의 흐름에 따라 밤낮 전환(밤이 되는시간부터(20:00~24:00), 아침이 되는시간 전(0:00~5:99)까지)
	isDark = ((m_Clock.hour >= TimeLine_NIGHT) || (m_Clock.hour < TimeLine_MORING)) ? true : false;
}






//--------------플레이어 관련-------------------

void GameManager::PlayerSleep()
{
	//하단 텍스트가 떠야하는 선택지 작동 함수
	isShowUnderTxt = true;

	//잠자기는 허기와 갈증이 30 미만에 가능하다
	if ((m_hunger >= 30) || (m_thirst >= 30))
	{
		//하단창 텍스트 출력
		nowShowUnderTxt = BED_SLEEP_X;
		return;
	}

	SetPlusHour(TimeSleep);

	//허기 갈증 10 이하로 잠들었다면 건강 +10
	if ((m_hunger <= 10) && (m_thirst <= 10))
	{
		m_health += 10;

		if (m_health > 100)
		{
			m_health = 100;
			nowShowUnderTxt = BED_SLEEP_O_HEALTH_GAMECLEAR; //건강 +10 문 열고 나갈 수 있다.
		}
		else //건강 +10
			nowShowUnderTxt = BED_SLEEP_O_HEALTH;
	}
	else //일반적으로 잠든경우
		nowShowUnderTxt = BED_SLEEP_O;


	//수치 조정
	m_fatigue -= 50;
	m_hunger += 30;
	m_thirst += 30;

	if (m_fatigue < 0)
		m_fatigue = 0;
	if (m_hunger > 100)
		m_hunger = 100;
	if (m_thirst > 100)
		m_thirst = 100;
}






//-------------------인벤토리---------------------

void GameManager::Inventory_Panel()
{
	//std::vector<std::pair<ITEM, int>> player_ItemList;
	//ENGINE::UIMgr->Remove("Inventory");
	//Inventory_UI = ENGINE::UIMgr->AddUI<ENGINE::UIImage>("Inventory");
	//Inventory_UI->Initialize("Inventory_panel.bmp", ENGINE::DrawType::AlphaBlend); //투명도 조절 가능하게끔
	//Inventory_UI->Set_Transparency(INVENTORY_TRANSPARENCY); //투명화 원하는 값(0 ~ 255)
	Inventory_UI->SetEnable(true);

	// 자식 UI 제거(0,1,2는 필수로 필요한 Child 기본 패널에 붙인 이전,취소,다음 버튼이다. 해당 인덱스는 삭제 되지 않고독 유의)
	for (int i = Inventory_Page_MinChlidCount; i < Inventory_UI->GetChildCount();)
	{
		ENGINE::UIPanel* childUI = Inventory_UI->GetChild(i);
		childUI->SetEnable(false);
		Inventory_UI->RemoveChildUI(childUI);
		// 원소가 삭제되면 i는 그대로 두고, 삭제하지 않았다면 다음 인덱스로 이동
	}
//	Inventory_UI->RemoveChildUI(Inventory_UI); //해당 함수 사용법 확인후 겹칩 안 뜨도록 설정

	if (Inventory_UI)
	{
		//int i, selectBtn_X, selectBtn_Y, cancel_X, cancel_Y, showItem_Count;
		int i, selectBtn_X, selectBtn_Y, showItem_Count;
		GameMgr->Set_IsPause(true);

		Inventory_UI->SetPosition(UI_INVENTORY_X, UI_INVENTORY_Y, false);

		selectBtn_X = Inventory_UI->GetSize().cx * 0.2f;
		selectBtn_Y = 17;
		//cancel_X = Inventory_UI->GetSize().cx * 0.5f;
		//cancel_Y = Inventory_UI->GetSize().cy - 15;


		std::vector<Item*> inventory = ItemMgr->GetItemList();

		//아이템이 9개 이상일 경우 > 보여줄 아이템 항목 9개로 고정
		/*인벤토리 10개에서 아이템 하나 썼을때 다음 페이지 안 뜨도록
		>첫페이지에서는 성공
		>두번째 페이지에서 총 아이템 아이템 9개 되었을 때(두번째 페이지는 비어있다.) 이전 페이지로 가면 두번째 페이지로 가는 버튼이 사라짐*/
		if (player_ItemList.size() > (Inventory_Index + 1) * Inventory_OnePage)
			showItem_Count = (Inventory_Index + 1) * Inventory_OnePage;
		else
			showItem_Count = player_ItemList.size();



		//인벤토리에 현재 있는 아이템 수만큼(최대 9개 - 나머지는 다음 페이지 버튼 누르면 보여주기) 아이템 칸 생성
		for (i = Inventory_Index * Inventory_OnePage; i < showItem_Count; i++)
		{
			//Item* useItem = ItemMgr->GetItemList().find(player_ItemList[i].itemID)->second;
			ITEM_ID playerHave_itemID = player_ItemList[i].itemID;
			Item* useItem = nullptr;
			std::string itemName;

			//플레이어 인벤토리에 들어있으면 ItemMgr의 아이템 데이터에 반드시 있음
			for (int i = 0; i < inventory.size(); i++)
			{
				if (inventory[i]->GetItemID() == playerHave_itemID) 
				{
					useItem = inventory[i];
					itemName = useItem->GetName();
					break;
				}
			}


			//버튼-선택지
			ENGINE::UIButton* btn_select = ENGINE::UIMgr->AddUI<ENGINE::UIButton>("Optional " + std::to_string(i + 1) + itemName, Inventory_UI); //파일 이름으로 구분 ex.Home_Flowerpot.bmp
			//ENGINE::UIButton* btn_select = ENGINE::UIMgr->AddUI<ENGINE::UIButton>("Optional " + std::to_string(i + 1) + "_" + (*interObject)[i]->GetObjectName() + " Btn", Inventory_UI); //파일 이름으로 구분 ex.Home_Flowerpot.bmp
			btn_select->Initialize("Inventory_Btn_Normal.bmp", "Inventory_Btn_Pressed.bmp", "", "", ENGINE::DrawType::Transparent);
			btn_select->SetLocalPosition(selectBtn_X, selectBtn_Y, true);
			//btn_select->SetListener(std::bind(&GameManager::ItemUseBtnClickHandler, this, useItem));
			btn_select->SetListener(std::bind(&GameManager::ItemUse_Detail_Panel, this, useItem));
			btn_select->SetEnable(true);

			//선택지 문구
			ENGINE::UILabel* btn_txt = ENGINE::UIMgr->AddUI<ENGINE::UILabel>(itemName + "ShowList Txt", btn_select);
			btn_txt->SetLocalPosition(FONT_SELECT_X, FONT_SELECT_Y, true);
			btn_txt->Initialize(itemName + " * " + std::to_string(GetCountPlayerItem(useItem->GetItemID())), RGB(255, 255, 255), ENGINE::GUIMgr->Get_Font(FONT_SELECT));
			btn_txt->SetEnable(true);

			selectBtn_X += btn_select->GetSize().cx + 10;

			//인벤토리 칸 3개 넘으면 다음 줄로 내려서 배치
			if (selectBtn_X >= Inventory_UI->GetSize().cx)
			{
				selectBtn_X = Inventory_UI->GetSize().cx * 0.2f;
				selectBtn_Y += 25;
			}
		}

		//----취소 버튼----
		Inventory_UI->GetChild(Inventory_Page_CancelBtn)->SetEnable(true);


		//----이전 페이지 버튼----
		if (Inventory_Index != 0)
		{//인벤토리 페이지의 인덱스가 0일때만 이전 버튼 안 뜨게
			//ENGINE::UIButton* btn_Prev = ENGINE::UIMgr->AddUI<ENGINE::UIButton>("Inventory_PevPage_Btn" + std::to_string(i + 1), Inventory_UI);
			//btn_Prev->Initialize("Inventory_Btn_Normal.bmp", "Inventory_Btn_Pressed.bmp", "", "", ENGINE::DrawType::Transparent);
			//btn_Prev->SetLocalPosition(cancel_X - btn_Prev->GetSize().cx - 10, cancel_Y, true);
			//Inventory_Index -= 1;
			//btn_Prev->SetListener(std::bind(&GameManager::Inventory_Panel, this, player));
			////이전 문구
			//ENGINE::UILabel* btnPrev_txt = ENGINE::UIMgr->AddUI<ENGINE::UILabel>("Inventory_PevPage_Txt" + std::to_string(i + 1), btn_Prev);
			//btnPrev_txt->SetLocalPosition(FONT_SELECT_X, FONT_SELECT_Y, true);
			//btnPrev_txt->Initialize("이전", RGB(255, 255, 255), ENGINE::GUIMgr->Get_Font(FONT_SELECT));
			//Inventory_UI->GetChild(1)
			Inventory_UI->GetChild(Inventory_Page_PrevBtn)->SetEnable(true);
		}
		else
			Inventory_UI->GetChild(Inventory_Page_PrevBtn)->SetEnable(false);

		//----다음 페이지 버튼----
		//if (showItem_Count >= Inventory_OnePage * (Inventory_Index + 1))
		if (player_ItemList.size() > (Inventory_Index + 1) * Inventory_OnePage)
		{//출력되지 않은 아이템이 10개를 넘어가면 다음 버튼 띄우기
			//ENGINE::UIButton* btn_Next = ENGINE::UIMgr->AddUI<ENGINE::UIButton>("Inventory_NextPage_Btn" + std::to_string(i + 1), Inventory_UI);
			//btn_Next->Initialize("Inventory_Btn_Normal.bmp", "Inventory_Btn_Pressed.bmp", "", "", ENGINE::DrawType::Transparent);
			//btn_Next->SetLocalPosition(cancel_X + btn_Next->GetSize().cx + 10, cancel_Y, true);
			//Inventory_Index += 1;
			Inventory_UI->GetChild(Inventory_Page_NextBtn)->SetEnable(true);
			//btn_Cancel->SetListener(std::bind(&GameManager::Inventory_Panel, this, player));
			//다음 문구
			//ENGINE::UILabel* btnNext_txt = ENGINE::UIMgr->AddUI<ENGINE::UILabel>("Inventory_NextPage_Txt" + std::to_string(i + 1), btn_Next);
			//btnNext_txt->SetLocalPosition(FONT_SELECT_X, FONT_SELECT_Y, true);
			//btnNext_txt->Initialize("다음", RGB(255, 255, 255), ENGINE::GUIMgr->Get_Font(FONT_SELECT));
		}
		else
			Inventory_UI->GetChild(Inventory_Page_NextBtn)->SetEnable(false);
	}
}

void GameManager::Cancel_InventoryBtnClickHandler()
{//인벤토리 창 끄기(인벤토리 창 위에 어떤 추가 창이 있으면 취소버튼 중복으로 눌리지 않게끔)
	bool active = false;

	//아이템 사용/취소 판넬이 떠있지 않을 경우에만 인벤토리 판넬 취소 가능 + (아이템 사용 창은 떠있고 게임 재생 + 인벤토리 창 켜져있는 것 방지)
	//아이템 사용하고 하단 창 뜨면, 하단 창만 클릭 가능하게(인벤토리 취소 창 못 누르게끔)
	if (Inventory_UI_ItemUseSelect == nullptr && underTxt_Section == nullptr) //하단창과 아이템 상태창 한번도 뜬 적 없는 경우
	{
		active = true;
	}
	else if (Inventory_UI_ItemUseSelect != nullptr && underTxt_Section == nullptr) //하단창 뜬 적 있는지 판별
	{
		//하단창 떠있는 상테에서 취소 버튼 못누르게
		if (!Inventory_UI_ItemUseSelect->GetEnable() && underTxt_Section == nullptr)
			active = true;
	}
	else if (Inventory_UI_ItemUseSelect == nullptr && underTxt_Section != nullptr) //아이템 상세창 뜬 적 있는지 판별
	{
		//아이템 상세창 떠있는 상테에서 취소 버튼 못누르게
		if (Inventory_UI_ItemUseSelect == nullptr && !underTxt_Section->GetEnable())
			active = true;
	}
	else if (Inventory_UI_ItemUseSelect != nullptr && underTxt_Section != nullptr) //아이템 상세창 한번 띄웠다가 인벤토리 창 지울 경우
	{
		if (!Inventory_UI_ItemUseSelect->GetEnable() && !underTxt_Section->GetEnable())
			active = true;
	}



	if (active)
	{
		Inventory_UI->SetEnable(FALSE); //아이템 종류 보여주는 판넬
		isPause = false;
		isInventory = false; //인벤토리가 관리된다.(인벤토리 끔)
	}
}

void GameManager::ShowInventoryNextPage(bool isMove_NextPage)
{
	bool active = false;

	//아이템 사용/취소 판넬이 떠있지 않을 경우에만 인벤토리 판넬 취소 가능 + (아이템 사용 창은 떠있고 게임 재생 + 인벤토리 창 켜져있는 것 방지)
	//아이템 사용하고 하단 창 뜨면, 하단 창만 클릭 가능하게(인벤토리 취소 창 못 누르게끔)
	if (Inventory_UI_ItemUseSelect == nullptr && underTxt_Section == nullptr) //하단창과 아이템 상태창 한번도 뜬 적 없는 경우
	{
		active = true;
	}
	else if (Inventory_UI_ItemUseSelect != nullptr && underTxt_Section == nullptr) //하단창 뜬 적 있는지 판별
	{
		//하단창 떠있는 상테에서 취소 버튼 못누르게
		if (!Inventory_UI_ItemUseSelect->GetEnable() && underTxt_Section == nullptr)
			active = true;
	}
	else if (Inventory_UI_ItemUseSelect == nullptr && underTxt_Section != nullptr) //아이템 상세창 뜬 적 있는지 판별
	{
		//아이템 상세창 떠있는 상테에서 취소 버튼 못누르게
		if (Inventory_UI_ItemUseSelect == nullptr && !underTxt_Section->GetEnable())
			active = true;
	}
	else if (Inventory_UI_ItemUseSelect != nullptr && underTxt_Section != nullptr) //아이템 상세창 한번 띄웠다가 인벤토리 창 지울 경우
	{
		if (!Inventory_UI_ItemUseSelect->GetEnable() && !underTxt_Section->GetEnable())
			active = true;
	}

	if (active)
	{
		if (isMove_NextPage)
			Inventory_Index += 1;
		else
			Inventory_Index -= 1;

		Inventory_Panel();
	}
}

void GameManager::PlusPlayerInventory(InventoryItem item)
{
	bool itemFound = false;

	for (auto iter = player_ItemList.begin(); iter != player_ItemList.end(); iter++)
	{
		if (iter->itemID == item.itemID)
		{
			//인벤토리에 해당 아이템이 이미 존재 > 수량 증가
			iter->itemCount++;
			itemFound = true; //아이템을 찾았음을 표시
			break; //이미 아이템을 찾았으므로 더 이상 검색할 필요 없음
		}
	}

	//인벤토리에 해당 아이템이 없는 경우 추가
	if (!itemFound)
		player_ItemList.push_back(item);
}

bool GameManager::MinusPlayerItem(ITEM_ID itemID)
{
	//아이템 하나만 사용되도록 설정되어있다. //현재 아이템은 영구 사용이 불가능하도록 설계되어있다.
	for (auto iter = player_ItemList.begin(); iter != player_ItemList.end(); iter++)
	{
		if (iter->itemID == itemID)
		{
			//아이템 사용 1개
			iter->itemCount--;

			//아이템 수량이 0이 되면 인벤토리에서 삭제한다.
			if (iter->itemCount == 0)
			{
				player_ItemList.erase(iter);
			}
			return true;
		}
	}

	return false;
}

int GameManager::GetCountPlayerItem(ITEM_ID itemID)
{
	for (auto iter = player_ItemList.begin(); iter != player_ItemList.end(); ++iter)
	{
		if (iter->itemID == itemID)
		{
			return iter->itemCount;
		}
	}
}

void GameManager::ItemUse_Detail_Panel(Item* useItem)
{
	//상세창이 처음 뜰 경우 + 상세창이 이미 떠있지 않을 경우 + 하단창이 떠있지 않을 경우   >   상세창을 띄울 수 있다.
	if ((Inventory_UI_ItemDetaiInfo == nullptr || !Inventory_UI_ItemDetaiInfo->GetEnable()) && !underTxt_Section->GetEnable())
	{
		//------------아이템 이미지 + 상세정보 판넬--------------
		ENGINE::UIMgr->Remove("ItemDetail");
		Inventory_UI_ItemDetaiInfo = ENGINE::UIMgr->AddUI<ENGINE::UIImage>("ItemDetail");
		Inventory_UI_ItemDetaiInfo->Initialize("Inventory_panel_Detail.bmp", ENGINE::DrawType::Transparent); //투명도 조절 가능하게끔
		//Inventory_UI_ItemDetaiInfo->Set_Transparency(ITEM_TRANSPARENCY); //투명화 원하는 값(0 ~ 255)


		if (Inventory_UI_ItemDetaiInfo)
		{
			int i, selectBtn_X, selectBtn_Y;//, cancel_X, cancel_Y;
			GameMgr->Set_IsPause(true);

			Inventory_UI_ItemDetaiInfo->SetPosition(UI_INVENTORY_ITEMDETAIL_X, UI_INVENTORY_ITEMDETAIL_Y, false);

			selectBtn_X = Inventory_UI_ItemDetaiInfo->GetSize().cx * 0.5f;
			selectBtn_Y = 17;

			std::string itemName = useItem->GetName();

			//아이템 이미지
			ENGINE::UIImage* itemImage;
			itemImage = ENGINE::UIMgr->AddUI<ENGINE::UIImage>("ItemDetail_Image", Inventory_UI_ItemDetaiInfo);
			itemImage->Initialize(useItem->GetImageBmp(), ENGINE::DrawType::Transparent);
			if (itemImage)
				itemImage->SetPosition(UI_INVENTORY_ITEMIMAGE_X, UI_INVENTORY_ITEMIMAGE_Y, false);


			//아이템 상세 설명 문구
			ENGINE::UILabel* btn_txt = ENGINE::UIMgr->AddUI<ENGINE::UILabel>(itemName + "Detail Txt", Inventory_UI_ItemDetaiInfo);
			btn_txt->SetLocalPosition(FONT_ITEM_DETAL_X, Inventory_UI_ItemDetaiInfo->GetSize().cy - 20, true);
			btn_txt->Initialize(useItem->GetDetailInfo(), RGB(255, 255, 255), ENGINE::GUIMgr->Get_Font(FONT_SELECT));
		}


		//------------아이템 사용/취소 판넬--------------

		ENGINE::UIMgr->Remove("ItemUse");
		Inventory_UI_ItemUseSelect = ENGINE::UIMgr->AddUI<ENGINE::UIImage>("ItemUse");
		Inventory_UI_ItemUseSelect->Initialize("Inventory_panel_Select.bmp", ENGINE::DrawType::Transparent); //투명도 조절 가능하게끔


		if (Inventory_UI_ItemUseSelect)
		{
			int i, selectBtn_X, selectBtn_Y;//, cancel_X, cancel_Y;
			GameMgr->Set_IsPause(true);

			Inventory_UI_ItemUseSelect->SetPosition(UI_INVENTORY_ITEMUSE_X, UI_INVENTORY_ITEMUSE_Y, false);

			selectBtn_X = Inventory_UI_ItemUseSelect->GetSize().cx * 0.5f;
			selectBtn_Y = 17;

			std::string itemName = useItem->GetName();

			//버튼-선택지
			ENGINE::UIButton* btn_select = ENGINE::UIMgr->AddUI<ENGINE::UIButton>("Optional Selete Use" + itemName, Inventory_UI_ItemUseSelect); //파일 이름으로 구분 ex.Home_Flowerpot.bmp
			//ENGINE::UIButton* btn_select = ENGINE::UIMgr->AddUI<ENGINE::UIButton>("Optional " + std::to_string(i + 1) + "_" + (*interObject)[i]->GetObjectName() + " Btn", Inventory_UI); //파일 이름으로 구분 ex.Home_Flowerpot.bmp
			btn_select->Initialize("Inventory_Btn_Normal.bmp", "Inventory_Btn_Pressed.bmp", "", "", ENGINE::DrawType::Transparent);
			btn_select->SetLocalPosition(selectBtn_X, selectBtn_Y, true);
			btn_select->SetListener(std::bind(&GameManager::ItemUseBtnClickHandler, this, useItem));

			//선택지 문구
			ENGINE::UILabel* btn_txt = ENGINE::UIMgr->AddUI<ENGINE::UILabel>(itemName + "Txt", btn_select);
			btn_txt->SetLocalPosition(FONT_SELECT_X, FONT_SELECT_Y, true);
			btn_txt->Initialize("사용", RGB(255, 255, 255), ENGINE::GUIMgr->Get_Font(FONT_SELECT));

			selectBtn_Y += 25;

			ENGINE::UIButton* btn_Cancel = ENGINE::UIMgr->AddUI<ENGINE::UIButton>("CancelBtn_Panel_", Inventory_UI_ItemUseSelect);
			btn_Cancel->Initialize("Inventory_Btn_Normal.bmp", "Inventory_Btn_Pressed.bmp", "", "", ENGINE::DrawType::Transparent);
			btn_Cancel->SetLocalPosition(selectBtn_X, selectBtn_Y, true);
			btn_Cancel->SetListener(std::bind(&GameManager::Cancel_ItemUseSelectBtnClickHandler, this));

			//선택지 문구
			ENGINE::UILabel* btnCancel_txt = ENGINE::UIMgr->AddUI<ENGINE::UILabel>("Cancel_Txt", btn_Cancel);
			btnCancel_txt->SetLocalPosition(FONT_SELECT_X, FONT_SELECT_Y, true);
			btnCancel_txt->Initialize("취소", RGB(255, 255, 255), ENGINE::GUIMgr->Get_Font(FONT_SELECT));
		}

		//Inventory_UI_ItemUseSelect->SetEnable(true);
	}
}

void GameManager::ItemUseBtnClickHandler(Item* useItem)
{
	//보험
	//하단창이 떠있을 경우 아이템 사용 불가능
	if (!underTxt_Section->GetEnable())
	{
		useItem->Use();
		Cancel_ItemUseSelectBtnClickHandler();
	}
}


void GameManager::Cancel_ItemUseSelectBtnClickHandler()
{
	//보험
	//하단창이 떠있을 경우 아이템 상세창 취소 버튼 불가능
	if (!underTxt_Section->GetEnable())
	{
		Inventory_UI_ItemDetaiInfo->SetEnable(FALSE); //아이템 이미지 + 상세정보
		Inventory_UI_ItemUseSelect->SetEnable(FALSE); //아이템 사용/취소 판넬
	}
}





//--요리--
void GameManager::Cook()
{
	switch (cookSelectCount)
	{
	case 1:
		ENGINE::UIMgr->Remove("Detail Optional Form_2");
		CookSelect_UI = nullptr;
		CookSelect_UI = ENGINE::UIMgr->AddUI<ENGINE::UIImage>("Detail Optional Form_2");
		CookSelect_UI->Initialize("Select_Panel_2.bmp", ENGINE::DrawType::Transparent);
		break;
	case 2:
		ENGINE::UIMgr->Remove("Detail Optional Form_3");
		CookSelect_UI = nullptr;
		CookSelect_UI = ENGINE::UIMgr->AddUI<ENGINE::UIImage>("Detail Optional Form_3");
		CookSelect_UI->Initialize("Select_Panel_3.bmp", ENGINE::DrawType::Transparent);
		break;
	case 3:
		ENGINE::UIMgr->Remove("Detail Optional Form_4");
		CookSelect_UI = nullptr;
		CookSelect_UI = ENGINE::UIMgr->AddUI<ENGINE::UIImage>("Detail Optional Form_4");
		CookSelect_UI->Initialize("Select_Panel_4.bmp", ENGINE::DrawType::Transparent);
		break;
	default:
		break;
	}


	//선택지가 존재하면
	if (CookSelect_UI) //Available이면 수가 0 이상이므로 bool값으로 판정하지 않았다.
	{
		int i, selectBtn_X, selectBtn_Y;

		CookSelect_UI->SetPosition(UI_SELECT_X, UI_SELECT_Y, false);
		selectBtn_X = CookSelect_UI->GetSize().cx * 0.5f;
		selectBtn_Y = 17;


		//세부 선택지 만들기
		for (i = 0; i < cookSelectCount; i++)
		{
			//버튼-선택지
			ENGINE::UIButton* btn_select = ENGINE::UIMgr->AddUI<ENGINE::UIButton>(std::to_string(i) + "Cook Optional " + std::to_string(i + 1) + " Btn", CookSelect_UI); //파일 이름으로 구분
			btn_select->Initialize("Select_Btn_Normal.bmp", "Select_Btn_Pressed.bmp", "", "", ENGINE::DrawType::Transparent);
			btn_select->SetLocalPosition(selectBtn_X, selectBtn_Y, true);
			//btn_select->SetListener(std::bind(&Object::DetailSelect, this, i));
			btn_select->SetListener(std::bind(&GameManager::Cooking, this, i));

			//상세 선택지 문구
			ENGINE::UILabel* btn_txt = ENGINE::UIMgr->AddUI<ENGINE::UILabel>(sCookSelect[i] + "Cook Optional Txt", btn_select);
			btn_txt->SetLocalPosition(FONT_SELECT_X, FONT_SELECT_Y, true);
			btn_txt->Initialize(sCookSelect[i], RGB(255, 255, 255), ENGINE::GUIMgr->Get_Font(FONT_SELECT));

			selectBtn_Y += 25;
		}

		ENGINE::UIButton* btn_Cancel = ENGINE::UIMgr->AddUI<ENGINE::UIButton>("Cook_CancelBtn_Panel_" + std::to_string(i + 1), CookSelect_UI);
		btn_Cancel->Initialize("Select_Btn_Normal.bmp", "Select_Btn_Pressed.bmp", "", "", ENGINE::DrawType::Transparent);
		btn_Cancel->SetLocalPosition(selectBtn_X, selectBtn_Y, true);
		btn_Cancel->SetListener(std::bind(&GameManager::CancelCookClickHandler, this));


		//선택지 문구
		ENGINE::UILabel* btnCancel_txt = ENGINE::UIMgr->AddUI<ENGINE::UILabel>("Cook_Cancel_Txt" + std::to_string(i + 1), btn_Cancel);
		btnCancel_txt->SetLocalPosition(FONT_SELECT_X, FONT_SELECT_Y, true);
		btnCancel_txt->Initialize("취소", RGB(255, 255, 255), ENGINE::GUIMgr->Get_Font(FONT_SELECT));
	}
	CookSelect_UI->SetEnable(TRUE);
}

void GameManager::Cooking(int selectMenu)
{
	bool bShortage = false;

	switch (selectMenu)
	{
	case 0:
		bShortage = MinusPlayerItem(FRUIT_RED) && MinusPlayerItem(FRUIT_ORANGE) && MinusPlayerItem(FRUIT_YELLOW) && MinusPlayerItem(FRUIT_BLUE);

		if (bShortage)
		{
			PlusPlayerInventory({ COOKING_ALLFRUIT, 1 });
			GameMgr->SetShowUnder(COOKING_SUCCES_ALLFRIUT); //요리 성공
		}
		break;
	case 1:
		bShortage = MinusPlayerItem(FRUIT_ORANGE) && MinusPlayerItem(FRUIT_YELLOW);

		if (bShortage)
		{
			PlusPlayerInventory({ COOKING_YELLOW, 1 });
			GameMgr->SetShowUnder(COOKING_SUCCES_YELLOW); //요리 성공
		}
		break;
	case 2:
		bShortage = MinusPlayerItem(FRUIT_RED) && MinusPlayerItem(FRUIT_BLUE);

		if (bShortage)
		{
			PlusPlayerInventory({ COOKING_BERRIES , 1 });
			GameMgr->SetShowUnder(COOKING_SUCCES_BERRIES); //요리 성공
		}
		break;
	}

	//아이템이 부족
	if (!bShortage)
		SetShowUnder(SHORTAGE_ITEM);

	CookSelect_UI->SetEnable(FALSE);
	GameMgr->Set_IsPause(false);
}

void GameManager::CancelCookClickHandler()
{
	CookSelect_UI->SetEnable(FALSE);
	GameMgr->Set_IsPause(false);
}

void GameManager::LoadCook()
{
	// 파일 스트림 열기
	std::ifstream load("Data/Cook.txt");

	// 파일이 성공적으로 열렸는지 확인
	if (load.is_open()) {
		int i = 0;
		load >> cookSelectCount;

		while (i++ < cookSelectCount) {
			std::string sName;
			CookMaterial tmpCookMaterial;
			//std::string line;
			//std::getline(load, line); // 개행 문자 처리

			load >> sName;
			sCookSelect.push_back(sName);

			load >> tmpCookMaterial.RedFruit;
			load >> tmpCookMaterial.OrangeFruit;
			load >> tmpCookMaterial.YellowFruit;
			load >> tmpCookMaterial.BlueFruit;
			cookMaterial.push_back(tmpCookMaterial);
		}

		// 파일 스트림 닫기
		load.close();
	}
}

void GameManager::CancelShowWindow()
{
	isShowWindow = false;
	isPause = false;

	timeLabel->SetEnable(true);

	if (isDark)
		window_Night->SetEnable(false);
	else
		window_Morning->SetEnable(false);
}


void GameManager::GameClear()
{
	isGameEnd = true;
	timeLabel->SetEnable(false);
}

void GameManager::GameEnd()
{
	PostQuitMessage(WM_QUIT);
}
