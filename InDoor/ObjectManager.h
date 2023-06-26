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
		VOID LoadData();
		VOID FileRead(const std::string& file);

		//초기 상태로 세팅
		void InitSetting();
		void Draw();
		friend Singleton;
	};
#define ObjectMgr ObjectManager::GetInstance()
}


