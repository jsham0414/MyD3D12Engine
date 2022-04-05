#pragma once

class SYSTEM_DLL GUIEdit : public GUILayout {
public:
	GUIEdit(XMFLOAT3 pos, DWORD flag = 0);
	virtual ~GUIEdit();

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