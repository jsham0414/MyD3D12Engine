#pragma once

#define DEFAULTWIDTH 800
#define DEFAULTHEIGHT 600

namespace Win32 {
	enum WindowType : DWORD {
		STATIC		= WS_OVERLAPPED,
		RESIZEABLE = WS_SIZEBOX,
		POPUP		= WS_POPUP,
	};

	namespace Utils {
		// AddBitmap 선언
		BOOL AddBitmap(CONST WCHAR* szFileName, HDC hWinDC, INT x = 0, INT y = 0);

		inline VOID SYSTEM_DLL ModifyWindowStyle(HWND hWnd, DWORD flagsToDisable, DWORD flagsToEnable) {
			DWORD style = GetWindowLong(hWnd, GWL_STYLE);
			SetWindowLong(hWnd, GWL_STYLE, (style & ~flagsToDisable) | flagsToEnable);
		}

		inline VOID SYSTEM_DLL ModifyWindowExStyle(HWND hWnd, DWORD flagsToDisable, DWORD flagsToEnable) {
			DWORD exStyle = GetWindowLong(hWnd, GWL_EXSTYLE);
			SetWindowLong(hWnd, GWL_EXSTYLE, (exStyle & ~flagsToDisable) | flagsToEnable);
		}

		inline BOOL SYSTEM_DLL HasStyle(HWND hWnd, DWORD style) {
			DWORD dwStyle = (DWORD)GetWindowLong(hWnd, GWL_STYLE);
			if ((dwStyle & style) != 0) return TRUE;
			return FALSE;
		}

		inline VOID SYSTEM_DLL ModifyClassStyle(HWND hWnd, DWORD flagsToDisable, DWORD flagsToEnable) {
			DWORD style = GetWindowLong(hWnd, GCL_STYLE);
			SetClassLong(hWnd, GCL_STYLE, (style & ~flagsToDisable) | flagsToEnable);
		}

		inline BOOL SYSTEM_DLL IsWindowFullscreen(HWND hWnd) {
			WINDOWPLACEMENT placement;
			ZeroMemory(&placement, sizeof(WINDOWPLACEMENT));
			GetWindowPlacement(hWnd, &placement);

			if (placement.showCmd == SW_MAXIMIZE)
				return TRUE;
			return FALSE;
		}

		inline VOID SYSTEM_DLL MaximizeWindow(HWND hWnd) {
			WINDOWPLACEMENT wPos;
			ZeroMemory(&wPos, sizeof(WINDOWPLACEMENT));
			GetWindowPlacement(hWnd, &wPos);

			if (wPos.showCmd == SW_MAXIMIZE) {
				ShowWindow(hWnd, SW_NORMAL);
				ModifyWindowStyle(hWnd, 0, WS_SIZEBOX);
			} else {
				ShowWindow(hWnd, SW_MAXIMIZE);
				ModifyWindowStyle(hWnd, WS_SIZEBOX, 0);
			}
		}

	}
}