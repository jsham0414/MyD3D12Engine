#pragma once

class SYSTEM_DLL PerGameSettings {
	// 싱글톤 클래스 사용을 위한 레퍼런스
private:
	static PerGameSettings* inst;
public:
	static PerGameSettings* GetInstance() { return inst; }
public:
	PerGameSettings();
	~PerGameSettings();
private:
	// 게임 초기 변수 세팅
	WCHAR m_wcGameName[MAX_NAME_STRING];
	WCHAR m_wcShortName[MAX_NAME_STRING];
	HICON m_hMainIcon;
	WCHAR m_wcBootTime[MAX_NAME_STRING];
	WCHAR m_wcSplashURL[MAX_NAME_STRING];

public:
	// 게터 세터 선언
	static WCHAR* GameName() { return inst->m_wcGameName; }
	static VOID SetGameName(UINT id) { LoadString(hInstance(), id, inst->m_wcGameName, MAX_NAME_STRING); }

	static WCHAR* ShortName() { return inst->m_wcShortName; }
	static VOID SetShortName(UINT id) { LoadString(hInstance(), id, inst->m_wcShortName, MAX_NAME_STRING); }

	static HICON MainIcon() { return inst->m_hMainIcon; }
	static VOID SetMainIcon(UINT id) { LoadIcon(hInstance(), MAKEINTRESOURCE(id)); }

	static WCHAR* BootTime() { return inst->m_wcBootTime; }
	static VOID SetBootTime(UINT id) { LoadString(hInstance(), id, inst->m_wcBootTime, MAX_NAME_STRING); }

	static WCHAR* SplashURL() { return inst->m_wcSplashURL; }
	static VOID SetSplashURL(UINT id) { LoadString(hInstance(), id, inst->m_wcSplashURL, MAX_NAME_STRING); }
};