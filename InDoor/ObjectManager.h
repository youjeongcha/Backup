#pragma once
#include <fstream>
#include <sstream>
#include "Singleton.h"
#include "Door.h"
#include "Window.h"

namespace ENGINE
{
	class ObjectManager : public Singleton<ObjectManager>
	{
	private:
		//가구 저장 데이터
		std::map <std::string, ObjectData> objectData;
		Door* door;
		Window* window;

		ObjectManager();

	public:
		~ObjectManager();

		//txt에서 정보 받아오기
		void LoadData();
		void FileRead(const std::string& file);

		//초기 상태로 세팅
		void InitSetting();
		void ChangeActiveState(); //활성화 상태 전환 //TODO::낀다, 끈다, 닫다의 개념. 현재 상태 판단도 필요하다.

		void Draw();

		void Update(const FLOAT& deltaTime);
		//상호작용이 가능한 object의 인덱스를 리턴
		bool InteractiveCheck_toPlayer(const RECT characterRect);

		friend Singleton;
	};
#define ObjectMgr ObjectManager::GetInstance()
}


