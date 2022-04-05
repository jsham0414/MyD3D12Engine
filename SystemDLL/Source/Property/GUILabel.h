#pragma once

class SYSTEM_DLL GUILabel : public GUILayout {
public:
	GUILabel(XMFLOAT3 pos, INT width, INT height, WSTRING text, DWORD flag);
	GUILabel(HWND parent, XMFLOAT3 pos, WSTRING text, DWORD flag = 0);
	virtual ~GUILabel();

public:
	virtual VOID PreInitialize();
	virtual VOID Initialize();
	virtual VOID Progress();
	virtual VOID Render(HDC hdc);
	virtual VOID Release();
public:
	virtual VOID ValueChanged() {};

private:
	WSTRING m_Text;
};