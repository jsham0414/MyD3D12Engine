#pragma once

namespace InspectorView {
	VOID SYSTEM_DLL Open();
	VOID SYSTEM_DLL Close();
}

// Inspector.h
// 선택된 오브젝트의 정보를 볼 수 있다.
class SYSTEM_DLL Inspector : public Win32::Window {
public:
	Inspector();
	~Inspector();

public:
	virtual LRESULT MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) override;
};