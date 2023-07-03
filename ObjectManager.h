#pragma once
#include <fstream>
#include <sstream>
#include "Singleton.h"
#include "Door.h"
#include "Window.h"

enum INTERACTIVE
{
	INTERACTIVE_MAX = 3
};

namespace ENGINE
{
	class ObjectManager : public Singleton<ObjectManager>
	{
	private:
		int mapIndex;
		//���� Load ���� ������
		std::map <std::string, ObjectData> objectData;

		//���� ��ü ����
		//std::map <EachObjectIndex, Object> map0_Objects;
		/*Door* door;
		Window* window;*/

		std::vector<Door*> door;
		std::vector<Window*> window;

		ObjectManager();

	public:
		~ObjectManager();

		//txt���� ���� �޾ƿ���
		void LoadData();
		void FileRead(const std::string& file);

		//map ����ɶ����� ��ü ���� �ٽ� �ϱ�
		void InitSetting(int _mapIndex);
		void Draw();
		void Update(const FLOAT& deltaTime);
		//��ȣ�ۿ��� ������ object�� �ε����� ����

		int InteractiveCheck_toPlayer(Object** objectIndexs, const RECT characterRect);
		void ChangeActiveState(Object** eachObjectindexs, int interactive_Count); //Ȱ��ȭ ���� ��ȯ //TODO::����, ����, �ݴ��� ����. ���� ���� �Ǵܵ� �ʿ��ϴ�.

		//EachObjectIndex* InteractiveCheck_toPlayer( const RECT characterRect);
		//bool InteractiveCheck_toPlayer(const RECT characterRect);

		friend Singleton;
	};
#define ObjectMgr ObjectManager::GetInstance()
}


