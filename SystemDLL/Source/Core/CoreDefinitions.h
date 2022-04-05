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
#define WF_NOTUSEPARENTPAINT 0x02

#define GUI_NUMONLY 0x01

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

inline const wchar_t* GetWC(const char* c) {
	const size_t cSize = strlen(c) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, c, cSize);

	return wc;
}

#define GET_NAME(n) #n
#define GET_NAME_WC(n) GetWC(GET_NAME(n))

enum class PrimitiveType {
	INT = 0,
	FLOAT,
	DOUBLE,
	SHORT,
	LONG,
	CHAR,
	BOOL,
	BYTE,
	FLOAT3,
};

typedef std::wstring WSTRING;
typedef std::string STRING;


typedef struct tagPropertyInfo {
	PrimitiveType Type;
	const WCHAR* Name;
	VOID* Data;

	tagPropertyInfo(PrimitiveType type, const WCHAR* name, VOID* data) {
		Type = type;
		Name = name;
		Data = data;
	}

	WSTRING ToString() {
		switch (Type) {
		case PrimitiveType::FLOAT:
			return std::to_wstring(*reinterpret_cast<FLOAT*>(Data));
		default:
			return WSTRING();
		}
	}

	//VOID Next(PROPERTY* next) { Next = next; }

} PROPERTY;

#define CREATE_PROPERTY(type, name, data) Factory<PROPERTY>::CreateProperty(type, name, data)
#define CREATE_PROPERTY(type, data) Factory<PROPERTY>::CreateProperty(type, GET_NAME_WC(data), (VOID*)&data)