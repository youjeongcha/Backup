#include "GameManager.h"
#include "ObjectManager.h"
//#include "GUIManager.h"
#include "UIManager.h"

GameManager::GameManager()
{
	//수치 상태
	m_health = 20;
	m_hunger = 5;
	//m_hunger = 50;
	m_thirst = 5;
	//m_thirst = 50;
	m_fatigue = 20;
	m_isAnyStatOver90 = false;

	//경과 시간
	m_elapsedSec = 0;
	m_elapsedMin = 0;

	//TXT 파일 읽어오기
	LoadData();

	//로드해온 Object 데이터 각 Scene마다 Object 관리하는 변수에 세팅
	Initialize();


    //시간 체크
	m_elapsedSec = 0.0f;
    nowTimeLine = TimeLine_MORING; oldTimeLine = TimeLine_MORING;
    m_Clock.hour = TimeLine_NIGHT - 1;
    m_Clock.min = 57;

    timeLabel = ENGINE::UIMgr->AddUI<ENGINE::UILabel>("Time Label");
    timeLabel->Initialize("", RGB(255, 255, 255), ENGINE::GUIMgr->Get_Font(FONT_STATE));
    timeLabel->SetPosition(10, 10); // 원하는 위치로 설정
}
GameManager::~GameManager()
{
}

void GameManager::Initialize()
{
	//멤버 변수 세팅
	InitSceneData(SCENE_DOOR, mDoorObject);
	InitSceneData(SCENE_KITCHEN, mKitchenObject);
	InitSceneData(SCENE_BEDROOM, mBedRoomObject);
}

void GameManager::RenewalSceneData(SCENE saveScene, const std::map<std::string, std::vector<Object*>>& nowSceneObject)
{
	switch (saveScene)
	{
	case SCENE_DOOR:
		//ClearSceneData(mDoorObject); // 기존의 mDoorObject 해제
		//mDoorObject = nowSceneObject;
		DeepCopyMap(mDoorObject, nowSceneObject); // 깊은 복사 수행
		break;
	case SCENE_KITCHEN:
		//ClearSceneData(mKitchenObject); // 기존의 mKitchenObject 해제
		//mKitchenObject = nowSceneObject;
		DeepCopyMap(mKitchenObject, nowSceneObject); // 깊은 복사 수행
		break;
	case SCENE_BEDROOM:
		//ClearSceneData(mBedRoomObject); // 기존의 mBedRoomObject 해제
		DeepCopyMap(mBedRoomObject, nowSceneObject); // 깊은 복사 수행
		//mBedRoomObject = nowSceneObject;
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

//void GameManager::ClearSceneData(std::map<std::string, std::vector<Object*>>& sceneData)
//{
//	for (auto& pair : sceneData)
//	{
//		//for (Object* obj : pair.second)
//		//{
//		//	delete obj;
//		//}
//		pair.second.clear();
//	}
//	sceneData.clear();
//}


//void GameManager::RenewalSceneData(SCENE saveScene, const std::map <std::string, std::vector<Object*>>& nowSceneObject)
//{
//	switch (saveScene)
//	{
//	case SCENE_DOOR:
//		mDoorObject = nowSceneObject;
//		break;
//	case SCENE_KITCHEN:
//		mKitchenObject = nowSceneObject;
//		break;
//	case SCENE_BEDROOM:
//		mBedRoomObject = nowSceneObject;
//		break;
//	}
//}

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



void GameManager::Update(const FLOAT&  deltaTime)
{
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
        isDrak = true;
        ENGINE::ObjectMgr->TimeChangeBitmap(isDrak);
    }
    else if ((nowTimeLine == TimeLine_MORING) && (oldTimeLine == TimeLine_NIGHT))
    {//밤 > 낮
        isDrak = false;
		ENGINE::ObjectMgr->TimeChangeBitmap(isDrak);
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
		//TODO::하단 창 띄우기
		//TODO::하단 창 텍스트
		
		//게임 오버 화면
		//게임 오버 화면 - 텍스트
	}

    oldTimeLine = nowTimeLine;
}

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

	//for (int _mapIndex = 0; _mapIndex < SCENE_COUNT; _mapIndex++)
	{
		//std::map <std::string, std::vector<Object*>> _Object;

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
}

void GameManager::SetPlusHour(int plusHour)
{
	m_Clock.hour += plusHour;

	//24시간 경과 갱신
	if (m_Clock.hour >= TimeLine_ONEDAY)
		m_Clock.hour -= TimeLine_ONEDAY;

	//시간의 흐름에 따라 밤낮 전환(밤이 되는시간부터(20:00~24:00), 아침이 되는시간 전(0:00~5:99)까지)
	isDrak = ((m_Clock.hour >= TimeLine_NIGHT) || (m_Clock.hour < TimeLine_MORING)) ? true : false;
}


//----플레이어 관련

void GameManager::PlayerSleep()
{
	//잠자기는 허기와 갈증이 30 미만에 가능하다
	if ((m_hunger >= 30) && (m_thirst >= 30))
	{
		//TODO::화면 출력
		return;
	}

	SetPlusHour(TimeSleep);

	//허기 갈증 10 이하로 잠들었다면 건강 +10
	if ((m_hunger <= 10) && (m_thirst <= 10))
	{
		m_health += 10;

		if (m_health > 100)
			m_health = 100;
	}

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