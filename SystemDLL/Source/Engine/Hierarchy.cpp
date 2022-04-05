#include "SystemDLL.h"
#include "Hierarchy.h"
#include "Inspector.h"

namespace HierarchyView {
	Hierarchy* m_pHierarchyWindow;

	VOID SYSTEM_DLL HierarchyView::Open() {
		if (m_pHierarchyWindow != nullptr) {
			return;
		}

		m_pHierarchyWindow = new Hierarchy();
	}

	VOID SYSTEM_DLL HierarchyView::Close() {
		if (!m_pHierarchyWindow)
			return;

		DestroyWindow(m_pHierarchyWindow->Handle());
		SAFE_DELETE(m_pHierarchyWindow);
	}
}


Hierarchy::Hierarchy() : Win32::Window(L"Hierarchy", NULL) {
	m_Flags = WF_NOTUSECAPTION;

	Size(300, 600);

	Win32::Window::RegisterNewClass();
	Win32::Window::Initialize();

	InvalidateRect(Handle(), NULL, TRUE);
}

Hierarchy::~Hierarchy() {
}

LRESULT Hierarchy::MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_LBUTTONDOWN:
		OnLMBDown();
		break;
	case WM_PAINT:
		OnPaint();
		break;
	}

	return Window::MessageHandler(hWnd, msg, wParam, lParam);
}

VOID Hierarchy::OnLMBDown() {
	POINT pt;
	GetCursorPos(&pt);

	RECT rect, rcc;
	GetWindowRect(Handle(), &rect);

	pt.x -= rect.left;
	pt.y -= rect.top;

	m_Selected = nullptr;

	INT i = 0;
	auto objs = ObjectManager::GetInstance()->GetObjects();
	for (auto iter = objs->begin(); iter != objs->end(); iter++) {
		RECT rc = { 8, 32 + i * 24, 8 + m_Size.cx, 32 + (i + 1) * 24 };
		if (rc.left < pt.x && rc.right > pt.x && rc.top < pt.y && rc.bottom > pt.y) {
			m_Selected = *iter;
			break;
		}
		i++;
	}

	InspectorView::ObjectChanged(m_Selected);
	InvalidateRect(Handle(), NULL, TRUE);
}

VOID Hierarchy::OnPaint() {

	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(Handle(), &ps);

	RECT rc;
	rc = { 0, 0, m_Size.cx, m_Size.cy };
	HBRUSH brush = CreateSolidBrush(RGB(36, 36, 36));
	FillRect(hdc, &rc, brush);
	DeleteObject(brush);

	INT i = 0;
	auto objs = ObjectManager::GetInstance()->GetObjects();
	for (auto iter = objs->begin(); iter != objs->end(); iter++) {
		if (m_Selected == *iter) {
			brush = CreateSolidBrush(RGB(92, 92, 92));
			rc = { 0, i * 24, m_Size.cx, (i + 1) * 24 };
			FillRect(hdc, &rc, brush);
			DeleteObject(brush);
		}

		SetBkMode(hdc, TRANSPARENT);
		SetTextAlign(hdc, TA_LEFT);
		SetTextColor(hdc, RGB(255, 255, 255));
		TextOut(hdc, 3, 3 + i * 24, (*iter)->GetName().c_str(), wcslen((*iter)->GetName().c_str()));

		i++;
	}

	EndPaint(Handle(), &ps);
}