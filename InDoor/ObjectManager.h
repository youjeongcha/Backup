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
		void LoadData();
		void FileRead(const std::string& file);

		//�ʱ� ���·� ����
		void InitSetting();
		void ChangeActiveState(); //Ȱ��ȭ ���� ��ȯ //TODO::����, ����, �ݴ��� ����. ���� ���� �Ǵܵ� �ʿ��ϴ�.

		void Draw();

		void Update(const FLOAT& deltaTime);
		//��ȣ�ۿ��� ������ object�� �ε����� ����
		bool InteractiveCheck_toPlayer(const RECT characterRect);

		friend Singleton;
	};
#define ObjectMgr ObjectManager::GetInstance()
}


