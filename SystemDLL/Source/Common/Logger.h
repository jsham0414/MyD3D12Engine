#pragma once
#include <string>

class SYSTEM_DLL Logger {
	// ?��????�래???�용???�한 ?�퍼?�스
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