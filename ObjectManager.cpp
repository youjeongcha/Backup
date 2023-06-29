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

		//map 변경될때마다 객체 설정 다시 하기
		for (int i = 0; i < objectData.find("Door")->second.objectCount; i++)
		{
			//해당 맵에 배치된 Object 인지 판별
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
		//TODO::해당 오브젝트만 수정 가능하게
		//TODO::낀다, 끈다, 닫다의 개념. 현재 상태 판단도 필요하다.
		//00을 00하다
		for (int i = 0; i < interactive_Count; i++)
		{
			if (eachObjectindexs[i].name == "문")
			{
				//해당 Object 이면
				if (eachObjectindexs[i].eachObjectIndex == objectData.find("Door")->second.eachObject[i].obejctIndex.eachObjectIndex)
					door[i]->ChangeActiveState();
			}
			else if (eachObjectindexs[i].name == "창문")
			{
				if (eachObjectindexs[i].eachObjectIndex == objectData.find("Window")->second.eachObject[i].obejctIndex.eachObjectIndex)
					window[i]->ChangeActiveState();
			}
		}
	}

	void ObjectManager::Draw()
	{//맵 인덱스 따라 그리도록
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
		//TODO::해당 맵의 object count를 알아야 한다.
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
	{//LATER::필요에 따라 Map별 업데이트 설정

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
	{ //TODO::현재 맵의 인덱스에 속하는 모든 Object를 검사해야 한다.
		LPRECT lprcDst = NULL;
		EachObjectIndex* interactArray[INTERACTIVE_MAX] = { nullptr };
		RECT objectRect;
		int count = 0;


		for (int i = 0; i < objectData.find("Door")->second.objectCount; i++)
		{
			//해당 맵에 배치된 Object 인지 판별
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
		

		// 동적으로 메모리를 할당하여 배열을 생성
		*objectIndexs = new EachObjectIndex[INTERACTIVE_MAX];
		// interactArray의 값을 resultArray로 복사
		for (int i = 0; i < count; i++)
		{
			*objectIndexs[i] = *interactArray[i];
		}
		//EachObjectIndex* resultArray = new EachObjectIndex[INTERACTIVE_MAX];
		//// interactArray의 값을 resultArray로 복사
		//for (int i = 0; i < count; i++)
		//{
		//	resultArray[i] = *interactArray[i];
		//}


		return count;
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
				//tmpObjectData.eachObject->obejctIndex.name = line;

				// 사용 타입
				//std::getline(load, line);
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

					//이름
					objStream >> tmpEachObject.obejctIndex.name;

					// 사용 맵의 인덱스
					objStream >> tmpEachObject.obejctIndex.mapIndex;

					objStream >> tmpEachObject.obejctIndex.eachObjectIndex;

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
}