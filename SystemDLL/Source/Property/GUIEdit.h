#pragma once

class SYSTEM_DLL GUIEdit : public GUILayout {
public:
	GUIEdit(HWND parent, XMFLOAT3 pos, WSTRING text, DWORD flag = 0);
	virtual ~GUIEdit();

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
	WSTRING m_Text;
	INT m_HICaret, m_LOCaret;
	std::function<VOID(VOID)> m_ChangedFunc;

public:
	std::function<VOID(VOID)>* GetChangedFunc() { return &m_ChangedFunc; }
	VOID ChangedFunc(std::function<VOID(VOID)> func) { m_ChangedFunc = func; }
};