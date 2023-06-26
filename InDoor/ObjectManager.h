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
		//���� ���� ������
		std::map <std::string, ObjectData> objectData;
		Door* door;
		Window* window;

		ObjectManager();

	public:
		~ObjectManager();

		//txt���� ���� �޾ƿ���
		VOID LoadData();
		VOID FileRead(const std::string& file);

		//�ʱ� ���·� ����
		void InitSetting();
		void Draw();
		friend Singleton;
	};
#define ObjectMgr ObjectManager::GetInstance()
}


