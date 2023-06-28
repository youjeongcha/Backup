#include "ObjectManager.h"

namespace ENGINE
{
	ObjectManager::ObjectManager()
	{
		LoadData();
		//door = new Door();
		//�� ��ü �����صΰ� �׸��� �׸��� �ʰ��
		door = new Door(objectData.find("Door")->second, 0);
		window = new Window(objectData.find("Window")->second, 0);
	}

	ObjectManager::~ObjectManager()
	{
		delete door;  // door �������� �޸� ����
	}

	void ObjectManager::LoadData()
	{
		FileRead("Door");
		FileRead("Window");
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
				tmpObjectData.name = line;

				// ��� Ÿ��
				std::getline(load, line);
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

					// ��� ���� �ε���
					objStream >> tmpEachObject.mapIndex;

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

	void ObjectManager::InitSetting()
	{
		//door = new Door();
	}

	void ObjectManager::ChangeActiveState()
	{
		//TODO::����, ����, �ݴ��� ����. ���� ���� �Ǵܵ� �ʿ��ϴ�.
		//00�� 00�ϴ�
		door->ChangeActiveState();
	}

	void ObjectManager::Draw()
	{ //TODO:: �� �ε��� ���� �׸����� ����
		door->Draw();
		window->Draw();
	}

	void ObjectManager::Update(const FLOAT& deltaTime)
	{
		door->Update(deltaTime);
		window->Update(deltaTime);
	}

	bool ObjectManager::InteractiveCheck_toPlayer(const RECT characterRect)
	{ //TODO::���� ���� �ε����� ���ϴ� ��� Object�� �˻��ؾ� �Ѵ�.
		LPRECT lprcDst = NULL;
		RECT objectRect = door->GetRect();

		if ((characterRect.right >= objectRect.left) && (objectRect.right >= characterRect.left))
			return true;

		objectRect = window->GetRect();
		if ((characterRect.right >= objectRect.left) && (objectRect.right >= characterRect.left))
			return true;

		//if (IntersectRect(lprcDst, &tmpRect, characterRect))
		//{
		//	return true;
		//}

		//tmpRect = window->GetRect();
		//if (IntersectRect(lprcDst, &tmpRect, characterRect))
		//{
		//	return true;
		//}

		return false;
	}

}