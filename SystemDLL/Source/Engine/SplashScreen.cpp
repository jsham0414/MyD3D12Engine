#include "SystemDLL.h"
#include "SplashScreen.h"
#include "Platform/WIN32/Win32Utils.h"

namespace SplashScreen {
#define WM_OUTPUTMESSAGE (WM_USER + 0x0001)

	SplashWindow* m_pSplashWindow;

	VOID Open() {
		if (m_pSplashWindow != nullptr) {
			return;
		}

		m_pSplashWindow = new SplashWindow();

		
	}

	VOID Close() {
		if (!m_pSplashWindow)
			return;

		DestroyWindow(m_pSplashWindow->Handle());
		SAFE_DELETE(m_pSplashWindow);
	}

	VOID AddMessage(const WCHAR* message) {
		return VOID SYSTEM_DLL();
	}
}

SplashWindow::SplashWindow() : Win32::Window(L"SplashScreen", NULL, Win32::WindowType::POPUP) {
	wcscpy_s(m_outputMessage, L"SplashScreen Starting ...");
	Size(500, 600);

	Win32::Window::RegisterNewClass();
	Win32::Window::Initialize();
}

SplashWindow::~SplashWindow() {
}

LRESULT SplashWindow::MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_PAINT:
		HBITMAP hBitmap;
		HDC hdc, hMemdc;
		PAINTSTRUCT ps;

		hdc = BeginPaint(hWnd, &ps);

		//Win32::Utils::AddBitmap(PerGameSettings::SplashURL(), hdc, 0, 0);

		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(255, 255, 255));

		if (Engine::GetMode() != Engine::EngineMode::RELEASE) {
			WSTRING engineModeText = Engine::EngineModeToString() + L" Mode";
			SetTextAlign(hdc, TA_RIGHT);
			TextOut(hdc, Size().cx - 15, 15, engineModeText.c_str(), wcslen(engineModeText.c_str()));
		}

		SetTextAlign(hdc, TA_CENTER);

		TextOut(hdc, Size().cx / 2, Size().cy - 30, m_outputMessage, wcslen(m_outputMessage));
		EndPaint(hWnd, &ps);
		break;
	case WM_OUTPUTMESSAGE:
		WCHAR* wcMsg = (WCHAR*)wParam;
		wcscpy_s(m_outputMessage, wcMsg);
		RedrawWindow();
		return 0;
	}

	return Window::MessageHandler(hWnd, msg, wParam, lParam);
}
