#include "ObjectManager.h"

namespace ENGINE
{
	ObjectManager::ObjectManager()
	{
		LoadData();
		//door = new Door();
		//다 객체 생성해두고 그리고 그리지 않고로
		door = new Door(objectData.find("Door")->second, 0);
		window = new Window(objectData.find("Window")->second, 0);
	}

	ObjectManager::~ObjectManager()
	{
		delete door;  // door 포인터의 메모리 정리
	}

	VOID ObjectManager::LoadData()
	{
		FileRead("Door");
		FileRead("Window");
	}


	VOID ObjectManager::FileRead(const std::string& file) {

		std::ifstream load("Data/" + file + ".txt");

		//오브젝트 객체 하나당 데이터 설정값
		ObjectData tmpObjectData; //하나의 가구 종류

		if (load.is_open()) {
			std::string line;

			// 읽어올 데이터가 있는지 확인
			if (std::getline(load, line)) {
				tmpObjectData.name = line;

				// 사용 타입
				std::getline(load, line);
				std::istringstream typeStream(line);
				for (int i = 0; i < (int)OBJECT_TYPE::TYPE_COUNT; ++i) {
					typeStream >> tmpObjectData.typeCheck[(OBJECT_TYPE)i];
				}

				// 스플릿 분리 xy
				std::getline(load, line);
				std::istringstream splitStream(line);
				splitStream >> tmpObjectData.spritesX;
				splitStream >> tmpObjectData.spritesY;

				// 이미지 파일
				std::getline(load, line);
				tmpObjectData.fileName = line;

				// 총 수량
				std::getline(load, line);
				std::istringstream countStream(line);
				countStream >> tmpObjectData.objectCount;

				// 오브젝트 객체 하나당 데이터 설정값
				for (int i = 0; i < tmpObjectData.objectCount; ++i) {
					std::getline(load, line);
					std::istringstream objStream(line);
					EachObject tmpEachObject; //가구 한 종류 안에서 객체들 관리

					// 사용 맵의 인덱스
					objStream >> tmpEachObject.mapIndex;
					// 현재 상태
					objStream >> tmpEachObject.Available;
					objStream >> tmpEachObject.isMove;
					objStream >> tmpEachObject.isAnim;
					objStream >> tmpEachObject.isActive;
					// 좌표
					objStream >> tmpEachObject.x;
					objStream >> tmpEachObject.y;
					// 위치 이동 정도
					objStream >> tmpEachObject.move_X;
					objStream >> tmpEachObject.move_Y;
					objStream >> tmpEachObject.move_Speed;


					tmpObjectData.eachObject = new EachObject(tmpEachObject);
				}
			}
			objectData.insert({ file, tmpObjectData }); //pair로 만들기
			load.close();
		}
	}


	/*
	VOID ObjectManager::FileRead(std::string file)
	{
		std::string test;
		std::ifstream load;

		//오브젝트 객체 하나당 데이터 설정값
		ObjectData tmpObjectData; //하나의 가구 종류
		EachObject tmpEachObject; //가구 한 종류 안에서 객체들 관리

		load.open("Data/" + file + ".txt");
		if (load.is_open())
		{
			//명칭
			load >> tmpObjectData.name;
			//사용 타입
			load >> tmpObjectData.typeCheck[OBJECT_TYPE::NORMAL];
			load >> tmpObjectData.typeCheck[OBJECT_TYPE::MOVE];
			load >> tmpObjectData.typeCheck[OBJECT_TYPE::ANIM];
			load >> tmpObjectData.typeCheck[OBJECT_TYPE::ACTIVE];
			//스플릿 분리 xy
			load >> tmpObjectData.spritesX;
			load >> tmpObjectData.spritesY;
			//이미지 파일
			load >> tmpObjectData.fileName;
			//총수량
			load >> tmpObjectData.objectCount;

			//--오브젝트 객체 하나당 데이터 설정값---------

			for (int i = 0; i < tmpObjectData.objectCount; i++)
			{
				//사용 맵의 인덱스
				load >> tmpEachObject.mapIndex;
				//현재 상태
				load >> tmpEachObject.Available;
				load >> tmpEachObject.isMove;
				load >> tmpEachObject.isAnim;
				load >> tmpEachObject.isActive;
				//좌표
				load >> tmpEachObject.x;
				load >> tmpEachObject.y;
				//위치 이동 정도(TODO::수정 필요)
				load >> tmpEachObject.move_X;
				load >> tmpEachObject.move_Y;
				load >> tmpEachObject.move_Speed;

				tmpObjectData.eachObject = new EachObject(tmpEachObject);
			}

			objectData.insert({ file, tmpObjectData }); //pair로 만들기
			load.close();
		}
	}*/

	void ObjectManager::InitSetting()
	{
		//door = new Door();
	}

	void ObjectManager::Draw()
	{//TODO:: 맵 인덱스 따라 그리도록 수정
		door->Draw();
		window->Draw();
	}

}