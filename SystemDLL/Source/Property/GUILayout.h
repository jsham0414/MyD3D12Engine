#pragma once

class SYSTEM_DLL GUILayout {
public:
	GUILayout(XMFLOAT3 pos, INT width, INT height);
	GUILayout();
	virtual ~GUILayout();

public:
	virtual VOID PreInitialize()PURE;
	virtual VOID Initialize()PURE;
	virtual VOID Progress()PURE;
	virtual VOID Render(HDC hdc)PURE;
	virtual VOID Release()PURE;
public:
	virtual VOID ValueChanged()PURE;
protected:
	HWND m_hWnd, m_ParentHandle;
	XMFLOAT3 m_Position;
	INT m_Width, m_Height;
	HMENU m_hID;
	DWORD m_Flag;
	PROPERTY* m_Property;

public:
	VOID ID(HMENU id) { m_hID = id; }
	HMENU ID() { return m_hID; }

	VOID Handle(HWND hWnd) { m_hWnd = hWnd; }
	HWND Handle() { return m_hWnd; }

	VOID Position(XMFLOAT3 pos) { m_Position = pos; }
	XMFLOAT3 Position() { return m_Position; }

	VOID ParentHandle(HWND hWnd) { m_ParentHandle = hWnd; }
	HWND ParentHandle() { return m_ParentHandle; }

	VOID Flag(DWORD flag) { m_Flag = flag; }
	DWORD Flag() { return m_Flag; }

	const PROPERTY* Property() { return m_Property; }
	VOID Property(PROPERTY* prop) { m_Property = prop; }
};