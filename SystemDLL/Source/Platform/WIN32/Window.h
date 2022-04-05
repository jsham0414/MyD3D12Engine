#pragma once 

#include "SubObject.h"

#pragma comment (lib, "uxtheme.lib")
#include <Uxtheme.h>

namespace Win32 {


	class SYSTEM_DLL Window : public Win32::SubObject, public Win32::Caption {
	public:
		Window(WSTRING wsTitle, HICON hIcon, WindowType type = RESIZEABLE);
		~Window();

		virtual VOID Initialize() override;

		virtual LRESULT MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) override;
		VOID OnNonClientActivate(BOOL active);
		VOID RedrawWindow();
		VOID OnNonClientCreate();
		VOID OnNonClientPaint(HRGN region);
		VOID OnNonClientLMBDown();
		VOID OnNonClientLMBUp();
		VOID OnGetMinMaxInfo(MINMAXINFO* minmax);
		VOID OnEnterSizeMove();
		VOID OnExitSizeMove();
		VOID OnPaint();
		VOID PaintCaption(HDC hdc);
		VOID DrawRect(HDC hdc, INT x, INT y, INT width, INT height, COLORREF color);
	protected:
		INT m_iWidth;
		INT m_iHeight;

		SIZE m_Size;
		WindowType m_Type;

		BOOL m_Active;
		DWORD m_Flags;
	public:
		SIZE Size() { return m_Size; }
		BOOL Active() { return m_Active; }
	public:
		VOID Size(SIZE size) { m_Size = size; }
		VOID Size(INT cx, INT cy) { m_Size.cx = cx; m_Size.cy = cy; }
		VOID Active(BOOL active) { m_Active = active; }
	};
}