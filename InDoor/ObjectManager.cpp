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
		//map ����ɶ����� ��ü ���� �ٽ� �ϱ�
		Delete_mObject();

		//Door
		std::vector<Object*> tmpObject;
		for (int i = 0; i < objectData.find("Door")->second.objectCount; i++)
		{
			//�ش� �ʿ� ��ġ�� Object ���� �Ǻ�
			if (_mapIndex == objectData.find("Door")->second.eachObject[i]->objectIndex.mapIndex)
				tmpObject.push_back(new Door(objectData.find("Door")->second, i));
		}
		mObject.insert({ "Door", tmpObject }); //pair�� �����

		tmpObject.clear();

		//Window
		for (int i = 0; i < objectData.find("Window")->second.objectCount; i++)
		{
			//�ش� �ʿ� ��ġ�� Object ���� �Ǻ�
			if (_mapIndex == objectData.find("Window")->second.eachObject[i]->objectIndex.mapIndex)
				tmpObject.push_back(new Window(objectData.find("Window")->second, i));
		}
		mObject.insert({ "Window", tmpObject }); //pair�� �����

		tmpObject.clear();

		//Drawer
		for (int i = 0; i < objectData.find("Drawer")->second.objectCount; i++)
		{
			//�ش� �ʿ� ��ġ�� Object ���� �Ǻ�
			if (_mapIndex == objectData.find("Drawer")->second.eachObject[i]->objectIndex.mapIndex)
				tmpObject.push_back(new Drawer(objectData.find("Drawer")->second, i));
		}
		mObject.insert({ "Drawer", tmpObject }); //pair�� �����

		tmpObject.clear();


		//Flowerpot
		for (int i = 0; i < objectData.find("Flowerpot")->second.objectCount; i++)
		{
			//�ش� �ʿ� ��ġ�� Object ���� �Ǻ�
			if (_mapIndex == objectData.find("Flowerpot")->second.eachObject[i]->objectIndex.mapIndex)
				tmpObject.push_back(new Flowerpot(objectData.find("Flowerpot")->second, i));
		}
		mObject.insert({ "Flowerpot", tmpObject }); //pair�� �����

		tmpObject.clear();

		//Bed
		for (int i = 0; i < objectData.find("Bed")->second.objectCount; i++)
		{
			//�ش� �ʿ� ��ġ�� Object ���� �Ǻ�
			if (_mapIndex == objectData.find("Bed")->second.eachObject[i]->objectIndex.mapIndex)
				tmpObject.push_back(new Bed(objectData.find("Bed")->second, i));
		}
		mObject.insert({ "Bed", tmpObject }); //pair�� �����

		tmpObject.clear();		
		
		//Shelf_Book
		for (int i = 0; i < objectData.find("Shelf_Book")->second.objectCount; i++)
		{
			//�ش� �ʿ� ��ġ�� Object ���� �Ǻ�
			if (_mapIndex == objectData.find("Shelf_Book")->second.eachObject[i]->objectIndex.mapIndex)
				tmpObject.push_back(new Shelf_Book(objectData.find("Shelf_Book")->second, i));
		}
		mObject.insert({ "Shelf_Book", tmpObject }); //pair�� �����

		tmpObject.clear();

		//Table_Vertical
		for (int i = 0; i < objectData.find("Table_Vertical")->second.objectCount; i++)
		{
			//�ش� �ʿ� ��ġ�� Object ���� �Ǻ�
			if (_mapIndex == objectData.find("Table_Vertical")->second.eachObject[i]->objectIndex.mapIndex)
				tmpObject.push_back(new Table_Vertical(objectData.find("Table_Vertical")->second, i));
		}
		mObject.insert({ "Table_Vertical", tmpObject }); //pair�� �����

		tmpObject.clear();		
		
		//Curtain_Red
		for (int i = 0; i < objectData.find("Curtain_Red")->second.objectCount; i++)
		{
			//�ش� �ʿ� ��ġ�� Object ���� �Ǻ�
			if (_mapIndex == objectData.find("Curtain_Red")->second.eachObject[i]->objectIndex.mapIndex)
				tmpObject.push_back(new Curtain_Red(objectData.find("Curtain_Red")->second, i));
		}
		mObject.insert({ "Curtain_Red", tmpObject }); //pair�� �����

		tmpObject.clear();	
		
		//Closet
		for (int i = 0; i < objectData.find("Closet")->second.objectCount; i++)
		{
			//�ش� �ʿ� ��ġ�� Object ���� �Ǻ�
			if (_mapIndex == objectData.find("Closet")->second.eachObject[i]->objectIndex.mapIndex)
				tmpObject.push_back(new Closet(objectData.find("Closet")->second, i));
		}
		mObject.insert({ "Closet", tmpObject }); //pair�� �����

		tmpObject.clear();	
		
		//Table_Red
		for (int i = 0; i < objectData.find("Table_Red")->second.objectCount; i++)
		{
			//�ش� �ʿ� ��ġ�� Object ���� �Ǻ�
			if (_mapIndex == objectData.find("Table_Red")->second.eachObject[i]->objectIndex.mapIndex)
				tmpObject.push_back(new Table_Red(objectData.find("Table_Red")->second, i));
		}
		mObject.insert({ "Table_Red", tmpObject }); //pair�� �����

		tmpObject.clear();
	}


	
	void ObjectManager::TimeChangeBitmap(bool isDrak)
	{//�ð��� ����� ���� ��ȭ�ϴ� Object�� Bitmap�� ��ȯ�Ѵ�.
		//TIP::���� ������Ʈ�� �̸��� ������ �ٸ��� �ϸ� if ���� or�� �߰��ϸ� �ȴ�.

		for (int i = 0; i < mObject.find("Window")->second.size(); i++)
		{
			mObject.find("Window")->second[i]->TimeChangeBitmap(isDrak);
		}
	}
	
	void ObjectManager::Draw()
	{ //�� �ε��� ���� �׸�����

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
	{ //LATER::�ʿ信 ���� Map�� ������Ʈ ����

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
	{//vObject���� ���� �ʿ� ��ġ�� Object �� ������ ����ִ�.
		RECT objectRect;
		int eachObjectIndex;

		for (int i = 0; i < vObject.size(); i++)
		{
			eachObjectIndex = vObject[i]->GetEachObjectIndex().eachObjectIndex;

			//�ش� �ʿ� ��ġ�� Object ���� �Ǻ� ���ʿ� �ش� ���� Object�� ������ ����
			objectRect = vObject[eachObjectIndex]->GetRect();

			//������ ������ ��ġ���� Ȯ��
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

		//������Ʈ ��ü �ϳ��� ������ ������
		ObjectData tmpObjectData; //�ϳ��� ���� ����

		if (load.is_open()) {
			std::string line;

			// �о�� �����Ͱ� �ִ��� Ȯ��
			if (std::getline(load, line)) {
				//������Ʈ ��Ī(���ϸ�� ����)
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
	}
}