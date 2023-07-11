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





enum INTERACTIVE
{
	INTERACTIVE_MAX = 3
};



namespace ENGINE
{
	class ObjectManager : public Singleton<ObjectManager>
	{
	private:
		//SCENE mapIndex; //현재 맵이 어떤 맵인지
		//가구 Load 저장 데이터
		std::map <std::string, ObjectData> objectData;

		//가구 객체 보관
		//std::map <EachObjectIndex, Object> map0_Objects;
		/*Door* door;
		Window* window;*/

		//함축
		//std::vector<Object> object;
		std::map <std::string, std::vector<Object*>> mObject; //현재 맵에 있는 Object들의 모음

		//std::vector<Door*> door;
		//std::vector<Window*> window;
		//std::vector<Drawer*> drawer;
		//std::vector<Flowerpot*> flowerpot;


		ObjectManager();

	public:
		~ObjectManager();

		//txt에서 정보 받아오기
		void LoadData();
		void FileRead(const std::string& file);
		//map 변경될때마다 객체 설정 다시 하기
		void Delete_mObject();
		void InitSetting(int _mapIndex);

		void Draw();
		void Update(const FLOAT& deltaTime);
		//상호작용이 가능한 object의 인덱스를 리턴

		//int SerachInterObject(std::vector<Object*> vObject, Object* interObject, const RECT characterRect, int interCount); //Player와 겹치는 Object를 interObject에 저장(각 Object 세분화를 함수화)
		//vObject에는 현재 맵에 위치한 Object 한 종류가 들어있다.
		void SerachInterObject(std::vector<Object*> vObject, std::vector<Object*>* interObject, const RECT characterRect); //Player와 겹치는 Object를 interObject에 저장(각 Object 세분화를 함수화)
		//int InteractiveCheck_toPlayer(Object* interObject, const RECT characterRect); //플레이어와 겹치는 Obejct를 가져온다.(메인)
		void InteractiveCheck_toPlayer(std::vector<Object*>* interObject, const RECT characterRect); //플레이어와 겹치는 Obejct를 가져온다.(메인)


		//void ChangeActiveState(Object** eachObjectindexs, int interactive_Count); //활성화 상태 전환 //TODO::낀다, 끈다, 닫다의 개념. 현재 상태 판단도 필요하다.
		void ChangeActiveState(Object* selectObject); //굳이 int 쓴다면 ex.바람이 불어서 모든 촛불이 꺼진다.

		//EachObjectIndex* InteractiveCheck_toPlayer( const RECT characterRect);
		//bool InteractiveCheck_toPlayer(const RECT characterRect);

		friend Singleton;
	};
#define ObjectMgr ObjectManager::GetInstance()
}


