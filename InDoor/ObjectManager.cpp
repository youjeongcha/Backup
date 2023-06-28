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

	void ObjectManager::LoadData()
	{
		FileRead("Door");
		FileRead("Window");
	}


	void ObjectManager::FileRead(const std::string& file) {

		std::ifstream load("Data/" + file + ".txt");

		//오브젝트 객체 하나당 데이터 설정값
		ObjectData tmpObjectData; //하나의 가구 종류

		if (load.is_open()) {
			std::string line;

			// 읽어올 데이터가 있는지 확인
			if (std::getline(load, line)) {
				//이름
				tmpObjectData.name = line;

				// 사용 타입
				std::getline(load, line);
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


					tmpObjectData.eachObject = new EachObject(tmpEachObject);
				}
			}
			objectData.insert({ file, tmpObjectData }); //pair로 만들기
			load.close();
		}
	}

	void ObjectManager::InitSetting()
	{
		//door = new Door();
	}

	void ObjectManager::ChangeActiveState()
	{
		//TODO::낀다, 끈다, 닫다의 개념. 현재 상태 판단도 필요하다.
		//00을 00하다
		door->ChangeActiveState();
	}

	void ObjectManager::Draw()
	{ //TODO:: 맵 인덱스 따라 그리도록 수정
		door->Draw();
		window->Draw();
	}

	void ObjectManager::Update(const FLOAT& deltaTime)
	{
		door->Update(deltaTime);
		window->Update(deltaTime);
	}

	bool ObjectManager::InteractiveCheck_toPlayer(const RECT characterRect)
	{ //TODO::현재 맵의 인덱스에 속하는 모든 Object를 검사해야 한다.
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