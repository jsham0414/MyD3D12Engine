#pragma once
#include <string>

class SYSTEM_DLL Logger {
	// ?±ê????´ë˜???¬ìš©???„í•œ ?ˆí¼?°ìŠ¤
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