#pragma once

#include "GUIEdit.h"
#include "GUILabel.h"

class SYSTEM_DLL GUITextBox : public GUILayout {
public:
	//GUITextBox(XMFLOAT3 pos, INT width, INT height, HWND parent, PROPERTY* prop, DWORD flag = NULL);
	GUITextBox(XMFLOAT3 pos, WSTRING text, HWND parent, DWORD flag);
	GUITextBox(HWND parent, PROPERTY* prop, DWORD flag = 0);
	virtual ~GUITextBox();

public:
	virtual VOID PreInitialize();
	virtual VOID Initialize();
	virtual VOID Progress();
	virtual VOID Render(HDC hdc);
	virtual VOID Release();

public:
	virtual VOID ValueChanged();

	VOID NumberCheck();
private:
	GUILabel* m_Text;
	GUIEdit* m_Edit;

	WSTRING m_LastGood;
	INT m_HICaret, m_LOCaret;

	
};