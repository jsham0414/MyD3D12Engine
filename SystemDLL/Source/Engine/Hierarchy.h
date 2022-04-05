#pragma once
#include "Platform/WIN32/Window.h"

namespace HierarchyView {
	VOID SYSTEM_DLL Open();
	VOID SYSTEM_DLL Close();
}

// Hierarchy.h
// ???ì˜ ?¤ë¸Œ?íŠ¸ë¥?? íƒ?˜ê±°??ë³????ˆë‹¤.
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