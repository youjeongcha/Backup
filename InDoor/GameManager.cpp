#include "GameManager.h"

GameManager::GameManager()
{
	Inventory_UI = nullptr;

	//TXT ���� �о����
	LoadData();
	LoadUnderTxt();

	//�̹��� ���ҽ� �ε� : �κ��丮 + ������
	ENGINE::ResourceMgr->Load("Inventory_panel.bmp");


	//Night and GameOver and Sleep
	ENGINE::ResourceMgr->Load("Black.bmp");
	night = ENGINE::ResourceMgr->GetBitmap("Black.bmp");
	night->SetDrawSize(ENGINE::SceneMgr->GetWidth(), ENGINE::SceneMgr->GetHeight());

	//ENGINE::ResourceMgr->Load("UnderSection.bmp");
	//underSection = ENGINE::ResourceMgr->GetBitmap("UnderSection.bmp");
	//underSection->SetDrawSize(ENGINE::SceneMgr->GetWidth(), 30);

	//�ð� üũ
	timeLabel = ENGINE::UIMgr->AddUI<ENGINE::UILabel>("Time Label");
	timeLabel->Initialize("", RGB(255, 255, 255), ENGINE::GUIMgr->Get_Font(FONT_STATE));
	timeLabel->SetPosition(10, 10); // ���ϴ� ��ġ�� ����

	ENGINE::ResourceMgr->Load("UnderSection.bmp");
	underTxt_Section = ENGINE::UIMgr->AddUI<ENGINE::UIButton>("Under Btn"); //���� �̸����� ����
	underTxt_Section->Initialize("UnderSection.bmp", "UnderSection.bmp", "", "", ENGINE::DrawType::AlphaBlend);
	underTxt_Section->SetLocalPosition(0, ENGINE::SceneMgr->GetHeight() - underTxt_Section->GetSize().cy, false);
	underTxt_Section->SetListener(std::bind(&GameManager::NextShowUnderSection, this, false));

	//�ϴ� �ؽ�Ʈ ����
	txtLabel = ENGINE::UIMgr->AddUI<ENGINE::UILabel>("Txt Label", underTxt_Section);
	txtLabel->Initialize("", RGB(255, 255, 255), ENGINE::GUIMgr->Get_Font(FONT_UNDERTXT));
	txtLabel->SetPosition(ENGINE::SceneMgr->GetWidth() / 3, ENGINE::SceneMgr->GetHeight() - 20); // ���ϴ� ��ġ�� ����


	//GameOver
	ENGINE::ResourceMgr->Load("GameOver.bmp");
	gameOver = ENGINE::ResourceMgr->GetBitmap("GameOver.bmp");
	//��ǥ
	gameOver_X = ENGINE::SceneMgr->GetWidth() - gameOver->GetSize().cx * 1.55;
	gameOver_Y = ENGINE::SceneMgr->GetHeight() / 2 - gameOver->GetSize().cy;
	

	//���� ���� ������
	ENGINE::ResourceMgr->Load("Select_Panel.bmp");
	ENGINE::UIMgr->Remove("Optional Form_1");
	select_Restart = ENGINE::UIMgr->AddUI<ENGINE::UIImage>("Optional Form_1");
	select_Restart->Initialize("Select_Panel.bmp", ENGINE::DrawType::Transparent);
	select_Restart->SetLocalPosition(ENGINE::SceneMgr->GetWidth() - select_Restart->GetSize().cx * 1.95, gameOver_Y + 55, true);

	int selectBtn_X, selectBtn_Y;
	selectBtn_X = select_Restart->GetSize().cx * 0.5f;
	selectBtn_Y = 13;
	
	//����� - ��ư
	ENGINE::ResourceMgr->Load("Btn_Restart_Normal.bmp");
	ENGINE::ResourceMgr->Load("Btn_Restart_Pressed.bmp");
	ENGINE::UIButton* btn_Restart = ENGINE::UIMgr->AddUI<ENGINE::UIButton>("Optional Restart Btn", select_Restart);
	btn_Restart->Initialize("Btn_Restart_Normal.bmp", "Btn_Restart_Pressed.bmp", "", "", ENGINE::DrawType::Transparent);
	btn_Restart->SetLocalPosition(selectBtn_X, selectBtn_Y, true);
	btn_Restart->SetListener(std::bind(&GameManager::Restart, this));

	//����� - ������ ����
	ENGINE::UILabel* btn_txt = ENGINE::UIMgr->AddUI<ENGINE::UILabel>("Restart Txt", btn_Restart);
	btn_txt->SetLocalPosition(FONT_SELECT_X, FONT_SELECT_Y, true);
	btn_txt->Initialize("�����", RGB(255, 255, 255), ENGINE::GUIMgr->Get_Font(FONT_SELECT));


	//---------------------
	//�ε��ؿ� Object ������ �� Scene���� Object �����ϴ� ������ ����
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
	isReset_OneTime = false;

	isDark = false;
	isShowUnderTxt = false;
	
	timeLabel->SetEnable(true);
	select_Restart->SetEnable(false);
	underTxt_Section->SetEnable(false);

	//�ϴ� �ؽ�Ʈ ���� ���� �ʱ� ���ð�
	nowShowUnderTxt = UNDERTXT_NONE;
	prevShowUnderTxt = UNDERTXT_NONE;

	//��ġ ����
	m_health = 5;
	//m_hunger = 100;
	 m_hunger = 30;
	m_thirst = 40;
	//m_thirst = 50;
	m_fatigue = 20;

	//��� �ð�
	m_elapsedSec = 0;
	m_elapsedMin = 0;

	//�ð� üũ
	m_elapsedSec = 0.0f;
	nowTimeLine = TimeLine_MORING; oldTimeLine = TimeLine_MORING;
	m_Clock.hour = TimeLine_NIGHT - 1;
	m_Clock.min = 00;

	//�ε��ؿ� Object ������ �� Scene���� Object �����ϴ� ������ ����
	Delete_SceneObject();
	Initialize();
}


void GameManager::Initialize()
{
	//��� ���� ����
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
		ShowUnderSectionTxt(); //�������� �����ϸ� �ش� �Լ����� ������ �ϰ� �������� ���´�.

	if (isDark)
	{
		night->AlphaBlendBlt(0, 0, ENGINE::SceneMgr->GetHeight() - 30);
	}
}




void GameManager::Update(const FLOAT&  deltaTime)
{
	if (isGameOver)
		return;

    //�ð� ��� ī��Ʈ
	//��� �ð� ������Ʈ(1�ʰ� ���ӻ� 1��)
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

		//----------�÷��̾� ����--------------
		// �Ƿ�, ���, ������ 100�� �Ǹ� > �ǰ��� 1�ʸ��� 1�� ���δ�.
		if ((m_fatigue == 100) || (m_thirst == 100) || (m_hunger == 100))
		{
			m_health -= 1;

			//�ּ�ġ ����
			if (m_health < 0)
				m_health = 0;
		}
    }


    //24�ð� ��� ����
    if (m_Clock.hour >= TimeLine_ONEDAY)
        m_Clock.hour -= TimeLine_ONEDAY;


    //�ð��� ���(�� ��)
    if ((m_Clock.hour >= TimeLine_MORING) && (m_Clock.hour < TimeLine_NIGHT))
        nowTimeLine = TimeLine_MORING;
    else
        nowTimeLine = TimeLine_NIGHT;


    //�ð��� ���� �޶����� ��ҵ� ó��(Object, NPC��)

    //���� ��ȯ�� ���� �ܼ� BitpMap �ٲ�� ��ҵ�
    if ((nowTimeLine == TimeLine_NIGHT) && (oldTimeLine == TimeLine_MORING))
    {//�� > ��
		isDark = true;
        ENGINE::ObjectMgr->TimeChangeBitmap(isDark);
    }
    else if ((nowTimeLine == TimeLine_MORING) && (oldTimeLine == TimeLine_NIGHT))
    {//�� > ��
		isDark = false;
		ENGINE::ObjectMgr->TimeChangeBitmap(isDark);
    }



	//----------�÷��̾� ����--------------

	//30�и��� �Ƿ�, ����, ��� ����
	if (m_elapsedMin >= 30) {
		m_elapsedMin = 0; //��� �ð� �ʱ�ȭ

		//�Ƿ�, ����, ��� ����
		m_fatigue += 5;
		m_thirst += 5;
		m_hunger += 5;

		//�Ƿ�, ���, ������ 90 �̻��� �Ǹ� > �ǰ��� 30�ʸ��� 5�� ���δ�.
		if ((m_fatigue >= 90) || (m_thirst >= 90) || (m_hunger >= 90))
			m_health -= 5;

		//��ġ�� �ִ� �ּҰ� ���� �ʵ��� ����
		if (m_health < 0)
			m_health = 0;
		if (m_fatigue > 100)
			m_fatigue = 100;
		if (m_thirst > 100)
			m_thirst = 100;
		if (m_hunger > 100)
			m_hunger = 100;
	}

	//-------GameOver   or   GameClear(�� ���� ���� üũ)-------
	if (m_health == 0)
	{
		isGameOver = true;
		isReset_OneTime = true; //���ӿ����ǰ� ���� ���� �Լ�(��, �÷��̾� ��ġ) 1ȸ ����
		//��� ����â ����
		select_Restart->SetEnable(true);
		timeLabel->SetEnable(false);
		//TODO::�ϴ� â ����
		//TODO::�ϴ� â �ؽ�Ʈ
		
		//���� ���� ȭ��
		//���� ���� ȭ�� - �ؽ�Ʈ
	}
	else if (m_health == 100)
	{
		isGameClear = true;
	}

    oldTimeLine = nowTimeLine;
}

void GameManager::LoadUnderTxt()
{
	// ���� ��Ʈ�� ����
	std::ifstream load("Data/UnderTxt.txt");

	// ������ ���������� ���ȴ��� Ȯ��
	if (load.is_open()) {
		int i = UNDERTXT_START;
		int lineCount;

		while (load >> lineCount && i < UNDERTXT_COUNT) {
			std::string line;
			std::getline(load, line); // ���� ���� ó��

			std::vector<std::string> txt;
			for (int j = 0; j < lineCount; ++j) {
				std::getline(load, line);
				txt.push_back(line);
			}

			mUnderTxt[static_cast<UNDERTXT>(i)] = txt;
			i++;
		}

		// ���� ��Ʈ�� �ݱ�
		load.close();
	}

	/*
	// ���� ��Ʈ�� ����
	std::ifstream load("Data/UnderTxt.txt");

	//������Ʈ ��ü �ϳ��� ������ ������
	ObjectData tmpObjectData; //�ϳ��� ���� ����

	// ������ ���������� ���ȴ��� Ȯ��
	if (load.is_open()) {

		// �� ������ �ؽ�Ʈ �о mUnderTxt�� ����
		std::string line;
		int i = UNDERTXT_START;

		while (std::getline(load, line) && i < UNDERTXT_COUNT) {
			mUnderTxt[static_cast<UNDERTXT>(i)] = line;
			i++;
		}

		// ���� ��Ʈ�� �ݱ�
		load.close();
	}*/
}

void GameManager::ShowUnderSectionTxt()
{ //ù��° �ؽ�Ʈ �㶧 ������ ���İ��� �ȴ�.

	//���� prevShowUnderTxt���� nowShowUnderTxt ���� �ٸ��� ��� �ؽ�Ʈ�� ��ȭ�Ѱ��̴�. �ε��� ī��Ʈ ���� �ʱ� ���� �ʿ�
	if (prevShowUnderTxt != nowShowUnderTxt)
	{
		//���� ���� ���� ���� �޶����� ó���� ������ �ʿ�
		prevShowUnderTxt = nowShowUnderTxt;

		//��� �����ϴ� �ؽ�Ʈ ������ �ε���
		indexShowUnderTxt = 0;
	}
	

	//�ؽ�Ʈ ������� ���� ��� �ε����� ���ؼ� ���� ���ش�.
		//������ �ؽ�Ʈ ���
	if (mUnderTxt.find(nowShowUnderTxt)->second.size() == (indexShowUnderTxt + 1)) //size�� 1���� ���� indexShowUnderTxt�� 0���� �����̹Ƿ�
		underTxt_Section->SetListener(std::bind(&GameManager::NextShowUnderSection, this, false));
	else
		//���ٷ� ������ �ؽ�Ʈ �ƴϸ� �̾ ����ϵ��� �缼���� �ʿ��ϴ�.
		underTxt_Section->SetListener(std::bind(&GameManager::NextShowUnderSection, this, true));



	//�ؽ�Ʈâ�� ������ ������ â�� �ؽ�Ʈ ����

	//�ϴ� �ؽ�Ʈâ
	underTxt_Section->SetEnable(true);

	underTxt_Section->Set_Transparency(UNDER_SECTION_TRANSPARENCY); //����ȭ ���ϴ� ��(0 ~ 255)
	underTxt_Section->Draw();

	//�ϴ� �ؽ�Ʈ ǥ��
	txtLabel->SetEnable(true);

	char timeStr[100];
	//sprintf_s(timeStr, sizeof(timeStr), "�ϴ� �ؽ�Ʈ�� ����.");
	sprintf_s(timeStr, sizeof(timeStr), mUnderTxt.find(nowShowUnderTxt)->second[indexShowUnderTxt].c_str());
	txtLabel->SetText(timeStr);
}

//void GameManager::DisableUnderSection()
void GameManager::NextShowUnderSection(bool isNextTxt)
{ //�ϴ�â(��ư)�� ������ �Ǹ� ������ �Ǵ��Լ�. ���� > isNextTxt false / ������ > isNextText true��
	//���� �ؽ�Ʈ ���� - Object �ϴ� â
	if (!isNextTxt)
	{
		indexShowUnderTxt = 0;
		isShowUnderTxt = false;
		underTxt_Section->SetEnable(false);
		txtLabel->SetEnable(false);
		Set_IsPause(false);
	}
	else //���� �ؽ�Ʈ ���� - NPC �ϴ� â
	{
		//�ϴ�â �ؽ�Ʈ ��� > ù��° �ε��� ����ϰ� ���� �ε��� ����ؾ��Ҷ� �ش� �Լ��� ���´�
		indexShowUnderTxt++;

		char timeStr[100];
		//�ش� �ؽ�Ʈ ���� ����صΰ� ����ؾ� �Ѵ�. indexShowUnderTxt�� �ε��� �����Ѵ� TODO::::::::::::::::::::::::::::::::::::::
		sprintf_s(timeStr, sizeof(timeStr), mUnderTxt.find(nowShowUnderTxt)->second[indexShowUnderTxt].c_str());
		txtLabel->SetText(timeStr);
	}
}


void GameManager::RenewalSceneData(SCENE saveScene, const std::map<std::string, std::vector<Object*>>& nowSceneObject)
{
	switch (saveScene)
	{
	case SCENE_DOOR:
		DeepCopyMap(mDoorObject, nowSceneObject); // ���� ���� ����
		break;
	case SCENE_KITCHEN:
		DeepCopyMap(mKitchenObject, nowSceneObject); // ���� ���� ����
		break;
	case SCENE_BEDROOM:
		DeepCopyMap(mBedRoomObject, nowSceneObject); // ���� ���� ����
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
			// �߻� Ŭ������ Object ��� ������ Ÿ������ ��ü�� �����Ͽ� ĳ����
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
			else if (dynamic_cast<Bookcase*>(srcObject))
			{
				Bookcase* bookcase = new Bookcase(*dynamic_cast<Bookcase*>(srcObject));
				destObjects.push_back(bookcase);
			}
			else if (dynamic_cast<Stove*>(srcObject))
			{
				Stove* stove = new Stove(*dynamic_cast<Stove*>(srcObject));
				destObjects.push_back(stove);
			}
			else if (dynamic_cast<KitchenCounter*>(srcObject))
			{
				KitchenCounter* counter = new KitchenCounter(*dynamic_cast<KitchenCounter*>(srcObject));
				destObjects.push_back(counter);
			}			
			else if (dynamic_cast<FirePot*>(srcObject))
			{
				FirePot* firepot = new FirePot(*dynamic_cast<FirePot*>(srcObject));
				destObjects.push_back(firepot);
			}
			else if (dynamic_cast<Sideboard*>(srcObject))
			{
				Sideboard* sideboard = new Sideboard(*dynamic_cast<Sideboard*>(srcObject));
				destObjects.push_back(sideboard);
			}
			
			else if (dynamic_cast<WallHanging*>(srcObject))
			{
				WallHanging* sideboard = new WallHanging(*dynamic_cast<WallHanging*>(srcObject));
				destObjects.push_back(sideboard);
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






//------���� ����� ����--------


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
	FileRead("Bookcase");
	FileRead("Stove");
	FileRead("KitchenCounter");
	FileRead("FirePot");
	FileRead("Sideboard");
	FileRead("WallHanging");


}


void GameManager::FileRead(const std::string& file) {

	std::ifstream load("Data/" + file + ".txt");

	//������Ʈ ��ü �ϳ��� ������ ������
	ObjectData tmpObjectData; //�ϳ��� ���� ����

	if (load.is_open()) {
		std::string line;

		// �о�� �����Ͱ� �ִ��� Ȯ��
		if (std::getline(load, line)) {
			//������Ʈ ��Ī(���ϸ��� ����)
			tmpObjectData.objectName = file;

			// ��� Ÿ��
			std::istringstream typeStream(line);

			std::string typeCheckValue;
			for (int i = 0; i < 4; i++) {
				typeStream >> typeCheckValue;
				if (typeCheckValue == "true") //���ڿ��� ���� false�� �Ǵ�
					tmpObjectData.typeCheck[static_cast<OBJECT_TYPE>(i)] = true;
				else
					tmpObjectData.typeCheck[static_cast<OBJECT_TYPE>(i)] = false;
			}

			// ���ø� �и� xy
			std::getline(load, line);
			std::istringstream splitStream(line);
			splitStream >> tmpObjectData.spritesX;
			splitStream >> tmpObjectData.spritesY;

			// �̹��� ����
			std::getline(load, line);
			tmpObjectData.fileName = line;

			//�� ������
			std::string sTmp;
			std::getline(load, line);
			std::istringstream selectStream(line);
			selectStream >> tmpObjectData.detailSelectCount;
			for (int i = 0; i < tmpObjectData.detailSelectCount; i++)
			{
				selectStream >> sTmp;
				tmpObjectData.sDetailSelect.push_back(sTmp);
			}


			// �� ����
			std::getline(load, line);
			std::istringstream countStream(line);
			countStream >> tmpObjectData.objectCount;

			// ������Ʈ ��ü �ϳ��� ������ ������
			for (int i = 0; i < tmpObjectData.objectCount; ++i)
			{
				std::getline(load, line);
				std::istringstream objStream(line);
				EachObject tmpEachObject; //���� �� ���� �ȿ��� ��ü�� ����

				//�̸�
				objStream >> tmpEachObject.objectIndex.name;

				// ��� ���� �ε���
				objStream >> tmpEachObject.objectIndex.mapIndex;
				//�ʸ��� �ش� ������Ʈ�� ���° ��ȣ����
				objStream >> tmpEachObject.objectIndex.eachObjectIndex;

				// ���� ����
				bool bTmp;

				std::string typeCheckValue;
				for (int i = 0; i < 4; i++) {

					objStream >> typeCheckValue;

					if (typeCheckValue == "true") //���ڿ��� ���� false�� �Ǵ�
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

				// ��ǥ
				objStream >> tmpEachObject.x;
				objStream >> tmpEachObject.y;
				// ��ġ �̵� ����
				objStream >> tmpEachObject.move_X;
				objStream >> tmpEachObject.move_Y;
				objStream >> tmpEachObject.move_Speed;


				tmpObjectData.eachObject.push_back(new EachObject(tmpEachObject));
			}
		}
		objectData.insert({ file, tmpObjectData }); //pair�� �����
		load.close();
	}

	//saveObjectData = objectData;
}




void GameManager::InitSceneData(int _mapIndex, std::map <std::string, std::vector<Object*>>& _Object)
{ //�ε��ؿ� Object ������ �� Scene���� Object �����ϴ� ������ ����

	//Door
	std::vector<Object*> tmpObject;
	for (int i = 0; i < objectData.find("Door")->second.objectCount; i++)
	{
		//�ش� �ʿ� ��ġ�� Object ���� �Ǻ�
		if (_mapIndex == objectData.find("Door")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new Door(objectData.find("Door")->second, i));
	}
	_Object.insert({ "Door", tmpObject }); //pair�� �����

	tmpObject.clear();

	//Window
	for (int i = 0; i < objectData.find("Window")->second.objectCount; i++)
	{
		//�ش� �ʿ� ��ġ�� Object ���� �Ǻ�
		if (_mapIndex == objectData.find("Window")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new Window(objectData.find("Window")->second, i));
	}
	_Object.insert({ "Window", tmpObject }); //pair�� �����

	tmpObject.clear();

	//Drawer
	for (int i = 0; i < objectData.find("Drawer")->second.objectCount; i++)
	{
		//�ش� �ʿ� ��ġ�� Object ���� �Ǻ�
		if (_mapIndex == objectData.find("Drawer")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new Drawer(objectData.find("Drawer")->second, i));
	}
	_Object.insert({ "Drawer", tmpObject }); //pair�� �����

	tmpObject.clear();


	//Flowerpot
	for (int i = 0; i < objectData.find("Flowerpot")->second.objectCount; i++)
	{
		//�ش� �ʿ� ��ġ�� Object ���� �Ǻ�
		if (_mapIndex == objectData.find("Flowerpot")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new Flowerpot(objectData.find("Flowerpot")->second, i));
	}
	_Object.insert({ "Flowerpot", tmpObject }); //pair�� �����

	tmpObject.clear();

	//Bed
	for (int i = 0; i < objectData.find("Bed")->second.objectCount; i++)
	{
		//�ش� �ʿ� ��ġ�� Object ���� �Ǻ�
		if (_mapIndex == objectData.find("Bed")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new Bed(objectData.find("Bed")->second, i));
	}
	_Object.insert({ "Bed", tmpObject }); //pair�� �����

	tmpObject.clear();

	//Shelf_Book
	for (int i = 0; i < objectData.find("Shelf_Book")->second.objectCount; i++)
	{
		//�ش� �ʿ� ��ġ�� Object ���� �Ǻ�
		if (_mapIndex == objectData.find("Shelf_Book")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new Shelf_Book(objectData.find("Shelf_Book")->second, i));
	}
	_Object.insert({ "Shelf_Book", tmpObject }); //pair�� �����

	tmpObject.clear();

	//Table_Vertical
	for (int i = 0; i < objectData.find("Table_Vertical")->second.objectCount; i++)
	{
		//�ش� �ʿ� ��ġ�� Object ���� �Ǻ�
		if (_mapIndex == objectData.find("Table_Vertical")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new Table_Vertical(objectData.find("Table_Vertical")->second, i));
	}
	_Object.insert({ "Table_Vertical", tmpObject }); //pair�� �����

	tmpObject.clear();

	//Curtain_Red
	for (int i = 0; i < objectData.find("Curtain_Red")->second.objectCount; i++)
	{
		//�ش� �ʿ� ��ġ�� Object ���� �Ǻ�
		if (_mapIndex == objectData.find("Curtain_Red")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new Curtain_Red(objectData.find("Curtain_Red")->second, i));
	}
	_Object.insert({ "Curtain_Red", tmpObject }); //pair�� �����

	tmpObject.clear();

	//Closet
	for (int i = 0; i < objectData.find("Closet")->second.objectCount; i++)
	{
		//�ش� �ʿ� ��ġ�� Object ���� �Ǻ�
		if (_mapIndex == objectData.find("Closet")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new Closet(objectData.find("Closet")->second, i));
	}
	_Object.insert({ "Closet", tmpObject }); //pair�� �����

	tmpObject.clear();

	//Table_Red
	for (int i = 0; i < objectData.find("Table_Red")->second.objectCount; i++)
	{
		//�ش� �ʿ� ��ġ�� Object ���� �Ǻ�
		if (_mapIndex == objectData.find("Table_Red")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new Table_Red(objectData.find("Table_Red")->second, i));
	}
	_Object.insert({ "Table_Red", tmpObject }); //pair�� �����

	tmpObject.clear();	
	
	//Bookcase
	for (int i = 0; i < objectData.find("Bookcase")->second.objectCount; i++)
	{
		//�ش� �ʿ� ��ġ�� Object ���� �Ǻ�
		if (_mapIndex == objectData.find("Bookcase")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new Bookcase(objectData.find("Bookcase")->second, i));
	}
	_Object.insert({ "Bookcase", tmpObject }); //pair�� �����

	tmpObject.clear();	
	
	//Stove
	for (int i = 0; i < objectData.find("Stove")->second.objectCount; i++)
	{
		//�ش� �ʿ� ��ġ�� Object ���� �Ǻ�
		if (_mapIndex == objectData.find("Stove")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new Stove(objectData.find("Stove")->second, i));
	}
	_Object.insert({ "Stove", tmpObject }); //pair�� �����

	tmpObject.clear();

	//KitchenCounter
	for (int i = 0; i < objectData.find("KitchenCounter")->second.objectCount; i++)
	{
		//�ش� �ʿ� ��ġ�� Object ���� �Ǻ�
		if (_mapIndex == objectData.find("KitchenCounter")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new KitchenCounter(objectData.find("KitchenCounter")->second, i));
	}
	_Object.insert({ "KitchenCounter", tmpObject }); //pair�� �����

	tmpObject.clear();
	
	//FirePot
	for (int i = 0; i < objectData.find("FirePot")->second.objectCount; i++)
	{
		//�ش� �ʿ� ��ġ�� Object ���� �Ǻ�
		if (_mapIndex == objectData.find("FirePot")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new FirePot(objectData.find("FirePot")->second, i));
	}
	_Object.insert({ "FirePot", tmpObject }); //pair�� �����

	tmpObject.clear();

	//Sideboard
	for (int i = 0; i < objectData.find("Sideboard")->second.objectCount; i++)
	{
		//�ش� �ʿ� ��ġ�� Object ���� �Ǻ�
		if (_mapIndex == objectData.find("Sideboard")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new Sideboard(objectData.find("Sideboard")->second, i));
	}
	_Object.insert({ "Sideboard", tmpObject }); //pair�� �����

	tmpObject.clear();
	
	//Sideboard
	for (int i = 0; i < objectData.find("WallHanging")->second.objectCount; i++)
	{
		//�ش� �ʿ� ��ġ�� Object ���� �Ǻ�
		if (_mapIndex == objectData.find("WallHanging")->second.eachObject[i]->objectIndex.mapIndex)
			tmpObject.push_back(new WallHanging(objectData.find("WallHanging")->second, i));
	}
	_Object.insert({ "WallHanging", tmpObject }); //pair�� �����

	tmpObject.clear();
}

void GameManager::SetPlusHour(int plusHour)
{
	m_Clock.hour += plusHour;

	//24�ð� ��� ����
	if (m_Clock.hour >= TimeLine_ONEDAY)
		m_Clock.hour -= TimeLine_ONEDAY;

	//�ð��� �帧�� ���� �㳷 ��ȯ(���� �Ǵ½ð�����(20:00~24:00), ��ħ�� �Ǵ½ð� ��(0:00~5:99)����)
	isDark = ((m_Clock.hour >= TimeLine_NIGHT) || (m_Clock.hour < TimeLine_MORING)) ? true : false;
}






//--------------�÷��̾� ����-------------------

void GameManager::PlayerSleep()
{
	//�ϴ� �ؽ�Ʈ�� �����ϴ� ������ �۵� �Լ�
	isShowUnderTxt = true;

	//���ڱ�� ���� ������ 30 �̸��� �����ϴ�
	if ((m_hunger >= 30) || (m_thirst >= 30))
	{
		//�ϴ�â �ؽ�Ʈ ���
		nowShowUnderTxt = BED_SLEEP_X;
		return;
	}

	SetPlusHour(TimeSleep);

	//��� ���� 10 ���Ϸ� �����ٸ� �ǰ� +10
	if ((m_hunger <= 10) && (m_thirst <= 10))
	{
		m_health += 10;

		if (m_health > 100)
		{
			m_health = 100;
			nowShowUnderTxt = BED_SLEEP_O_HEALTH_GAMECLEAR; //�ǰ� +10 �� ���� ���� �� �ִ�.
		}
		else //�ǰ� +10
			nowShowUnderTxt = BED_SLEEP_O_HEALTH;
	}
	else //�Ϲ������� �����
		nowShowUnderTxt = BED_SLEEP_O;


	//��ġ ����
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


//-------------------�κ��丮---------------------

void GameManager::Inventory(Player& player)
{
	std::vector<std::pair<ITEM, int>> player_ItemList;
	ENGINE::UIMgr->Remove("Inventory");
	Inventory_UI = ENGINE::UIMgr->AddUI<ENGINE::UIImage>("Inventory");
	Inventory_UI->Initialize("Inventory_panel.bmp", ENGINE::DrawType::AlphaBlend); //������ ���� �����ϰԲ�
	Inventory_UI->Set_Transparency(INVENTORY_TRANSPARENCY); //����ȭ ���ϴ� ��(0 ~ 255)


	if (Inventory_UI)
	{
		int i, selectBtn_X, selectBtn_Y;
		GameMgr->Set_IsPause(true);

		Inventory_UI->SetPosition(UI_INVENTORY_X, UI_INVENTORY_Y, false);

		selectBtn_X = Inventory_UI->GetSize().cx * 0.5f;
		selectBtn_Y = 17;


		//�κ��丮�� ���� �ִ� ������ ����ŭ ������ ĭ ����
		for (i = 0; i < player.GetItemList().size(); i++)
		{
			Item* useItem = ItemMgr->GetItemList().find(player_ItemList[i].first)->second;
			std::string itemName = useItem->GetName();

			//��ư-������
			ENGINE::UIButton* btn_select = ENGINE::UIMgr->AddUI<ENGINE::UIButton>("Optional " + std::to_string(i + 1) + itemName, Inventory_UI); //���� �̸����� ���� ex.Home_Flowerpot.bmp
			//ENGINE::UIButton* btn_select = ENGINE::UIMgr->AddUI<ENGINE::UIButton>("Optional " + std::to_string(i + 1) + "_" + (*interObject)[i]->GetObjectName() + " Btn", Inventory_UI); //���� �̸����� ���� ex.Home_Flowerpot.bmp
			btn_select->Initialize("Select_Btn_Normal.bmp", "Select_Btn_Pressed.bmp", "", "", ENGINE::DrawType::Transparent);
			btn_select->SetLocalPosition(selectBtn_X, selectBtn_Y, true);
			btn_select->SetListener(std::bind(&GameManager::ItemUseBtnClickHandler, this, useItem));

			//������ ����
			ENGINE::UILabel* btn_txt = ENGINE::UIMgr->AddUI<ENGINE::UILabel>(itemName + "Txt", btn_select);
			btn_txt->SetLocalPosition(FONT_SELECT_X, FONT_SELECT_Y, true);
			btn_txt->Initialize(itemName, RGB(255, 255, 205), ENGINE::GUIMgr->Get_Font(FONT_SELECT));

			selectBtn_X += 25;

			//�κ��丮 ĭ 3�� ������ ���� �ٷ� ������ ��ġ
			if (selectBtn_X >= 75)
			{
				selectBtn_X = 0;
				selectBtn_Y += 25;
			}
		}


		ENGINE::UIButton* btn_Cancel = ENGINE::UIMgr->AddUI<ENGINE::UIButton>("CancelBtn_Panel_" + std::to_string(i + 1), Inventory_UI);
		btn_Cancel->Initialize("Select_Btn_Normal.bmp", "Select_Btn_Pressed.bmp", "", "", ENGINE::DrawType::Transparent);
		btn_Cancel->SetLocalPosition(selectBtn_X, selectBtn_Y, true);
		btn_Cancel->SetListener(std::bind(&GameManager::CancelBtnClickHandler, this));

		//������ ����
		ENGINE::UILabel* btnCancel_txt = ENGINE::UIMgr->AddUI<ENGINE::UILabel>("Cancel_Txt" + std::to_string(i + 1), btn_Cancel);
		btnCancel_txt->SetLocalPosition(FONT_SELECT_X, FONT_SELECT_Y, true);
		btnCancel_txt->Initialize("���", RGB(255, 255, 255), ENGINE::GUIMgr->Get_Font(FONT_SELECT));
	}
}

void GameManager::ItemUseBtnClickHandler(Item* useItem)
{
	useItem->Use();
	Inventory_UI->SetEnable(FALSE);
}

void GameManager::CancelBtnClickHandler()
{
	Inventory_UI->SetEnable(FALSE);
	isPause = false;
	isInventory = false; //�κ��丮�� �����ȴ�.(�κ��丮 ��)
}