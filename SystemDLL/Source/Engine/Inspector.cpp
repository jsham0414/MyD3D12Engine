#include "SystemDLL.h"
#include "Inspector.h"

#define WM_INSPECTOR (WM_USER+0)
#define ID_EDIT 100

namespace InspectorView {
	Inspector* Window;

	VOID SYSTEM_DLL InspectorView::Open() {
		if (Window != nullptr) {
			return;
		}

		Window = new Inspector();
	}

	VOID SYSTEM_DLL InspectorView::Update() {
		if (Window == nullptr) {
			return;
		}

		Window->Update();
	}

	VOID SYSTEM_DLL InspectorView::Close() {
		if (!Window)
			return;

		DestroyWindow(Window->Handle());
		SAFE_DELETE(Window);
	}

	VOID SYSTEM_DLL ObjectChanged(GameObject* selected) {
		Window->ObjectChanged(selected);
	}

	std::vector<std::pair<WSTRING, PROPERTY*>>* GetProperty() {
		return Window->GetProperty();
	}
	
	VOID SYSTEM_DLL AddProperty(GUILayout* type) {
		type->ParentHandle(Window->Handle());
		Window->GetGUILayout()->push_back(type);
	}

	VOID SYSTEM_DLL AddProperty(PrimitiveType type, const WCHAR* name, VOID* data) {

	}

	HMENU SYSTEM_DLL GetGUIID() {
		return (HMENU)(ID_EDIT + Window->GetGUILayout()->size());
	}

	VOID SYSTEM_DLL AddProperty(WSTRING _name, PROPERTY* _property) {
		Window->GetProperty()->push_back(std::make_pair(_name, _property));
	}
}

Inspector::Inspector() : Window(L"Inspector", NULL) {
	m_Flags = WF_NOTUSECAPTION | WF_NOTUSEPARENTPAINT;
	
	Size(400, 600);

	Win32::Window::RegisterNewClass();
	Win32::Window::Initialize();

	//
}

Inspector::~Inspector() {
	Release();
}

VOID Inspector::Update() {
	for (auto iter = m_GUILayout.begin(); iter != m_GUILayout.end(); iter++) {
		(*iter)->Progress();
	}
}

VOID Inspector::ObjectChanged(GameObject* selected) {
	m_Property.clear();

	for (std::vector<GUILayout*>::iterator iter = m_GUILayout.begin(); iter != m_GUILayout.end(); iter++) {
		SAFE_DELETE(*iter);
	}
	m_GUILayout.clear();

	//DestroyWindow()

	m_Selected = selected;

	if (m_Selected != nullptr) {
		m_Selected->LoadProperties(Handle());
	}

	InvalidateRect(Handle(), NULL, TRUE);
	SendMessage(Handle(), WM_PRINT, 0, 0);
}

LRESULT Inspector::MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_PRINT:
		OnPaint();
		break;
	case WM_COMMAND:
		ExecuteCommand(wParam, lParam);
		break;
	case WM_EXITSIZEMOVE:
		InvalidateRect(Handle(), NULL, TRUE);
		SendMessage(Handle(), WM_PRINT, 0, 0);
		break;
	}

	return Window::MessageHandler(hWnd, msg, wParam, lParam);
}

VOID Inspector::OnPaint() {
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(Handle(), &ps);

	for (auto iter = m_GUILayout.begin(); iter != m_GUILayout.end(); iter++) {
		(*iter)->Render(hdc);
	}

	EndPaint(Handle(), &ps);

}

VOID Inspector::ExecuteCommand(WPARAM wParam, LPARAM lParam) {
	for (auto iter = m_GUILayout.begin(); iter != m_GUILayout.end(); iter++) {
		if ((*iter)->ID() == (HMENU)LOWORD(wParam)) {
			switch (HIWORD(wParam)) {
			case EN_CHANGE:
				(*iter)->ValueChanged();
				/*switch ((*iter)->Property()->Type) {
				case PrimitiveType::FLOAT:
					WCHAR str[256];
					GetWindowText((*iter)->Handle(), str, _countof(str));
					FLOAT fValue = _wtof(str);
					float* pValue = reinterpret_cast<float*>((*iter)->Property()->Data);
					(*pValue) = fValue;
					break;
				}*/
			}
		}
	}
}

VOID Inspector::Release() {
	// 프로퍼티 해제
	for (auto prop = m_Property.begin(); prop != m_Property.end(); prop++) {
		SAFE_DELETE((*prop).second);
	}
}