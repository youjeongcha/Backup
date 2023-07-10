#include "ObjectManager.h"

namespace ENGINE
{
	ObjectManager::ObjectManager()
	{
		LoadData();
		InitSetting(0);
	}

	ObjectManager::~ObjectManager()
	{
		Delete_mObject();

		//for (auto index : vObject)
		//{
		//	delete index;
		//}
		//vObject.clear(); // ��ü���� ������ �� ���͸� ���

		//for (auto index : window)
		//{
		//	delete index;
		//}
		//window.clear();
		//
		//for (auto index : drawer)
		//{
		//	delete index;
		//}
		//drawer.clear();
		//for (auto index : flowerpot)
		//{
		//	delete index;
		//}
		//flowerpot.clear();
	}

	void ObjectManager::LoadData()
	{
		FileRead("Door");
		FileRead("Window");
		FileRead("Drawer");
		FileRead("Flowerpot");
	}


	void ObjectManager::Delete_mObject()
	{
		if (mObject.size() > 0)
		{
			for (std::map<std::string, std::vector<Object*>>::iterator iter = mObject.begin(); iter != mObject.end(); iter++)
				delete& iter->second;
			mObject.clear();
		}
	}

	void ObjectManager::InitSetting(int _mapIndex)
	{
		mapIndex = _mapIndex;

		//Delete_mObject();

		//door.clear();
		//window.clear();
		//drawer.clear();
		//flowerpot.clear();

		//map ����ɶ����� ��ü ���� �ٽ� �ϱ�

		//Door
		std::vector<Object*> tmpObject;
		for (int i = 0; i < objectData.find("Door")->second.objectCount; i++)
		{
			//�ش� �ʿ� ��ġ�� Object ���� �Ǻ�
			if (mapIndex == objectData.find("Door")->second.eachObject[i].objectIndex.mapIndex)
			{
				tmpObject.push_back(new Door(objectData.find("Door")->second, i));
				//mObject.insert({"Door", new Door(objectData.find("Door")->second, i)}); //pair�� �����
			}
		}
		mObject.insert({ "Door", tmpObject }); //pair�� �����

		tmpObject.clear();

		//Window
		for (int i = 0; i < objectData.find("Window")->second.objectCount; i++)
		{
			//�ش� �ʿ� ��ġ�� Object ���� �Ǻ�
			if (mapIndex == objectData.find("Window")->second.eachObject[i].objectIndex.mapIndex)
			{
				tmpObject.push_back(new Window(objectData.find("Window")->second, i));
				//mObject.insert({"Door", new Door(objectData.find("Door")->second, i)}); //pair�� �����
			}
		}
		mObject.insert({ "Window", tmpObject }); //pair�� �����

		tmpObject.clear();

		//Drawer
		for (int i = 0; i < objectData.find("Drawer")->second.objectCount; i++)
		{
			//�ش� �ʿ� ��ġ�� Object ���� �Ǻ�
			if (mapIndex == objectData.find("Drawer")->second.eachObject[i].objectIndex.mapIndex)
			{
				tmpObject.push_back(new Drawer(objectData.find("Drawer")->second, i));
				//mObject.insert({"Door", new Door(objectData.find("Door")->second, i)}); //pair�� �����
			}
		}
		mObject.insert({ "Drawer", tmpObject }); //pair�� �����

		tmpObject.clear();


		//Flowerpot
		for (int i = 0; i < objectData.find("Flowerpot")->second.objectCount; i++)
		{
			//�ش� �ʿ� ��ġ�� Object ���� �Ǻ�
			if (mapIndex == objectData.find("Flowerpot")->second.eachObject[i].objectIndex.mapIndex)
			{
				tmpObject.push_back(new Flowerpot(objectData.find("Flowerpot")->second, i));
				//mObject.insert({"Door", new Door(objectData.find("Door")->second, i)}); //pair�� �����
			}
		}
		mObject.insert({ "Flowerpot", tmpObject }); //pair�� �����

		tmpObject.clear();


		//for (int i = 0; i < objectData.find("Door")->second.objectCount; i++)
		//{
		//	//�ش� �ʿ� ��ġ�� Object ���� �Ǻ�
		//	if (mapIndex == objectData.find("Door")->second.eachObject[i].objectIndex.mapIndex)
		//	{
		//		mObject.push_back(new Door(objectData.find("Door")->second, i));
		//	}
		//}
		//for (int i = 0; i < objectData.find("Window")->second.objectCount; i++)
		//{
		//	if (mapIndex == objectData.find("Window")->second.eachObject[i].objectIndex.mapIndex)
		//	{
		//		window.push_back(new Window(objectData.find("Window")->second, i));
		//	}
		//}
		//for (int i = 0; i < objectData.find("Drawer")->second.objectCount; i++)
		//{
		//	if (mapIndex == objectData.find("Drawer")->second.eachObject[i].objectIndex.mapIndex)
		//	{
		//		drawer.push_back(new Drawer(objectData.find("Drawer")->second, i));
		//	}
		//}
		//for (int i = 0; i < objectData.find("Flowerpot")->second.objectCount; i++)
		//{
		//	if (mapIndex == objectData.find("Flowerpot")->second.eachObject[i].objectIndex.mapIndex)
		//	{
		//		flowerpot.push_back(new Flowerpot(objectData.find("Flowerpot")->second, i));
		//	}
		//}
		//window = new Window(objectData.find("Window")->second, 0);
	}



	//void ObjectManager::ChangeActiveState(Object** eachObjectindexs, int interactive_Count)
	void ObjectManager::ChangeActiveState(Object* selectObject)
	{
		EachObjectIndex select = selectObject->GetEachObjectIndex();
		//TODO::�ش� ������Ʈ�� ���� �����ϰ�
		//TODO::����, ����, �ݴ��� ����. ���� ���� �Ǵܵ� �ʿ��ϴ�.
		//00�� 00�ϴ�
		//for (int i = 0; i < interactive_Count; i++)
		//{
		if (select.name == "��")
		{
			//�ش� Object �̸�
			if (select.eachObjectIndex == objectData.find("Door")->second.eachObject->objectIndex.eachObjectIndex)
				mObject.find("Door")->second[select.eachObjectIndex]->ChangeActiveState(); //door�� window���� <���� ��>�� �ִ� ������Ʈ�� ī��Ʈ �Ѵ�.
		}
		else if (select.name == "â��")
		{
			if (select.eachObjectIndex == objectData.find("Window")->second.eachObject->objectIndex.eachObjectIndex)
				mObject.find("Window")->second[select.eachObjectIndex]->ChangeActiveState();
		}
		else if (select.name == "����")
		{
			if (select.eachObjectIndex == objectData.find("Drawer")->second.eachObject->objectIndex.eachObjectIndex)
				mObject.find("Drawer")->second[select.eachObjectIndex]->ChangeActiveState();
		}
		else if (select.name == "ȭ��")
		{
			if (select.eachObjectIndex == objectData.find("Flowerpot")->second.eachObject->objectIndex.eachObjectIndex)
				mObject.find("Flowerpot")->second[select.eachObjectIndex]->ChangeActiveState();
		}
	}

	void ObjectManager::Draw()
	{//�� �ε��� ���� �׸�����

		for (int i = 0; i < mObject.find("Door")->second.size(); i++)
			mObject.find("Door")->second[i]->Draw();

		for (int i = 0; i < mObject.find("Window")->second.size(); i++)
			mObject.find("Window")->second[i]->Draw();

		for (int i = 0; i < mObject.find("Drawer")->second.size(); i++)
			mObject.find("Drawer")->second[i]->Draw();

		for (int i = 0; i < mObject.find("Flowerpot")->second.size(); i++)
			mObject.find("Flowerpot")->second[i]->Draw();

		//for (auto index : door)
		//{
		//	index.Draw();
		//}
		//for (auto index : window)
		//{
		//	index.Draw();
		//}
		/*for (int i = 0;i < door.size(); i++)
		{
			door[i]->Draw();
		}
		for (int i = 0;i < window.size(); i++)
		{
			window[i]->Draw();
		}
		for (int i = 0;i < drawer.size(); i++)
		{
			drawer[i]->Draw();
		}
		for (int i = 0;i < flowerpot.size(); i++)
		{
			flowerpot[i]->Draw();
		}*/
		//TODO::�ش� ���� object count�� �˾ƾ� �Ѵ�.
		//for (int i = 0; i < objectData.find("Door")->second.objectCount; i++)
		//{
		//	door[i].Draw();
		//}
		//for (int i = 0; i < objectData.find("Window")->second.objectCount; i++)
		//{
		//	window[i].Draw();
		//}
	}




	void ObjectManager::Update(const FLOAT& deltaTime)
	{//LATER::�ʿ信 ���� Map�� ������Ʈ ����

		for (int i = 0; i < mObject.find("Door")->second.size(); i++)
			mObject.find("Door")->second[i]->Update(deltaTime);

		for (int i = 0; i < mObject.find("Window")->second.size(); i++)
			mObject.find("Window")->second[i]->Update(deltaTime);

		for (int i = 0; i < mObject.find("Drawer")->second.size(); i++)
			mObject.find("Drawer")->second[i]->Update(deltaTime);

		for (int i = 0; i < mObject.find("Flowerpot")->second.size(); i++)
			mObject.find("Flowerpot")->second[i]->Update(deltaTime);

		/*
		for (int i = 0;i < door.size(); i++)
		{
			door[i]->Update(deltaTime);
		}
		for (int i = 0;i < window.size(); i++)
		{
			window[i]->Update(deltaTime);
		}
		for (int i = 0;i < drawer.size(); i++)
		{
			drawer[i]->Update(deltaTime);
		}
		for (int i = 0;i < flowerpot.size(); i++)
		{
			flowerpot[i]->Update(deltaTime);
		}*/
	}

	void ObjectManager::SerachInterObject(std::vector<Object*> vObject, std::vector<Object*>* interObject, const RECT characterRect)
	{
		RECT objectRect;
		EachObjectIndex eachObject_in_Map;

		//for (int i = 0; i < objectData.find(objectName)->second.objectCount; i++)
		for (int i = 0; i < vObject.size(); i++)
		{
			eachObject_in_Map = objectData.find(vObject[i]->GetObjectName())->second.eachObject[i].objectIndex;

			//�ش� �ʿ� ��ġ�� Object ���� �Ǻ�
			if (mapIndex == eachObject_in_Map.mapIndex)
			{
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
		}
		//return interObject;
	}

	void ObjectManager::InteractiveCheck_toPlayer(std::vector<Object*>* interObject, const RECT characterRect)
	{ //���� ���� �ε����� ���ϴ� ��� Object�� �˻��ؾ� �Ѵ�.
		//int interCount = 0;

		SerachInterObject(mObject.find("Door")->second, interObject, characterRect);
		SerachInterObject(mObject.find("Window")->second, interObject, characterRect);
		SerachInterObject(mObject.find("Drawer")->second, interObject, characterRect);
		SerachInterObject(mObject.find("Flowerpot")->second, interObject, characterRect);
		
		//return interCount;
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
				for (int i = 0; i < tmpObjectData.objectCount; ++i) {
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


					tmpObjectData.eachObject = new EachObject(tmpEachObject);
				}
			}
			objectData.insert({ file, tmpObjectData }); //pair�� �����
			load.close();
		}
	}
}