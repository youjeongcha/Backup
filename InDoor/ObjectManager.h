#pragma once
#include <fstream>
#include <sstream>
#include "Singleton.h"
#include "Door.h"
#include "Window.h"
#include "Drawer.h"
#include "Flowerpot.h"

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

		//����
		//std::vector<Object> object;
		std::map <std::string, std::vector<Object*>> mObject;

		//std::vector<Door*> door;
		//std::vector<Window*> window;
		//std::vector<Drawer*> drawer;
		//std::vector<Flowerpot*> flowerpot;


		ObjectManager();

	public:
		~ObjectManager();

		//txt���� ���� �޾ƿ���
		void LoadData();
		void FileRead(const std::string& file);
		//map ����ɶ����� ��ü ���� �ٽ� �ϱ�
		void Delete_mObject();
		void InitSetting(int _mapIndex);

		void Draw();
		void Update(const FLOAT& deltaTime);
		//��ȣ�ۿ��� ������ object�� �ε����� ����

		//int SerachInterObject(std::vector<Object*> vObject, Object* interObject, const RECT characterRect, int interCount); //Player�� ��ġ�� Object�� interObject�� ����(�� Object ����ȭ�� �Լ�ȭ)
		void SerachInterObject(std::vector<Object*> vObject, std::vector<Object>& interObject, const RECT characterRect); //Player�� ��ġ�� Object�� interObject�� ����(�� Object ����ȭ�� �Լ�ȭ)
		//int InteractiveCheck_toPlayer(Object* interObject, const RECT characterRect); //�÷��̾�� ��ġ�� Obejct�� �����´�.(����)
		void InteractiveCheck_toPlayer(std::vector<Object>& interObject, const RECT characterRect); //�÷��̾�� ��ġ�� Obejct�� �����´�.(����)


		//void ChangeActiveState(Object** eachObjectindexs, int interactive_Count); //Ȱ��ȭ ���� ��ȯ //TODO::����, ����, �ݴ��� ����. ���� ���� �Ǵܵ� �ʿ��ϴ�.
		void ChangeActiveState(Object eachObjectindexs); //���� int ���ٸ� ex.�ٶ��� �Ҿ ��� �к��� ������.

		//EachObjectIndex* InteractiveCheck_toPlayer( const RECT characterRect);
		//bool InteractiveCheck_toPlayer(const RECT characterRect);

		friend Singleton;
	};
#define ObjectMgr ObjectManager::GetInstance()
}


