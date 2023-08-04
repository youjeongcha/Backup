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

		//map ����ɶ����� ��ü ���� �ٽ� �ϱ�
		Delete_mObject();

		//�ش� ���� Object �����͵� ����
		mObject = GameMgr->ApplySceneData((SCENE)change_MapIndex);

		//�ش� ���� Object ��Ʈ�� ���� ����(��,��)
		TimeChangeBitmap();
	}


	void ObjectManager::TimeChangeBitmap()
	{//�ð��� ����� ���� ��ȭ�ϴ� Object�� Bitmap�� ��ȯ�Ѵ�.
		//TIP::���� ������Ʈ�� �̸��� ������ �ٸ��� �ϸ� if ���� or�� �߰��ϸ� �ȴ�.

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
	{ //�� �ε��� ���� �׸�����

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
	{ //LATER::�ʿ信 ���� Map�� ������Ʈ ����

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

			//�ش� �ʿ� ��ġ�� Object ���� �Ǻ� ���ʿ� �ش� ���� Object�� ������ ����
			objectRect = vObject[eachObject_in_Map.eachObjectIndex]->GetRect();

			//������ ������ ��ġ���� Ȯ��
			if ((characterRect.right >= objectRect.left) && (objectRect.right >= characterRect.left))
			{
				//interObject[count++] = new Object(objectData.find("Door")->second, i); //i�� ���ϳ������� ���° ������Ʈ ������� �Ǵ�


				//TODO::�� ��ȣ�� ���� �ε��� ��ȣ�� ���� Object�� ���Ϳ��� �������ִ�(���� ����) �Լ� �����.
				//interObject[interCount++] = *dynamic_cast<Object*>(door[eachObject_in_Map.objectIndex.eachObjectIndex]);
				//interObject[interCount] = *new Object();
				//interObject[interCount++] = *vObject[eachObject_in_Map.objectIndex.eachObjectIndex];
				//interObject[interCount] = *vObject[eachObject_in_Map.eachObjectIndex];

				interObject->push_back(vObject[eachObject_in_Map.eachObjectIndex]);
				//���� �����ڸ� �̿��Ͽ� ���� ����. > ���� ���縦 �ϸ� ����Ǹ鼭 Component�� �Ҹ��ڰ� �ڵ� ȣ��Ǿ� renderer�� ������ ���� �ȴ�.
				//interObject.push_back(Object(*vObject[eachObject_in_Map.eachObjectIndex]));
			}
		}
	}*/

	void ObjectManager::InteractiveCheck_toPlayer(std::vector<Object*>* interObject, const RECT characterRect)
	{ //���� ���� �ε����� ���ϰ� �÷��̾�� ��ȣ�ۿ� ������ ��� Object�� �˻��ؾ� �Ѵ�.
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
	{//vObject���� ���� �ʿ� ��ġ�� Object �� ������ ����ִ�.
		RECT objectRect;
		//int eachObjectIndex;

		for (int i = 0; i < vObject.size(); i++)
		{
			//���� ������̾���� �÷��̾�� ��ġ���� Ȯ���ϱ� ���� //��ȣ�ۿ� ������ Object���� Ȯ��
			if (vObject[i]->GetisUse() && vObject[i]->IsInteractive())
			{
				//eachObjectIndex = vObject[i]->GetEachObjectIndex().eachObjectIndex;

				//�ش� �ʿ� ��ġ�� Object ���� �Ǻ� ���ʿ� �ش� ���� Object�� ������ ����
				//objectRect = vObject[eachObjectIndex]->GetRect();
				objectRect = vObject[i]->GetRect();
				//������ ������ ��ġ���� Ȯ��
				if ((characterRect.right >= objectRect.left) && (objectRect.right >= characterRect.left))
					interObject->push_back(vObject[i]);
			}
		}
	}
}