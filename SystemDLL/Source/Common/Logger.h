#pragma once
#include <string>

class SYSTEM_DLL Logger {
	// 싱글톤 클래스 사용을 위한 레퍼런스
private:
	static Logger* instance;
public:
	static Logger* GetInstance() { return instance; }

public:
	Logger();
	~Logger();

	static VOID PrintLog(const WCHAR* fmt, ...);

	static WSTRING LogDirectory();
	static WSTRING LogFile();
	static VOID PrintDebugSeperator();
	static BOOL IsMTailRunning();
	static VOID StartMTail();
};