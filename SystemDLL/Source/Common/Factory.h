#pragma once

template <typename T1>
class Factory {
public:
	static T1* CreateInstance() {
		T1* pObject = new T1;
		pObject->Initialize();
		return (T1*)pObject;
	}

	static T1* CreateProperty(PrimitiveType type, const WCHAR* name, VOID* data) {


		T1* pObject = new T1(type, name, data);
		return (T1*)pObject;
	}

	static T1* CreateEdit(HWND parent, XMFLOAT3 pos, WSTRING text, DWORD flag = 0) {
		T1* pObject = new T1(parent, pos, text, flag);
		return (T1*)pObject;
	}

	static T1* CreateGUIVector3(PrimitiveType type, const WCHAR* name, VOID* data) {
		T1* pObject = new T1(type, name, data);
		return (T1*)pObject;
	}

	static T1* CreateGUITextbox(HWND parent, PROPERTY* prop, DWORD flag = 0) {
		T1* pObject = new T1(parent, prop, flag);
		return (T1*)pObject;
	}

	static T1* CreateLabel(HWND parent, XMFLOAT3 pos, WSTRING text, DWORD flag = 0) {
		T1* pObject = new T1(parent, pos, text, flag);
		return pObject;
	}

public:
	Factory() {};
	~Factory() {};
};