#pragma once
#include "EngineMecro.h"

//특별한 기능이 없는 UI Tool Base, 계층구조 등을 만들 때 사용 가능

#ifndef UI_PANEL_H
#define UI_PANEL_H

namespace ENGINE
{
	enum class UIType 
	{ 
		PANEL, IMAGE, BUTTON, LABEL 
	};

	class UIPanel
	{
	protected:
		BOOL isEnable, pivotCenter;
		POINT position, localPosition;
		RECT rect;
		SIZE size;
		UIPanel* parent;
		std::vector<UIPanel*> child;
		UIType uiType;

	public:
		UIPanel();
		virtual ~UIPanel();

	private:
		VOID SetParent(UIPanel* parent) { this->parent = parent; }
		VOID SetLocalPos(INT32 x, INT32 y);

	protected:
		virtual VOID SetRect(BOOL pivotCenter) { rect = { localPosition.x, localPosition.y, localPosition.x, localPosition.y }; }

	public:
		// 월드(스크린) 좌표 상의 위치.
		virtual VOID SetPosition(INT32 x, INT32 y, BOOL pivotCenter = FALSE); 
		// 부모 UI를 중점으로 한 위치.
		virtual VOID SetLocalPosition(INT32 x, INT32 y, BOOL pivotCenter = FALSE); 
		virtual VOID Update();
		virtual VOID Draw();

		// 자식으로 추가된 ui는 알아서 메모리를 해제한다.
		// 계층구조, 자식 UI 추가.
		UIPanel* AddChildUI(UIPanel* ui); 
		// 자식에서 제외하고 메모리 해제를 하지 않는다.
		VOID RemoveChildUI(UIPanel* ui); 
		// 변경된 자신의 위치를 중심으로 자식 UI의 위치를 재배치.
		VOID RefreshPos(); 
		VOID SetEnable(BOOL enable) { isEnable = enable; }

		BOOL Enable() CONST { return isEnable; }
		UINT32 GetChildCount() CONST { return child.size(); }
		UIPanel* GetChild(INT32 index);
		UIPanel* GetParent() CONST { return parent; }
		POINT GetPosition() CONST { return position; }
		POINT GetLocalPosition() CONST { return localPosition; }
		UIType GetUIType() CONST { return uiType; }
		SIZE GetSize() CONST { return size; }
	}; // class UIPanel

} // namespace ENGINE
#endif // !UI_PANEL_H
