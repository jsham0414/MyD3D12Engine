#include "SystemDLL.h"
#include "Window.h"
#include <Core/CoreDefinitions.cpp>

#define DCX_USETYPE 0x00010000

namespace Win32 {
	Window::Window(WSTRING wsTitle, HICON hIcon, WindowType type)
		: Win32::SubObject(wsTitle, wsTitle, hIcon), m_Type(type), m_Flags(0) {
		Size(DEFAULTWIDTH, DEFAULTHEIGHT);
	}

	Window::~Window() {
	}

	VOID Window::Initialize() {
		RECT desktop;
		const HWND hDesktop = GetDesktopWindow();
		GetWindowRect(hDesktop, &desktop);

		RECT r = { 0, 0, m_Size.cx, m_Size.cy };
		AdjustWindowRect(&r, m_Type, false);
		int w = r.right - r.left;
		int h = r.bottom - r.top;

		m_hWnd = CreateWindow(m_Name.c_str(), m_Title.c_str(), m_Type,
			((desktop.right / 2) - (m_Size.cx / 2)), ((desktop.bottom / 2) - (m_Size.cy / 2)),
			m_Size.cx, m_Size.cy, nullptr, nullptr, hInstance(), (void*)this);
		if (!m_hWnd) {
			MessageBox(0, L"?덈룄???앹꽦???ㅽ뙣?덉뒿?덈떎.", 0, 0);
			return;
		}

		ShowWindow(m_hWnd, SW_SHOW);
		UpdateWindow(m_hWnd);
	}

	LRESULT Window::MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		switch (msg) {
		case WM_NCCREATE:
			OnNonClientCreate();
			return TRUE;
		case WM_NCACTIVATE:
			OnNonClientActivate(LOWORD(wParam) != WA_INACTIVE);
			return TRUE;
		case WM_NCPAINT:
			OnNonClientPaint((HRGN)wParam);
			return FALSE;
		case WM_NCLBUTTONDOWN:
			SetTimer(hWnd, 2, 10, NULL);
			OnNonClientLMBDown();
			break;
		case WM_NCLBUTTONUP:
			KillTimer(hWnd, 2);
			OnNonClientLMBUp();
			break;
		case WM_NCLBUTTONDBLCLK:
			Win32::Utils::MaximizeWindow(hWnd);
			return 0;
		case WM_GETMINMAXINFO:
			OnGetMinMaxInfo((MINMAXINFO*)lParam);
			return 0;
		case WM_ENTERSIZEMOVE:
			OnEnterSizeMove();
			return 0;
		case WM_EXITSIZEMOVE:
			OnExitSizeMove();
			return 0;
		case WM_PAINT:
			OnPaint();
			break;
		case WM_TIMER:
			switch (wParam) {
			case 1:
				RedrawWindow();
				break;
			case 2:
				if (!(GetKeyState(VK_LBUTTON) & 0x8000)) {
					SendMessage(hWnd, WM_NCLBUTTONUP, 0, 0);
				}
				break;
			}
			break;
		}

		return SubObject::MessageHandler(hWnd, msg, wParam, lParam);
	}

	VOID Window::OnNonClientActivate(BOOL active) {
		Active(active);
	}

	VOID Window::RedrawWindow() {
		SetWindowPos(Handle(), 0, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_DRAWFRAME | SWP_FRAMECHANGED);
		SendMessage(Handle(), WM_PAINT, 0, 0);
	}

	VOID Window::OnNonClientCreate() {
		SetTimer(Handle(), 1, 100, NULL);
		SetWindowTheme(Handle(), L"", L"");
		Win32::Utils::ModifyClassStyle(Handle(), 0, CS_DROPSHADOW);

		Win32::Caption::AddCaptionButton(new CaptionButton(L"X", CB_CLOSE));
		Win32::Caption::AddCaptionButton(new CaptionButton(L"🗖", CB_MAXIMIZE));
		Win32::Caption::AddCaptionButton(new CaptionButton(L"🗕", CB_MINIMIZE));
	}

	VOID Window::OnNonClientPaint(HRGN region) {
		// 珥덇린???④퀎

		HDC hdc = GetDCEx(Handle(), region, DCX_WINDOW | DCX_INTERSECTRGN | DCX_USETYPE);

		RECT rect;
		GetWindowRect(Handle(), &rect);

		SIZE size = SIZE{ rect.right - rect.left, rect.bottom - rect.top };

		HBITMAP hbmMem = CreateCompatibleBitmap(hdc, size.cx, size.cy);
		HANDLE hOld = SelectObject(hdc, hbmMem);

		// 洹몃━湲??④퀎

		HBRUSH brush = CreateSolidBrush(RGB(46, 46, 46));

		RECT newRect = RECT{ 0, 0, size.cx, size.cy };
		FillRect(hdc, &newRect, brush);

		if (Active() && !Win32::Utils::IsWindowFullscreen(Handle())) {
			brush = CreateSolidBrush(RGB(0, 100, 150));
			FrameRect(hdc, &newRect, brush);
		}

		PaintCaption(hdc);

		// ?댁젣 ?④퀎

		DeleteObject(brush);

		// ?붾툝 踰꾪띁留?
		BitBlt(hdc, 0, 0, size.cx, size.cy, hdc, 0, 0, SRCCOPY);

		SelectObject(hdc, hOld);
		DeleteObject(hbmMem);

		ReleaseDC(Handle(), hdc);
	}

	VOID Window::OnNonClientLMBDown() {

		POINT pt;
		GetCursorPos(&pt);

		RECT rect;
		GetWindowRect(Handle(), &rect);

		pt.x -= rect.left;
		pt.y -= rect.top;

		INT spacing = 0;
		for (auto& button : Caption::CaptionButtons()) {
			if (button->Rect.left < pt.x && button->Rect.right > pt.x && button->Rect.top < pt.y && button->Rect.bottom > pt.y) {
				EnableWindow(Handle(), FALSE);
			}
		}
	}

	VOID Window::OnNonClientLMBUp() {
		if (m_Flags & WF_NOTUSECAPTION)
			return;

		POINT pt;
		GetCursorPos(&pt);

		RECT rect;
		GetWindowRect(Handle(), &rect);

		pt.x -= rect.left;
		pt.y -= rect.top;

		INT spacing = 0;
		for (auto& button : Caption::CaptionButtons()) {
			if (button->Rect.left < pt.x && button->Rect.right > pt.x && button->Rect.top < pt.y && button->Rect.bottom > pt.y) {
				switch (button->Command) {
				case CB_CLOSE:
					SendMessage(Handle(), WM_CLOSE, 0, 0);
					break;
				case CB_MINIMIZE:
					ShowWindow(Handle(), SW_MINIMIZE);
					break;
				case CB_MAXIMIZE:
					Win32::Utils::MaximizeWindow(Handle());
					break;
				}
			}
		}

		EnableWindow(Handle(), TRUE);
	}

	VOID Window::OnGetMinMaxInfo(MINMAXINFO* minmax) {
		RECT WorkArea;
		SystemParametersInfo(SPI_GETWORKAREA, 0, &WorkArea, 0);
		minmax->ptMaxSize.x = WorkArea.right - WorkArea.left;
		minmax->ptMaxSize.y = WorkArea.bottom - WorkArea.top;
		m_Size.cx = WorkArea.right - WorkArea.left;
		m_Size.cy = WorkArea.bottom - WorkArea.top;
		minmax->ptMaxPosition.x = WorkArea.left;
		minmax->ptMaxPosition.y = WorkArea.top;
		minmax->ptMinTrackSize.x = 300;
		minmax->ptMinTrackSize.y = 200;
	}

	VOID Window::OnEnterSizeMove() {
		Win32::Utils::ModifyWindowStyle(Handle(), 0, WS_SIZEBOX);
		RECT rect;
		GetWindowRect(Handle(), &rect);
		m_Size.cx = rect.right - rect.left;
		m_Size.cy = rect.bottom - rect.top;
	}

	VOID Window::OnExitSizeMove() {
		RECT rect;
		GetWindowRect(Handle(), &rect);
		m_Size.cx = rect.right - rect.left;
		m_Size.cy = rect.bottom - rect.top;
		RECT WorkArea;
		SystemParametersInfo(SPI_GETWORKAREA, 0, &WorkArea, 0);
		if (rect.top < WorkArea.top + 5 && !Win32::Utils::IsWindowFullscreen(Handle())) {
			Win32::Utils::MaximizeWindow(Handle());
		}

		if (m_Flags & WF_NOTUSEPARENTPAINT)
			return;

		InvalidateRect(Handle(), NULL, TRUE);
	}

	VOID Window::OnPaint() {
		if (m_Flags & WF_NOTUSEPARENTPAINT)
			return;

		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(Handle(), &ps);

		RECT rc;
		GetClientRect(Handle(), &rc);

		HBRUSH brush;
		brush = CreateSolidBrush(RGB(36, 36, 36));

		FillRect(hdc, &rc, brush);

		DeleteObject(brush);

		EndPaint(Handle(), &ps);
	}

	VOID Window::PaintCaption(HDC hdc) {
		RECT rect;
		GetWindowRect(Handle(), &rect);

		SIZE size = SIZE{ rect.right - rect.left, rect.bottom - rect.top };

		if (ShowTitle()) {
			rect = RECT{ 0, 0, size.cx, 30 };
			SetBkMode(hdc, TRANSPARENT);
			SetTextColor(hdc, Active() ? RGB(255, 255, 255) : RGB(92, 92, 92));

			/* 
			DT_SINGLELINE		?띿뒪?몃? ??以꾩뿉 ?쒖떆?쒕떎
			DT_VCENTER		?띿뒪?몃? ?섏쭅 媛?대뜲???뺣젹?⑸땲??
			DT_CENTER			?띿뒪?몃? 媛?대뜲 ?뺣젹?⑸땲??
			*/
			DrawText(hdc, m_Title.c_str(), wcslen(m_Title.c_str()), &rect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
		}

		if (m_Flags & WF_NOTUSECAPTION)
			return;

		POINT pt;
		GetCursorPos(&pt);

		GetWindowRect(Handle(), &rect);

		pt.x -= rect.left;
		pt.y -= rect.top;

		INT spacing = 0;
		for (auto& button : Caption::CaptionButtons()) {
			spacing += button->Width;
			button->Rect = RECT{ size.cx - spacing, 0, size.cx - spacing + button->Width, 30 };

			if (button->Rect.left < pt.x && button->Rect.right > pt.x && button->Rect.top < pt.y && button->Rect.bottom > pt.y) {
				HBRUSH brush;
				if (!(GetKeyState(VK_LBUTTON) & 0x8000)) {
					brush = CreateSolidBrush(RGB(92, 92, 92));
				} else {
					brush = CreateSolidBrush(RGB(0, 100, 150));
				}
				FillRect(hdc, &button->Rect, brush);
				DeleteObject(brush);
			}

			if (button->Text.compare(L"?뿒") == 0 && Win32::Utils::IsWindowFullscreen(Handle())) {
				button->Text = L"?뿓";
			} else if (button->Text.compare(L"?뿓") == 0 && !Win32::Utils::IsWindowFullscreen(Handle())) {
				button->Text = L"?뿒";
			}

			DrawText(hdc, button->Text.c_str(), wcslen(button->Text.c_str()), &button->Rect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
		}

	}

	VOID Window::DrawRect(HDC hdc, INT x, INT y, INT width, INT height, COLORREF color) {
		HBRUSH brush = CreateSolidBrush(color);
		HPEN pen = CreatePen(PS_SOLID, 1, color);
		HGDIOBJ oldBrush = SelectObject(hdc, brush);
		HGDIOBJ oldPen = SelectObject(hdc, pen);
		
		Rectangle(hdc, x, y, x + width, y + height);
		
		SelectObject(hdc, oldBrush);
		SelectObject(hdc, oldPen);
		DeleteObject(brush);
		DeleteObject(pen);
	}
}

