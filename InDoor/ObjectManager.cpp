#include "ObjectManager.h"
#include "DemoScene.h"
#include "GameManager.h"

namespace ENGINE
{
	ObjectManager::ObjectManager()
	{
	}

	ObjectManager::~ObjectManager()
	{
		Delete_mObject();
	}


	void ObjectManager::Delete_mObject()
	{
		for (Object* obj : mObject)
		{
			delete obj;
		}
		mObject.clear();
	}

	//void ObjectManager::InitSetting(int _mapIndex, bool isDrak)
	void ObjectManager::InitSetting(int now_MapIndex, int change_MapIndex, bool isDrak)
	{
		if (mObject.size())
			GameMgr-> RenewalSceneData((SCENE)now_MapIndex, mObject);

		//map 변경될때마다 객체 설정 다시 하기
		Delete_mObject();

		//해당 씬의 Object 데이터들 세팅
		mObject = GameMgr->ApplySceneData((SCENE)change_MapIndex);

		//해당 씬의 Object 비트맵 상태 설정(밤,낮)
		TimeChangeBitmap();
	}


	void ObjectManager::TimeChangeBitmap()
	{//시간의 경과에 따라 변화하는 Object의 Bitmap을 전환한다.
		//TIP::만약 오브젝트의 이름을 기존과 다르게 하면 if 문에 or로 추가하면 된다.

		for (auto object : mObject)
		{
			object->TimeChangeBitmap();
		}

		//for (int i = 0; i < mObject.find("Window")->second.size(); i++)
		//{
		//	mObject.find("Window")->second[i]->TimeChangeBitmap(isDrak);
		//}
	}
	
	void ObjectManager::Draw()
	{ //맵 인덱스 따라 그리도록

		for (auto object : mObject)
		{
			object->Draw();
		}

		//for (auto pair : mObject)
		//{
		//	for (auto object : pair.second)
		//	{
		//		object->Draw();
		//	}
		//}

		//for (int i = 0; i < mObject.find("Door")->second.size(); i++)
		//	mObject.find("Door")->second[i]->Draw();

		//for (int i = 0; i < mObject.find("Window")->second.size(); i++)
		//	mObject.find("Window")->second[i]->Draw();

		//for (int i = 0; i < mObject.find("Drawer")->second.size(); i++)
		//	mObject.find("Drawer")->second[i]->Draw();

		//for (int i = 0; i < mObject.find("Flowerpot")->second.size(); i++)
		//	mObject.find("Flowerpot")->second[i]->Draw();

		//for (int i = 0; i < mObject.find("Bed")->second.size(); i++)
		//	mObject.find("Bed")->second[i]->Draw();	

		//for (int i = 0; i < mObject.find("Table_Vertical")->second.size(); i++)
		//	mObject.find("Table_Vertical")->second[i]->Draw();
		//
		//for (int i = 0; i < mObject.find("Shelf_Book")->second.size(); i++)
		//	mObject.find("Shelf_Book")->second[i]->Draw();	
		//
		//for (int i = 0; i < mObject.find("Curtain_Red")->second.size(); i++)
		//	mObject.find("Curtain_Red")->second[i]->Draw();	
		//
		//for (int i = 0; i < mObject.find("Table_Red")->second.size(); i++)
		//	mObject.find("Table_Red")->second[i]->Draw();

		//for (int i = 0; i < mObject.find("Closet")->second.size(); i++)
		//	mObject.find("Closet")->second[i]->Draw();	

		//for (int i = 0; i < mObject.find("Bookcase")->second.size(); i++)
		//	mObject.find("Bookcase")->second[i]->Draw();	
		//		
		//for (int i = 0; i < mObject.find("Stove")->second.size(); i++)
		//	mObject.find("Stove")->second[i]->Draw();			
		//
		//for (int i = 0; i < mObject.find("KitchenCounter")->second.size(); i++)
		//	mObject.find("KitchenCounter")->second[i]->Draw();
		//
		//for (int i = 0; i < mObject.find("FirePot")->second.size(); i++)
		//	mObject.find("FirePot")->second[i]->Draw();			
		//
		//for (int i = 0; i < mObject.find("Sideboard")->second.size(); i++)
		//	mObject.find("Sideboard")->second[i]->Draw();
		//
		//for (int i = 0; i < mObject.find("WallHanging")->second.size(); i++)
		//	mObject.find("WallHanging")->second[i]->Draw();
		//
		//for (int i = 0; i < mObject.find("WaterCup")->second.size(); i++)
		//	mObject.find("WaterCup")->second[i]->Draw();	

		//for (int i = 0; i < mObject.find("OneCandle")->second.size(); i++)
		//	mObject.find("OneCandle")->second[i]->Draw();	


	}


	void ObjectManager::Animation(const FLOAT& deltaTime)
	{
		for (auto object : mObject)
		{
			object->Animation(deltaTime);
		}
		//for (int i = 0; i < mObject.find("OneCandle")->second.size(); i++)
		//	mObject.find("OneCandle")->second[i]->Animation(deltaTime);
	}



	/*
	//void ObjectManager::Update(const FLOAT& deltaTime, const Clock m_Clock)
	void ObjectManager::Update(const FLOAT& deltaTime)
	{ //LATER::필요에 따라 Map별 업데이트 설정

		for (int i = 0; i < mObject.find("Door")->second.size(); i++)
			mObject.find("Door")->second[i]->Update(deltaTime);

		for (int i = 0; i < mObject.find("Window")->second.size(); i++)
			mObject.find("Window")->second[i]->Update(deltaTime);

		/*for (int i = 0; i < mObject.find("Drawer")->second.size(); i++)
			mObject.find("Drawer")->second[i]->Update(deltaTime);

		for (int i = 0; i < mObject.find("Flowerpot")->second.size(); i++)
			mObject.find("Flowerpot")->second[i]->Update(deltaTime);

/*		for (int i = 0; i < mObject.find("Bed")->second.size(); i++)
			mObject.find("Bed")->second[i]->Update(deltaTime);	
		
	/*	for (int i = 0; i < mObject.find("Shelf_Book")->second.size(); i++)
			mObject.find("Shelf_Book")->second[i]->Update(deltaTime);
			
		for (int i = 0; i < mObject.find("Curtain_Red")->second.size(); i++)
			mObject.find("Curtain_Red")->second[i]->Update(deltaTime);
		
		for (int i = 0; i < mObject.find("Sideboard")->second.size(); i++)
			mObject.find("Sideboard")->second[i]->Update(deltaTime);
	}*/



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
		SerachInterObject(mObject, interObject, characterRect);


		/*SerachInterObject(mObject.find("Door")->second, interObject, characterRect);
		SerachInterObject(mObject.find("Window")->second, interObject, characterRect);
		SerachInterObject(mObject.find("Drawer")->second, interObject, characterRect);
		SerachInterObject(mObject.find("Flowerpot")->second, interObject, characterRect);
		SerachInterObject(mObject.find("Bed")->second, interObject, characterRect);
		SerachInterObject(mObject.find("Curtain_Red")->second, interObject, characterRect);
		SerachInterObject(mObject.find("Closet")->second, interObject, characterRect);
		SerachInterObject(mObject.find("Bookcase")->second, interObject, characterRect);
		SerachInterObject(mObject.find("Stove")->second, interObject, characterRect);
		SerachInterObject(mObject.find("Sideboard")->second, interObject, characterRect);
		SerachInterObject(mObject.find("WaterCup")->second, interObject, characterRect);
		SerachInterObject(mObject.find("OneCandle")->second, interObject, characterRect);*/
	}

	void ObjectManager::SerachInterObject(std::vector<Object*> vObject, std::vector<Object*>* interObject, const RECT characterRect)
	{//vObject에는 현재 맵에 위치한 Object 한 종류가 들어있다.
		RECT objectRect;
		//int eachObjectIndex;

		for (int i = 0; i < vObject.size(); i++)
		{
			//현재 사용중이어야지 플레이어와 겹치는지 확인하기 위해 //상호작용 가능한 Object인지 확인
			if (vObject[i]->GetisUse() && vObject[i]->IsInteractive())
			{
				//eachObjectIndex = vObject[i]->GetEachObjectIndex().eachObjectIndex;

				//해당 맵에 배치된 Object 인지 판별 애초에 해당 맵의 Object만 가지고 있음
				//objectRect = vObject[eachObjectIndex]->GetRect();
				objectRect = vObject[i]->GetRect();
				//가로폭 영역이 겹치는지 확인
				if ((characterRect.right >= objectRect.left) && (objectRect.right >= characterRect.left))
					interObject->push_back(vObject[i]);
			}
		}
	}
}