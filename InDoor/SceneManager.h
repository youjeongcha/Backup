#pragma once
#include "Singleton.h"
#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H


//SceneManager Ŭ������ �����ڰ� private�̱� ������ Singleton class�� friend�� ������ش�.
//TimeManager ����

namespace ENGINE
{
	class SceneManager : public Singleton<SceneManager>
	{
	private:
		HWND hWnd;
		HDC hDC, hBackDC;
		UINT32 width, height;

		Scene* currScene;
		std::string nextScene; //key ������ ����ϰ� �ִ�.
		std::map<std::string, Scene*> scenes; //key ���� scene���� �����ϰ� �ִ�.

		SceneManager() : hWnd(NULL), hDC(NULL), hBackDC(NULL), width(0), height(0), currScene(NULL) {}
	public:
		~SceneManager();
		void Initialize(HWND hWnd, UINT32 width, UINT32 height);
		void Release();
		void Render();

		bool RegisterScene(LPCSTR sceneName, Scene* scene); //Scene�� ���.
		bool LoadScene(LPCSTR scenenName); //�ҷ� �� Scene�� ����.

		UINT32 GetWidth() const { return width; } //�������� Ŭ���̾�Ʈ �ʺ�.
		UINT32 GetHeight() const { return height; } //�������� Ŭ���̾�Ʈ ����.
		HWND GetHWND() const { return hWnd; }
		HDC GetBackDC() const { return hBackDC; }
	private:
		void SetScene(); //��ϵ� Scene�� ����
		void Update();
		void Draw();
		HBITMAP CreateDIBSectionRe(); //Back Bitmap�� ����� ���� ��Ʈ�� Creater

		friend Singleton; //friend�� ����ϴ� �ʿ��� public���� ����-����� �����ϸ�, �̱��� new ������ pInstance ���ٿ� ���ǰ� �ִ�.
	}; //class SceneManager
#define SceneMgr SceneManager::GetInstance()
} //namespace ENGINE

#endif // !SCENE_MANAGER_H