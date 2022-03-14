#pragma once

#include "Platform/WIN32/Window.h"

namespace SplashScreen {
	VOID SYSTEM_DLL Open();
	VOID SYSTEM_DLL Close();
	VOID SYSTEM_DLL AddMessage(CONST WCHAR* message);
}

// SplashWindow.h
// 엔진 시작 화면
class SYSTEM_DLL SplashWindow : public Win32::Window {
public:
	SplashWindow();
	~SplashWindow();

	virtual LRESULT MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) override;
private:
	WCHAR m_outputMessage[MAX_NAME_STRING];
};