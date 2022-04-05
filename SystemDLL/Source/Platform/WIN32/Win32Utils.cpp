#include "SystemDLL.h"
#include "Win32Utils.h"

namespace Win32 {
	namespace Utils {
		BOOL AddBitmap(CONST WCHAR* szFileName, HDC hWinDC, INT x, INT y) {
			BITMAP bBitmap;
			ZeroMemory(&bBitmap, sizeof(bBitmap));
			HDC hLocalDC = CreateCompatibleDC(hWinDC);

			HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, szFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			if (hBitmap == NULL) {
				MessageBox(NULL, L"LoadImage Failed", L"Error", MB_OK);
				return false;
			}

			GetObject(reinterpret_cast<HGDIOBJ>(hBitmap), sizeof(BITMAP), reinterpret_cast<LPVOID>(&hBitmap));

			SelectObject(hLocalDC, hBitmap);

			if (!BitBlt(hWinDC, x, y, bBitmap.bmWidth, bBitmap.bmHeight, hLocalDC, 0, 0, SRCCOPY)) {
				MessageBox(NULL, L"Blit Failed", L"Error", MB_OK);
				return false;
			}

			// ë©”ëª¨ë¦?? ë‹¹ ?´ì œ
			::DeleteDC(hLocalDC);
			::DeleteObject(hBitmap);
			return true;
		}
	}
}