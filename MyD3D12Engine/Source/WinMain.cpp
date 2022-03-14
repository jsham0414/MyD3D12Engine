#include "pch.h"
#include "Application.h"

WCHAR		WindowClass[MAX_NAME_STRING];
WCHAR		WindowTitle[MAX_NAME_STRING];
INT			WindowWidth;
INT			WindowHeight;
HICON		hIcon;

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, INT);
LRESULT CALLBACK WindowProcess(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
VOID InitializeVariables();
VOID CreateWindowClass();
VOID InitializeWindow();
VOID MessageLoop();

/*
int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, INT) {
	InitializeVariables();
	CreateWindowClass();
	InitializeWindow();
	MessageLoop();

	return 0;
}
*/

LRESULT CALLBACK WindowProcess(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// 전역 변수 초기화
VOID InitializeVariables() {
	LoadString(hInstance(), IDS_PERGAMENAME, WindowClass, MAX_NAME_STRING);
	LoadString(hInstance(), IDS_WINDOWCLASS, WindowTitle, MAX_NAME_STRING);
	hIcon = LoadIcon(hInstance(), MAKEINTRESOURCE(IDI_MAINICON));
	WindowWidth = 1280;
	WindowHeight = 720;
}

// 윈도우 클래스 생성
VOID CreateWindowClass() {
	WNDCLASSEX wcEx;
	wcEx.cbSize = sizeof(WNDCLASSEX);
	wcEx.style = CS_HREDRAW | CS_VREDRAW;
	wcEx.cbClsExtra = 0;
	wcEx.cbWndExtra = 0;

	wcEx.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcEx.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);

	wcEx.hIcon = hIcon;
	wcEx.hIconSm = hIcon;

	wcEx.lpszClassName = WindowClass;

	wcEx.lpszMenuName = nullptr;

	wcEx.hInstance = hInstance();

	wcEx.lpfnWndProc = DefWindowProc;

	RegisterClassEx(&wcEx);
}

// 윈도우 초기화 및 생성
VOID InitializeWindow() {
	HWND hWnd = CreateWindow(WindowClass, WindowTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, WindowWidth, WindowHeight, nullptr, nullptr, hInstance(), nullptr);
	if (!hWnd) {
		MessageBox(0, L"윈도우 생성에 실패했습니다.", 0, 0);
		return;
	}

	ShowWindow(hWnd, SW_SHOW);
}

// 메시지 루프 처리
VOID MessageLoop() {
	MSG msg = { 0 };
	while (msg.message != WM_QUIT) {
		// 윈도우 메시지가 올 경우 처리
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {

		}
	}
}
