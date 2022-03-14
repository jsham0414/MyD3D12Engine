#pragma once

template <typename T1, typename T2>
class Factory {
public:
	static T1* CreateInstance() {
		T2* pObject = new T2;
		pObject->Initialize();
		return (T1*)pObject;
	}
public:
	Factory() {};
	~Factory() {};
};