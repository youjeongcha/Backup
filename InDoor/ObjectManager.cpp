#include "ObjectManager.h"
#include "DemoScene.h"

namespace ENGINE
{
	ObjectManager::ObjectManager()
	{
		LoadData();
	}

	ObjectManager::~ObjectManager()
	{
		Delete_mObject();
	}

	void ObjectManager::LoadData()
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


	void ObjectManager::Delete_mObject()
	{
		if (mObject.size() > 0)
		{
			for (std::map<std::string, std::vector<Object*>>::iterator iter = mObject.begin(); iter != mObject.end(); iter++)
			{
				for (Object* obj : iter->second)
				{
					delete obj;
				}
				iter->second.clear();
			}
		}
		mObject.clear();
	}

	void ObjectManager::InitSetting(int _mapIndex, bool isDrak)
	{
		//map 변경될때마다 객체 설정 다시 하기
		Delete_mObject();

		//Door
		std::vector<Object*> tmpObject;
		for (int i = 0; i < objectData.find("Door")->second.objectCount; i++)
		{
			//해당 맵에 배치된 Object 인지 판별
			if (_mapIndex == objectData.find("Door")->second.eachObject[i]->objectIndex.mapIndex)
				tmpObject.push_back(new Door(objectData.find("Door")->second, i));
		}
		mObject.insert({ "Door", tmpObject }); //pair로 만들기

		tmpObject.clear();

		//Window
		for (int i = 0; i < objectData.find("Window")->second.objectCount; i++)
		{
			//해당 맵에 배치된 Object 인지 판별
			if (_mapIndex == objectData.find("Window")->second.eachObject[i]->objectIndex.mapIndex)
				tmpObject.push_back(new Window(objectData.find("Window")->second, i));
		}
		mObject.insert({ "Window", tmpObject }); //pair로 만들기

		tmpObject.clear();

		//Drawer
		for (int i = 0; i < objectData.find("Drawer")->second.objectCount; i++)
		{
			//해당 맵에 배치된 Object 인지 판별
			if (_mapIndex == objectData.find("Drawer")->second.eachObject[i]->objectIndex.mapIndex)
				tmpObject.push_back(new Drawer(objectData.find("Drawer")->second, i));
		}
		mObject.insert({ "Drawer", tmpObject }); //pair로 만들기

		tmpObject.clear();


		//Flowerpot
		for (int i = 0; i < objectData.find("Flowerpot")->second.objectCount; i++)
		{
			//해당 맵에 배치된 Object 인지 판별
			if (_mapIndex == objectData.find("Flowerpot")->second.eachObject[i]->objectIndex.mapIndex)
				tmpObject.push_back(new Flowerpot(objectData.find("Flowerpot")->second, i));
		}
		mObject.insert({ "Flowerpot", tmpObject }); //pair로 만들기

		tmpObject.clear();

		//Bed
		for (int i = 0; i < objectData.find("Bed")->second.objectCount; i++)
		{
			//해당 맵에 배치된 Object 인지 판별
			if (_mapIndex == objectData.find("Bed")->second.eachObject[i]->objectIndex.mapIndex)
				tmpObject.push_back(new Bed(objectData.find("Bed")->second, i));
		}
		mObject.insert({ "Bed", tmpObject }); //pair로 만들기

		tmpObject.clear();		
		
		//Shelf_Book
		for (int i = 0; i < objectData.find("Shelf_Book")->second.objectCount; i++)
		{
			//해당 맵에 배치된 Object 인지 판별
			if (_mapIndex == objectData.find("Shelf_Book")->second.eachObject[i]->objectIndex.mapIndex)
				tmpObject.push_back(new Shelf_Book(objectData.find("Shelf_Book")->second, i));
		}
		mObject.insert({ "Shelf_Book", tmpObject }); //pair로 만들기

		tmpObject.clear();

		//Table_Vertical
		for (int i = 0; i < objectData.find("Table_Vertical")->second.objectCount; i++)
		{
			//해당 맵에 배치된 Object 인지 판별
			if (_mapIndex == objectData.find("Table_Vertical")->second.eachObject[i]->objectIndex.mapIndex)
				tmpObject.push_back(new Table_Vertical(objectData.find("Table_Vertical")->second, i));
		}
		mObject.insert({ "Table_Vertical", tmpObject }); //pair로 만들기

		tmpObject.clear();		
		
		//Curtain_Red
		for (int i = 0; i < objectData.find("Curtain_Red")->second.objectCount; i++)
		{
			//해당 맵에 배치된 Object 인지 판별
			if (_mapIndex == objectData.find("Curtain_Red")->second.eachObject[i]->objectIndex.mapIndex)
				tmpObject.push_back(new Curtain_Red(objectData.find("Curtain_Red")->second, i));
		}
		mObject.insert({ "Curtain_Red", tmpObject }); //pair로 만들기

		tmpObject.clear();	
		
		//Closet
		for (int i = 0; i < objectData.find("Closet")->second.objectCount; i++)
		{
			//해당 맵에 배치된 Object 인지 판별
			if (_mapIndex == objectData.find("Closet")->second.eachObject[i]->objectIndex.mapIndex)
				tmpObject.push_back(new Closet(objectData.find("Closet")->second, i));
		}
		mObject.insert({ "Closet", tmpObject }); //pair로 만들기

		tmpObject.clear();	
		
		//Table_Red
		for (int i = 0; i < objectData.find("Table_Red")->second.objectCount; i++)
		{
			//해당 맵에 배치된 Object 인지 판별
			if (_mapIndex == objectData.find("Table_Red")->second.eachObject[i]->objectIndex.mapIndex)
				tmpObject.push_back(new Table_Red(objectData.find("Table_Red")->second, i));
		}
		mObject.insert({ "Table_Red", tmpObject }); //pair로 만들기

		tmpObject.clear();
	}


	
	void ObjectManager::TimeChangeBitmap(bool isDrak)
	{//시간의 경과에 따라 변화하는 Object의 Bitmap을 전환한다.
		//TIP::만약 오브젝트의 이름을 기존과 다르게 하면 if 문에 or로 추가하면 된다.

		for (int i = 0; i < mObject.find("Window")->second.size(); i++)
		{
			mObject.find("Window")->second[i]->TimeChangeBitmap(isDrak);
		}
	}
	
	void ObjectManager::Draw()
	{ //맵 인덱스 따라 그리도록

		for (int i = 0; i < mObject.find("Door")->second.size(); i++)
			mObject.find("Door")->second[i]->Draw();

		for (int i = 0; i < mObject.find("Window")->second.size(); i++)
			mObject.find("Window")->second[i]->Draw();

		for (int i = 0; i < mObject.find("Drawer")->second.size(); i++)
			mObject.find("Drawer")->second[i]->Draw();

		for (int i = 0; i < mObject.find("Flowerpot")->second.size(); i++)
			mObject.find("Flowerpot")->second[i]->Draw();

		for (int i = 0; i < mObject.find("Bed")->second.size(); i++)
			mObject.find("Bed")->second[i]->Draw();	

		for (int i = 0; i < mObject.find("Table_Vertical")->second.size(); i++)
			mObject.find("Table_Vertical")->second[i]->Draw();
		
		for (int i = 0; i < mObject.find("Shelf_Book")->second.size(); i++)
			mObject.find("Shelf_Book")->second[i]->Draw();	
		
		for (int i = 0; i < mObject.find("Curtain_Red")->second.size(); i++)
			mObject.find("Curtain_Red")->second[i]->Draw();	
		
		for (int i = 0; i < mObject.find("Table_Red")->second.size(); i++)
			mObject.find("Table_Red")->second[i]->Draw();

		for (int i = 0; i < mObject.find("Closet")->second.size(); i++)
			mObject.find("Closet")->second[i]->Draw();	
		



	}




	//void ObjectManager::Update(const FLOAT& deltaTime, const Clock m_Clock)
	void ObjectManager::Update(const FLOAT& deltaTime)
	{ //LATER::필요에 따라 Map별 업데이트 설정

		for (int i = 0; i < mObject.find("Door")->second.size(); i++)
			mObject.find("Door")->second[i]->Update(deltaTime);

		for (int i = 0; i < mObject.find("Window")->second.size(); i++)
			mObject.find("Window")->second[i]->Update(deltaTime);

		/*for (int i = 0; i < mObject.find("Drawer")->second.size(); i++)
			mObject.find("Drawer")->second[i]->Update(deltaTime);*/

		for (int i = 0; i < mObject.find("Flowerpot")->second.size(); i++)
			mObject.find("Flowerpot")->second[i]->Update(deltaTime);

/*		for (int i = 0; i < mObject.find("Bed")->second.size(); i++)
			mObject.find("Bed")->second[i]->Update(deltaTime);*/		
		
	/*	for (int i = 0; i < mObject.find("Shelf_Book")->second.size(); i++)
			mObject.find("Shelf_Book")->second[i]->Update(deltaTime);*/
			
		for (int i = 0; i < mObject.find("Curtain_Red")->second.size(); i++)
			mObject.find("Curtain_Red")->second[i]->Update(deltaTime);
	}

	void ObjectManager::SerachInterObject(std::vector<Object*> vObject, std::vector<Object*>* interObject, const RECT characterRect)
	{//vObject에는 현재 맵에 위치한 Object 한 종류가 들어있다.
		RECT objectRect;
		int eachObjectIndex;

		for (int i = 0; i < vObject.size(); i++)
		{
			eachObjectIndex = vObject[i]->GetEachObjectIndex().eachObjectIndex;

			//해당 맵에 배치된 Object 인지 판별 애초에 해당 맵의 Object만 가지고 있음
			objectRect = vObject[eachObjectIndex]->GetRect();

			//가로폭 영역이 겹치는지 확인
			if ((characterRect.right >= objectRect.left) && (objectRect.right >= characterRect.left))
				interObject->push_back(vObject[eachObjectIndex]);
		}
	}

/*	void ObjectManager::SerachInterObject(std::vector<Object*> vObject, std::vector<Object*>* interObject, const RECT characterRect)
	{
		RECT objectRect;
		EachObjectIndex eachObject_in_Map;

		
		//for (int i = 0; i < objectData.find(objectName)->second.objectCount; i++)
		for (int i = 0; i < vObject.size(); i++)
		{
			eachObject_in_Map = objectData.find(vObject[i]->GetObjectName())->second.eachObject[i].objectIndex;

			//해당 맵에 배치된 Object 인지 판별 애초에 해당 맵의 Object만 가지고 있음
			objectRect = vObject[eachObject_in_Map.eachObjectIndex]->GetRect();

			//가로폭 영역이 겹치는지 확인
			if ((characterRect.right >= objectRect.left) && (objectRect.right >= characterRect.left))
			{
				//interObject[count++] = new Object(objectData.find("Door")->second, i); //i는 파일내에서의 몇번째 오브젝트 사용인지 판단


				//TODO::맵 번호와 개별 인덱스 번호로 기존 Object들 백터에서 리턴해주는(얕은 복사) 함수 만들기.
				//interObject[interCount++] = *dynamic_cast<Object*>(door[eachObject_in_Map.objectIndex.eachObjectIndex]);
				//interObject[interCount] = *new Object();
				//interObject[interCount++] = *vObject[eachObject_in_Map.objectIndex.eachObjectIndex];
				//interObject[interCount] = *vObject[eachObject_in_Map.eachObjectIndex];

				interObject->push_back(vObject[eachObject_in_Map.eachObjectIndex]);
				//복사 생성자를 이용하여 깊은 복사. > 얕은 복사를 하면 복사되면서 Component의 소멸자가 자동 호출되어 renderer가 쓰레기 값이 된다.
				//interObject.push_back(Object(*vObject[eachObject_in_Map.eachObjectIndex]));
			}
		}
	}*/

	void ObjectManager::InteractiveCheck_toPlayer(std::vector<Object*>* interObject, const RECT characterRect)
	{ //현재 맵의 인덱스에 속하고 플레이어와 상호작용 가능한 모든 Object를 검사해야 한다.
		SerachInterObject(mObject.find("Door")->second, interObject, characterRect);
		SerachInterObject(mObject.find("Window")->second, interObject, characterRect);
		SerachInterObject(mObject.find("Drawer")->second, interObject, characterRect);
		SerachInterObject(mObject.find("Flowerpot")->second, interObject, characterRect);
		SerachInterObject(mObject.find("Bed")->second, interObject, characterRect);
		SerachInterObject(mObject.find("Curtain_Red")->second, interObject, characterRect);
		SerachInterObject(mObject.find("Closet")->second, interObject, characterRect);
	}


	void ObjectManager::FileRead(const std::string& file) {

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
	}
}