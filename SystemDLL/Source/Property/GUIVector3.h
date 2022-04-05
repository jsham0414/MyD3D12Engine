#pragma once

class SYSTEM_DLL GUIVector3 : public GUILayout {
public:
	GUIVector3(XMFLOAT3 pos, INT width, INT height, HWND parent, DWORD flag = NULL);
	virtual ~GUIVector3();

public:
	virtual VOID PreInitialize();
	virtual VOID Initialize();
	virtual VOID Progress();
	virtual VOID Render(HDC hdc);
	virtual VOID Release();

public:
	VOID NumberCheck();

private:
	WSTRING m_LastGood;
	INT m_HICaret, m_LOCaret;


};