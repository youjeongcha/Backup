#pragma once
#include <fstream>
#include <sstream>
#include "Singleton.h"
#include "Door.h"
#include "Window.h"
#include "Drawer.h"
#include "Flowerpot.h"
#include "Bed.h"
#include "Shelf_Book.h"
#include "Table_Vertical.h"
#include "Curtain_Red.h"
#include "Closet.h"
#include "Table_Red.h"
#include "Bookcase.h"
#include "Stove.h"
#include "KitchenCounter.h"
#include "FirePot.h"
#include "Sideboard.h"
#include "WallHanging.h"
#include "WaterCup.h"
//#include "RoundTable.h"
//#include "WallHanging.h"






enum INTERACTIVE
{
	INTERACTIVE_MAX = 3
};



namespace ENGINE
{
	class ObjectManager : public Singleton<ObjectManager>
	{
	private:
		//SCENE mapIndex; //���� ���� � ������
		//���� Load ���� ������
		//std::map <std::string, ObjectData> objectData;
		//std::map <std::string, ObjectData> saveObjectData;

		//���� ��ü ����
		//std::map <EachObjectIndex, Object> map0_Objects;
		/*Door* door;
		Window* window;*/

		//����
		//std::vector<Object> object;
		std::map <std::string, std::vector<Object*>> mObject; //���� �ʿ� �ִ� Object���� ����

		//std::vector<Door*> door;
		//std::vector<Window*> window;
		//std::vector<Drawer*> drawer;
		//std::vector<Flowerpot*> flowerpot;


		ObjectManager();

	public:
		~ObjectManager();


		//�����
		//void Restrat();
		//map ����ɶ����� ��ü ���� �ٽ� �ϱ�
		void Delete_mObject();
		//void Delete_mObject(int _mapIndex);
		void InitSetting(int now_MapIndex, int change_MapIndex, bool isDrak);

		void Draw();
		void Update(const FLOAT& deltaTime);
		//��ȣ�ۿ��� ������ object�� �ε����� ����

		//int SerachInterObject(std::vector<Object*> vObject, Object* interObject, const RECT characterRect, int interCount); //Player�� ��ġ�� Object�� interObject�� ����(�� Object ����ȭ�� �Լ�ȭ)
		//vObject���� ���� �ʿ� ��ġ�� Object �� ������ ����ִ�.
		void SerachInterObject(std::vector<Object*> vObject, std::vector<Object*>* interObject, const RECT characterRect); //Player�� ��ġ�� Object�� interObject�� ����(�� Object ����ȭ�� �Լ�ȭ)
		//int InteractiveCheck_toPlayer(Object* interObject, const RECT characterRect); //�÷��̾�� ��ġ�� Obejct�� �����´�.(����)
		void InteractiveCheck_toPlayer(std::vector<Object*>* interObject, const RECT characterRect); //�÷��̾�� ��ġ�� Obejct�� �����´�.(����)


		//�ð��� �帧�� ���� ��ȭ�ϴ� Bitmap�� ��ȯ�Ѵ�. ex)â���� �̹���
		void TimeChangeBitmap(bool isDrak); //���� int ���ٸ� ex.�ٶ��� �Ҿ ��� �к��� ������.

		//EachObjectIndex* InteractiveCheck_toPlayer( const RECT characterRect);
		//bool InteractiveCheck_toPlayer(const RECT characterRect);

		friend Singleton;
	};
#define ObjectMgr ObjectManager::GetInstance()
}