#pragma once
#include "Singleton.h"
#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H


//SceneManager 클래스의 생성자가 private이기 때문에 Singleton class를 friend로 만들어준다.
//TimeManager 적용

namespace ENGINE
{
	class SceneManager : public Singleton<SceneManager>
	{
	private:
		HWND hWnd;
		HDC hDC, hBackDC;
		UINT32 width, height;

		Scene* currScene;
		std::string nextScene; //?
		std::map<std::string, Scene*> scenes; //?

		SceneManager() : hWnd(NULL), hDC(NULL), hBackDC(NULL), width(0), height(0), currScene(NULL) {}
	public:
		~SceneManager();
		void Initialize(HWND hWnd, UINT32 width, UINT32 height);
		void Release();
		void Render();

		bool RegisterScene(LPCSTR sceneName, Scene* scene); //Scene을 등록.
		bool LoadScene(LPCSTR scenenName); //불러 올 Scene을 설정.

		UINT32 GetWidth() const { return width; } //윈도우의 클라이언트 너비.
		UINT32 GetHeight() const { return height; } //윈도우의 클라이언트 높이.
		HWND GetHWND() const { return hWnd; }
		HDC GetBackDC() const { return hBackDC; }
	private:
		void SetScene(); //등록된 Scene을 적용
		void Update();
		void Draw();
		HBITMAP CreateDIBSectionRe(); //Back Bitmap을 만들기 위한 비트맵 Creater

		friend Singleton;
	}; //class SceneManager
#define SceneMgr SceneManager::GetInstance()
} //namespace ENGINE

#endif // !SCENE_MANAGER_H