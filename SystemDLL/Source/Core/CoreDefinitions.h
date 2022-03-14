#pragma once

#ifdef BUILD_DLL
#define SYSTEM_DLL __declspec(dllexport)
#else
#define SYSTEM_DLL __declspec(dllimport)
#endif

#define MAX_NAME_STRING 256
#define hInstance() GetModuleHandle(NULL)

#define DECLARE_SINGLETON(type)			\
public:												\
	static type** GetInstance(void) {			\
		static type* pInstance = new type;	\
		if(pInstance == NULL)					\
			pInstance = new type;				\
		return &pInstance;						\
	}													\
	static void DestroyInstance(void) {			\
		type** ppInstance = GetInstance();	\
		if(*ppInstance != NULL) {				\
			delete *ppInstance;					\
			*ppInstance = NULL;					\
		}												\
	}													\

#define WF_NOTUSECAPTION 0x01

#define GET_SINGLE(type) (*type::GetInstance())

enum WINMODE {
	WINMODE_FULL,
	WINMODE_WIN,
};

template<typename T>
inline VOID SAFE_DELETE(T& pointer) { delete pointer; (pointer) = NULL; }

template<typename T>
inline VOID SAFE_DELETE_ARRAY(T& pointer) { delete[] pointer; (pointer) = NULL; }

template<typename T>
inline VOID SAFE_DELETE_ARRAY_OBJ(T& pointer, int n) {
	if (pointer) { for (int i = 0; i < n; i++) { SAFE_DELETE((pointer)[i]); } delete[](pointer); pointer = NULL; }
}

template<typename T>
inline VOID SAFE_DELETE_ARRAY_ARRAY(T& pointer, int n) {
	if (pointer) { for (int i = 0; i < n; i++) { SAFE_DELETE_ARRAY((pointer)[i]); } delete[](pointer); pointer = NULL; }
}

typedef std::wstring WSTRING;
typedef std::string STRING;