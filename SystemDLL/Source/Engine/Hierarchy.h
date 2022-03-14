#pragma once
#include "Platform/WIN32/Window.h"

namespace HierarchyView {
	VOID SYSTEM_DLL Open();
	VOID SYSTEM_DLL Close();
}

// Hierarchy.h
// 씬 상의 오브젝트를 선택하거나 볼 수 있다.
class SYSTEM_DLL Hierarchy : public Win32::Window {
public:
	Hierarchy();
	~Hierarchy();

private:
	GameObject* m_Selected;

public:

	virtual LRESULT MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) override;
	VOID OnLMBDown();
	VOID OnPaint();
};