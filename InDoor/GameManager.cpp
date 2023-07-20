#include "GameManager.h"

GameManager::GameManager()
{
	//TXT 파일 읽어오기
	LoadData();
	LoadUnderTxt();

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
	txtLabel->SetText("테스트용");


	//GameOver
	ENGINE::ResourceMgr->Load("GameOver.bmp");
	gameOver = ENGINE::ResourceMgr->GetBitmap("GameOver.bmp");
	//좌표
	gameOver_X = ENGINE::SceneMgr->GetWidth() - gameOver->GetSize().cx * 1.55;
	gameOver_Y = ENGINE::SceneMgr->GetHeight() / 2 - gameOver->GetSize().cy;
	

	//게임 오버 선택지
	ENGINE::ResourceMgr->Load("Select_Panel.bmp");
	ENGINE::UIMgr->Remove("Optional Form_1");
	select_Restart = ENGINE::UIMgr->AddUI<ENGINE::UIImage>("Optional Form_1");
	select_Restart->Initialize("Select_Panel.bmp", ENGINE::DrawType::Transparent);
	select_Restart->SetLocalPosition(ENGINE::SceneMgr->GetWidth() - select_Restart->GetSize().cx * 1.95, gameOver_Y + 55, true);

	int selectBtn_X, selectBtn_Y;
	selectBtn_X = select_Restart->GetSize().cx * 0.5f;
	selectBtn_Y = 13;
	
	//재시작 - 버튼
	ENGINE::ResourceMgr->Load("Select_Btn_Normal.bmp");
	ENGINE::ResourceMgr->Load("Select_Btn_Pressed.bmp");
	ENGINE::UIButton* btn_Restart = ENGINE::UIMgr->AddUI<ENGINE::UIButton>("Optional Restart Btn", select_Restart);
	btn_Restart->Initialize("Select_Btn_Normal.bmp", "Select_Btn_Pressed.bmp", "", "", ENGINE::DrawType::Transparent);
	btn_Restart->SetLocalPosition(selectBtn_X, selectBtn_Y, true);
	btn_Restart->SetListener(std::bind(&GameManager::Restart, this));

	//재시작 - 선택지 문구
	ENGINE::UILabel* btn_txt = ENGINE::UIMgr->AddUI<ENGINE::UILabel>("Restart Txt", btn_Restart);
	btn_txt->SetLocalPosition(FONT_SELECT_X, FONT_SELECT_Y, true);
	btn_txt->Initialize("재시작", RGB(255, 255, 205), ENGINE::GUIMgr->Get_Font(FONT_SELECT));


	//---------------------
	//로드해온 Object 데이터 각 Scene마다 Object 관리하는 변수에 세팅
	Restart();
}
GameManager::~GameManager()
{
}

void GameManager::Delete_SceneObject()
{
	if (mDoorObject.size() > 0)
	{
		for (std::map<std::string, std::vector<Object*>>::iterator iter = mDoorObject.begin(); iter != mDoorObject.end(); iter++)
		{
			//for (Object* obj : iter->second)
			//{
			//	delete obj;
			//}
			iter->second.clear();
		}
	}
	mDoorObject.clear();

	if (mKitchenObject.size() > 0)
	{
		for (std::map<std::string, std::vector<Object*>>::iterator iter = mKitchenObject.begin(); iter != mKitchenObject.end(); iter++)
		{
			//for (Object* obj : iter->second)
			//{
			//	delete obj;
			//}
			iter->second.clear();
		}
	}
	mKitchenObject.clear();

	if (mBedRoomObject.size() > 0)
	{
		for (std::map<std::string, std::vector<Object*>>::iterator iter = mBedRoomObject.begin(); iter != mBedRoomObject.end(); iter++)
		{
			//for (Object* obj : iter->second)
			//{
			//	delete obj;
			//}
			iter->second.clear();
		}
	}
	mBedRoomObject.clear();
}

void GameManager::Restart()
{
	isGameOver = false;
	isGameClear = false;

	isDark = false;
	isShowUnderTxt = false;
	
	timeLabel->SetEnable(true);
	select_Restart->SetEnable(false);
	underTxt_Section->SetEnable(false);

	//하단 텍스트 감지 위해 초기 세팅값
	nowShowUnderTxt = UNDERTXT_NONE;
	prevShowUnderTxt = UNDERTXT_NONE;

	//수치 상태
	m_health = 10;
	m_hunger = 100;
	//m_hunger = 50;
	m_thirst = 5;
	//m_thirst = 50;
	m_fatigue = 20;

	//경과 시간
	m_elapsedSec = 0;
	m_elapsedMin = 0;

	//시간 체크
	m_elapsedSec = 0.0f;
	nowTimeLine = TimeLine_MORING; oldTimeLine = TimeLine_MORING;
	m_Clock.hour = TimeLine_NIGHT - 1;
	m_Clock.min = 50;

	//로드해온 Object 데이터 각 Scene마다 Object 관리하는 변수에 세팅
	Delete_SceneObject();
	Initialize();
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
		gameOver->StretchBlt(gameOver_X, gameOver_Y);
		select_Restart->Draw();
		return;
	}

	if (isShowUnderTxt)
		ShowUnderSectionTxt(nowShowUnderTxt); //선택지를 선택하면 해당 함수에서 세팅을 하고 이쪽으로 들어온다.

	if (isDark)
	{
		night->AlphaBlendBlt(0, 0, ENGINE::SceneMgr->GetHeight() - 30);
	}
}




void GameManager::Update(const FLOAT&  deltaTime)
{
	//underTxt_UI->SetEnable(false);

	//txtLabel->SetEnable(true);


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


    //시간에 따라 달라지는 요소들 처리(Object, NPC등)

    //낮밤 전환에 따라 단순 BitpMap 바뀌는 요소들
    if ((nowTimeLine == TimeLine_NIGHT) && (oldTimeLine == TimeLine_MORING))
    {//낮 > 밤
		isDark = true;
        ENGINE::ObjectMgr->TimeChangeBitmap(isDark);
    }
    else if ((nowTimeLine == TimeLine_MORING) && (oldTimeLine == TimeLine_NIGHT))
    {//밤 > 낮
		isDark = false;
		ENGINE::ObjectMgr->TimeChangeBitmap(isDark);
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
		if ((m_fatigue <= 90) || (m_thirst <= 90) || (m_hunger <= 90))
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
		//상단 상태창 삭제
		select_Restart->SetEnable(true);
		timeLabel->SetEnable(false);
		//TODO::하단 창 띄우기
		//TODO::하단 창 텍스트
		
		//게임 오버 화면
		//게임 오버 화면 - 텍스트
	}
	else if (m_health == 100)
	{
		isGameClear = true;
	}

    oldTimeLine = nowTimeLine;
}

void GameManager::LoadUnderTxt()
{
	// 파일 스트림 열기
	std::ifstream load("Data/UnderTxt.txt");

	//오브젝트 객체 하나당 데이터 설정값
	ObjectData tmpObjectData; //하나의 가구 종류

	// 파일이 성공적으로 열렸는지 확인
	if (load.is_open()) {

		// 줄 단위로 텍스트 읽어서 mUnderTxt에 저장
		std::string line;
		int i = UNDERTXT_START;

		while (std::getline(load, line) && i < UNDERTXT_COUNT) {
			mUnderTxt[static_cast<UNDERTXT>(i)] = line;
			i++;
		}

		// 파일 스트림 닫기
		load.close();
	}
}

void GameManager::ShowUnderSectionTxt(UNDERTXT showTxt)
{ //첫번째 텍스트 뜰때 무조건 거쳐가게 된다.

	//이전 prevShowUnderTxt값과 nowShowUnderTxt 값이 다르면 출력 텍스트가 변화한것이다. 인덱스 카운트 위해 초기 세팅 필요
	if (prevShowUnderTxt != nowShowUnderTxt)
	{
		//이전 값과 현재 값이 달라지는 처음의 순간만 필요
		prevShowUnderTxt = nowShowUnderTxt;

		//출력 시작하는 텍스트 유형과 인덱스
		nowShowUnderTxt = showTxt;
		indexShowUnderTxt = 0;
	}
	//텍스트 사이즈와 현재 출력 인덱스를 비교해서 세팅 해준다. TODO::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

	//한줄로 끝내는 텍스트 아니면 이어서 출력하도록 재세팅이 필요하다.
	underTxt_Section->SetListener(std::bind(&GameManager::NextShowUnderSection, this, true));
	//마지막 줄일 경우
	underTxt_Section->SetListener(std::bind(&GameManager::NextShowUnderSection, this, false));



	//텍스트창을 누르기 전까지 창과 텍스트 유지

	//하단 텍스트창
	underTxt_Section->SetEnable(true);

	underTxt_Section->Set_Transparency(UNDER_SECTION_TRANSPARENCY); //투명화 원하는 값(0 ~ 255)
	underTxt_Section->Draw();

	//하단 텍스트 표시
	txtLabel->SetEnable(true);

	char timeStr[100];
	//sprintf_s(timeStr, sizeof(timeStr), "하단 텍스트를 띄운다.");
	sprintf_s(timeStr, sizeof(timeStr), mUnderTxt.find(showTxt)->second.c_str());
	txtLabel->SetText(timeStr);
}

//void GameManager::DisableUnderSection()
void GameManager::NextShowUnderSection(bool isNextTxt)
{ //하단창(버튼)을 누르게 되면 들어오게 되는함수. 한줄 > isNextTxt false / 여러줄 > isNextText true로
	//다음 텍스트 없음 - Object 하단 창
	if (!isNextTxt)
	{
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
		//해당 텍스트 순서 기억해두고 출력해야 한다. indexShowUnderTxt로 인덱스 관리한다 TODO::::::::::::::::::::::::::::::::::::::
		sprintf_s(timeStr, sizeof(timeStr), mUnderTxt.find(nowShowUnderTxt)->second.c_str());
		txtLabel->SetText(timeStr);
	}
}


void GameManager::RenewalSceneData(SCENE saveScene, const std::map<std::string, std::vector<Object*>>& nowSceneObject)
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

void GameManager::DeepCopyMap(std::map<std::string, std::vector<Object*>>& dest, const std::map<std::string, std::vector<Object*>>& src)
{
	dest.clear();

	for (const auto& pair : src)
	{
		const std::string& key = pair.first;
		const std::vector<Object*>& srcObjects = pair.second;

		std::vector<Object*> destObjects;
		destObjects.reserve(srcObjects.size());

		for (Object* srcObject : srcObjects)
		{
			// 추상 클래스인 Object 대신 동일한 타입으로 객체를 생성하여 캐스팅
			if (dynamic_cast<Door*>(srcObject))
			{
				Door* door = new Door(*dynamic_cast<Door*>(srcObject));
				destObjects.push_back(door);
			}
			else if (dynamic_cast<Window*>(srcObject))
			{
				Window* window = new Window(*dynamic_cast<Window*>(srcObject));
				destObjects.push_back(window);
			}
			else if (dynamic_cast<Drawer*>(srcObject))
			{
				Drawer* drawer = new Drawer(*dynamic_cast<Drawer*>(srcObject));
				destObjects.push_back(drawer);
			}
			else if (dynamic_cast<Flowerpot*>(srcObject))
			{
				Flowerpot* ploerpot = new Flowerpot(*dynamic_cast<Flowerpot*>(srcObject));
				destObjects.push_back(ploerpot);
			}
			else if (dynamic_cast<Bed*>(srcObject))
			{
				Bed* window = new Bed(*dynamic_cast<Bed*>(srcObject));
				destObjects.push_back(window);
			}
			else if (dynamic_cast<Shelf_Book*>(srcObject))
			{
				Shelf_Book* shelfBook = new Shelf_Book(*dynamic_cast<Shelf_Book*>(srcObject));
				destObjects.push_back(shelfBook);
			}
			else if (dynamic_cast<Table_Vertical*>(srcObject))
			{
				Table_Vertical* tableVertical = new Table_Vertical(*dynamic_cast<Table_Vertical*>(srcObject));
				destObjects.push_back(tableVertical);
			}
			else if (dynamic_cast<Curtain_Red*>(srcObject))
			{
				Curtain_Red* curtainRed = new Curtain_Red(*dynamic_cast<Curtain_Red*>(srcObject));
				destObjects.push_back(curtainRed);
			}
			else if (dynamic_cast<Closet*>(srcObject))
			{
				Closet* closet = new Closet(*dynamic_cast<Closet*>(srcObject));
				destObjects.push_back(closet);
			}
			else if (dynamic_cast<Table_Red*>(srcObject))
			{
				Table_Red* tableRed = new Table_Red(*dynamic_cast<Table_Red*>(srcObject));
				destObjects.push_back(tableRed);
			}
		}

		dest[key] = destObjects;
	}
}


std::map<std::string, std::vector<Object*>> GameManager::ApplySceneData(SCENE applyScene)
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

	return std::map<std::string, std::vector<Object*>>();
}




//------파일 입출력 관련--------


void GameManager::LoadData()
{
	FileRead("Door");
	FileRead("Window");
	FileRead("Drawer");
	FileRead("Flowerpot");
	FileRead("Bed");
	FileRead("Shelf_Book");
	FileRead("Table_Vertical");
	FileRead("Curtain_Red");
	FileRead("Closet");
	FileRead("Table_Red");
	//FileRead("Bookcase");

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
			for (int i = 0; i < 4; i++) {
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




void GameManager::InitSceneData(int _mapIndex, std::map <std::string, std::vector<Object*>>& _Object)
{ //로드해온 Object 데이터 각 Scene마다 Object 관리하는 변수에 세팅

			//Door
	std::vector<Object*> tmpObject;
	for (int i = 0; i < objectData.find("Door")->second.objectCount; i++)
	{
		//해당 맵에 배치된 Object 인지 판별
		if (_mapIndex == objectData.find("Door")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new Door(objectData.find("Door")->second, i));
	}
	_Object.insert({ "Door", tmpObject }); //pair로 만들기

	tmpObject.clear();

	//Window
	for (int i = 0; i < objectData.find("Window")->second.objectCount; i++)
	{
		//해당 맵에 배치된 Object 인지 판별
		if (_mapIndex == objectData.find("Window")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new Window(objectData.find("Window")->second, i));
	}
	_Object.insert({ "Window", tmpObject }); //pair로 만들기

	tmpObject.clear();

	//Drawer
	for (int i = 0; i < objectData.find("Drawer")->second.objectCount; i++)
	{
		//해당 맵에 배치된 Object 인지 판별
		if (_mapIndex == objectData.find("Drawer")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new Drawer(objectData.find("Drawer")->second, i));
	}
	_Object.insert({ "Drawer", tmpObject }); //pair로 만들기

	tmpObject.clear();


	//Flowerpot
	for (int i = 0; i < objectData.find("Flowerpot")->second.objectCount; i++)
	{
		//해당 맵에 배치된 Object 인지 판별
		if (_mapIndex == objectData.find("Flowerpot")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new Flowerpot(objectData.find("Flowerpot")->second, i));
	}
	_Object.insert({ "Flowerpot", tmpObject }); //pair로 만들기

	tmpObject.clear();

	//Bed
	for (int i = 0; i < objectData.find("Bed")->second.objectCount; i++)
	{
		//해당 맵에 배치된 Object 인지 판별
		if (_mapIndex == objectData.find("Bed")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new Bed(objectData.find("Bed")->second, i));
	}
	_Object.insert({ "Bed", tmpObject }); //pair로 만들기

	tmpObject.clear();

	//Shelf_Book
	for (int i = 0; i < objectData.find("Shelf_Book")->second.objectCount; i++)
	{
		//해당 맵에 배치된 Object 인지 판별
		if (_mapIndex == objectData.find("Shelf_Book")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new Shelf_Book(objectData.find("Shelf_Book")->second, i));
	}
	_Object.insert({ "Shelf_Book", tmpObject }); //pair로 만들기

	tmpObject.clear();

	//Table_Vertical
	for (int i = 0; i < objectData.find("Table_Vertical")->second.objectCount; i++)
	{
		//해당 맵에 배치된 Object 인지 판별
		if (_mapIndex == objectData.find("Table_Vertical")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new Table_Vertical(objectData.find("Table_Vertical")->second, i));
	}
	_Object.insert({ "Table_Vertical", tmpObject }); //pair로 만들기

	tmpObject.clear();

	//Curtain_Red
	for (int i = 0; i < objectData.find("Curtain_Red")->second.objectCount; i++)
	{
		//해당 맵에 배치된 Object 인지 판별
		if (_mapIndex == objectData.find("Curtain_Red")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new Curtain_Red(objectData.find("Curtain_Red")->second, i));
	}
	_Object.insert({ "Curtain_Red", tmpObject }); //pair로 만들기

	tmpObject.clear();

	//Closet
	for (int i = 0; i < objectData.find("Closet")->second.objectCount; i++)
	{
		//해당 맵에 배치된 Object 인지 판별
		if (_mapIndex == objectData.find("Closet")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new Closet(objectData.find("Closet")->second, i));
	}
	_Object.insert({ "Closet", tmpObject }); //pair로 만들기

	tmpObject.clear();

	//Table_Red
	for (int i = 0; i < objectData.find("Table_Red")->second.objectCount; i++)
	{
		//해당 맵에 배치된 Object 인지 판별
		if (_mapIndex == objectData.find("Table_Red")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new Table_Red(objectData.find("Table_Red")->second, i));
	}
	_Object.insert({ "Table_Red", tmpObject }); //pair로 만들기

	tmpObject.clear();
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






//----플레이어 관련--------

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