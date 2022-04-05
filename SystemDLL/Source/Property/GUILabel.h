#pragma once

class SYSTEM_DLL GUILabel : public GUILayout {
public:
	GUILabel(XMFLOAT3 pos, INT width, INT height, WSTRING text, DWORD flag);
	virtual ~GUILabel();

public:
	virtual VOID PreInitialize();
	virtual VOID Initialize();
	virtual VOID Progress();
	virtual VOID Render(HDC hdc);
	virtual VOID Release();

private:
	WSTRING m_Text;
};