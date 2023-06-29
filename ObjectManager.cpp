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
		for (auto index : door)
		{
			delete index;
		}
		for (auto index : window)
		{
			delete index;
		}
	}

	void ObjectManager::LoadData()
	{
		FileRead("Door");
		FileRead("Window");
	}


	void ObjectManager::InitSetting(int _mapIndex)
	{
		mapIndex = _mapIndex;

		door.clear();
		window.clear();

		//map ����ɶ����� ��ü ���� �ٽ� �ϱ�
		for (int i = 0; i < objectData.find("Door")->second.objectCount; i++)
		{
			//�ش� �ʿ� ��ġ�� Object ���� �Ǻ�
			if (mapIndex == objectData.find("Door")->second.eachObject[i].obejctIndex.mapIndex)
			{
				door.push_back(new Door(objectData.find("Door")->second, i));
			}
		}
		for (int i = 0; i < objectData.find("Window")->second.objectCount; i++)
		{
			if (mapIndex == objectData.find("Window")->second.eachObject[i].obejctIndex.mapIndex)
			{
				window.push_back(new Window(objectData.find("Window")->second, i));
			}
		}
		//window = new Window(objectData.find("Window")->second, 0);
	}

	void ObjectManager::ChangeActiveState(EachObjectIndex* eachObjectindexs, int interactive_Count)
	{
		//TODO::�ش� ������Ʈ�� ���� �����ϰ�
		//TODO::����, ����, �ݴ��� ����. ���� ���� �Ǵܵ� �ʿ��ϴ�.
		//00�� 00�ϴ�
		for (int i = 0; i < interactive_Count; i++)
		{
			if (eachObjectindexs[i].name == "��")
			{
				//�ش� Object �̸�
				if (eachObjectindexs[i].eachObjectIndex == objectData.find("Door")->second.eachObject[i].obejctIndex.eachObjectIndex)
					door[i]->ChangeActiveState();
			}
			else if (eachObjectindexs[i].name == "â��")
			{
				if (eachObjectindexs[i].eachObjectIndex == objectData.find("Window")->second.eachObject[i].obejctIndex.eachObjectIndex)
					window[i]->ChangeActiveState();
			}
		}
	}

	void ObjectManager::Draw()
	{//�� �ε��� ���� �׸�����
		//for (auto index : door)
		//{
		//	index.Draw();
		//}
		//for (auto index : window)
		//{
		//	index.Draw();
		//}
		for (int i = 0;i < door.size(); i++)
		{
			door[i]->Draw();
		}
		for (int i = 0;i < window.size(); i++)
		{
			window[i]->Draw();
		}
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

		for (int i = 0;i < door.size(); i++)
		{
			door[i]->Update(deltaTime);
		}
		for (int i = 0;i < window.size(); i++)
		{
			window[i]->Update(deltaTime);
		}
		//for (auto index : door)
		//{
		//	index.Update(deltaTime);
		//}
		//for (auto index : window)
		//{
		//	index.Update(deltaTime);
		//}
	}

	int ObjectManager::InteractiveCheck_toPlayer(EachObjectIndex** objectIndexs, const RECT characterRect)
	{ //TODO::���� ���� �ε����� ���ϴ� ��� Object�� �˻��ؾ� �Ѵ�.
		LPRECT lprcDst = NULL;
		EachObjectIndex* interactArray[INTERACTIVE_MAX] = { nullptr };
		RECT objectRect;
		int count = 0;


		for (int i = 0; i < objectData.find("Door")->second.objectCount; i++)
		{
			//�ش� �ʿ� ��ġ�� Object ���� �Ǻ�
			if (mapIndex == objectData.find("Door")->second.eachObject[i].obejctIndex.mapIndex)
			{
				objectRect = door[i]->GetRect();


				if ((characterRect.right >= objectRect.left) && (objectRect.right >= characterRect.left))
				{
					count++;
					interactArray[i] = &objectData.find("Door")->second.eachObject[i].obejctIndex;
				}
			}
		}

		for (int i = 0; i < objectData.find("Window")->second.objectCount; i++)
		{
			if (mapIndex == objectData.find("Window")->second.eachObject[i].obejctIndex.mapIndex)
			{
				objectRect = window[i]->GetRect();

				if ((characterRect.right >= objectRect.left) && (objectRect.right >= characterRect.left))
				{
					count++;
					interactArray[i] = &objectData.find("Window")->second.eachObject[i].obejctIndex;
				}
			}
		}
		

		// �������� �޸𸮸� �Ҵ��Ͽ� �迭�� ����
		*objectIndexs = new EachObjectIndex[INTERACTIVE_MAX];
		// interactArray�� ���� resultArray�� ����
		for (int i = 0; i < count; i++)
		{
			*objectIndexs[i] = *interactArray[i];
		}
		//EachObjectIndex* resultArray = new EachObjectIndex[INTERACTIVE_MAX];
		//// interactArray�� ���� resultArray�� ����
		//for (int i = 0; i < count; i++)
		//{
		//	resultArray[i] = *interactArray[i];
		//}


		return count;
	}


	void ObjectManager::FileRead(const std::string& file) {

		std::ifstream load("Data/" + file + ".txt");

		//������Ʈ ��ü �ϳ��� ������ ������
		ObjectData tmpObjectData; //�ϳ��� ���� ����

		if (load.is_open()) {
			std::string line;

			// �о�� �����Ͱ� �ִ��� Ȯ��
			if (std::getline(load, line)) {
				//�̸�
				//tmpObjectData.eachObject->obejctIndex.name = line;

				// ��� Ÿ��
				//std::getline(load, line);
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
					objStream >> tmpEachObject.obejctIndex.name;

					// ��� ���� �ε���
					objStream >> tmpEachObject.obejctIndex.mapIndex;

					objStream >> tmpEachObject.obejctIndex.eachObjectIndex;

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