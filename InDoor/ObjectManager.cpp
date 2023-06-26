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

	VOID ObjectManager::LoadData()
	{
		FileRead("Door");
		FileRead("Window");
	}


	VOID ObjectManager::FileRead(const std::string& file) {

		std::ifstream load("Data/" + file + ".txt");

		//������Ʈ ��ü �ϳ��� ������ ������
		ObjectData tmpObjectData; //�ϳ��� ���� ����

		if (load.is_open()) {
			std::string line;

			// �о�� �����Ͱ� �ִ��� Ȯ��
			if (std::getline(load, line)) {
				tmpObjectData.name = line;

				// ��� Ÿ��
				std::getline(load, line);
				std::istringstream typeStream(line);
				for (int i = 0; i < (int)OBJECT_TYPE::TYPE_COUNT; ++i) {
					typeStream >> tmpObjectData.typeCheck[(OBJECT_TYPE)i];
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
					objStream >> tmpEachObject.Available;
					objStream >> tmpEachObject.isMove;
					objStream >> tmpEachObject.isAnim;
					objStream >> tmpEachObject.isActive;
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


	/*
	VOID ObjectManager::FileRead(std::string file)
	{
		std::string test;
		std::ifstream load;

		//������Ʈ ��ü �ϳ��� ������ ������
		ObjectData tmpObjectData; //�ϳ��� ���� ����
		EachObject tmpEachObject; //���� �� ���� �ȿ��� ��ü�� ����

		load.open("Data/" + file + ".txt");
		if (load.is_open())
		{
			//��Ī
			load >> tmpObjectData.name;
			//��� Ÿ��
			load >> tmpObjectData.typeCheck[OBJECT_TYPE::NORMAL];
			load >> tmpObjectData.typeCheck[OBJECT_TYPE::MOVE];
			load >> tmpObjectData.typeCheck[OBJECT_TYPE::ANIM];
			load >> tmpObjectData.typeCheck[OBJECT_TYPE::ACTIVE];
			//���ø� �и� xy
			load >> tmpObjectData.spritesX;
			load >> tmpObjectData.spritesY;
			//�̹��� ����
			load >> tmpObjectData.fileName;
			//�Ѽ���
			load >> tmpObjectData.objectCount;

			//--������Ʈ ��ü �ϳ��� ������ ������---------

			for (int i = 0; i < tmpObjectData.objectCount; i++)
			{
				//��� ���� �ε���
				load >> tmpEachObject.mapIndex;
				//���� ����
				load >> tmpEachObject.Available;
				load >> tmpEachObject.isMove;
				load >> tmpEachObject.isAnim;
				load >> tmpEachObject.isActive;
				//��ǥ
				load >> tmpEachObject.x;
				load >> tmpEachObject.y;
				//��ġ �̵� ����(TODO::���� �ʿ�)
				load >> tmpEachObject.move_X;
				load >> tmpEachObject.move_Y;
				load >> tmpEachObject.move_Speed;

				tmpObjectData.eachObject = new EachObject(tmpEachObject);
			}

			objectData.insert({ file, tmpObjectData }); //pair�� �����
			load.close();
		}
	}*/

	void ObjectManager::InitSetting()
	{
		//door = new Door();
	}

	void ObjectManager::Draw()
	{//TODO:: �� �ε��� ���� �׸����� ����
		door->Draw();
		window->Draw();
	}

}