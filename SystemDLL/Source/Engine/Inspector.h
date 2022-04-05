#pragma once

namespace InspectorView {
	VOID SYSTEM_DLL Open();
	VOID SYSTEM_DLL Update();
	VOID SYSTEM_DLL Close();
	VOID SYSTEM_DLL ObjectChanged(GameObject* selected);
	std::vector<std::pair<WSTRING, PROPERTY*>>* GetProperty();
	HMENU SYSTEM_DLL GetGUIID();
	VOID SYSTEM_DLL AddProperty(GUILayout* type);
	VOID SYSTEM_DLL AddProperty(PrimitiveType type, const WCHAR* name, VOID* data);
}



// Inspector.h
// ?†ÌÉù???§Î∏å?ùÌä∏???ïÎ≥¥Î•?Î≥????àÎã§.
class SYSTEM_DLL Inspector : public Win32::Window {
public:
	Inspector();
	~Inspector();
public:
	std::vector<std::pair<WSTRING, PROPERTY*>> m_Property;
	std::vector<GUILayout*> m_GUILayout;

	GameObject* m_Selected;
public:
	VOID Update();
	VOID Release();
	VOID ObjectChanged(GameObject* selected);
	VOID ExecuteCommand(WPARAM wParam, LPARAM lParam);
	virtual LRESULT MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) override;
	VOID OnPaint();

public:
	std::vector<std::pair<WSTRING, PROPERTY*>>* GetProperty() { return &m_Property; }
	std::vector<GUILayout*>* GetGUILayout() { return &m_GUILayout; }
};