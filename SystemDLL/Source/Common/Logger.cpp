#include "SystemDLL.h"
#include <fstream>
#include <shlobj.h>
#include <cstdio>
#include <TlHelp32.h>

Logger* Logger::instance;

Logger::Logger() {
	instance = this;
}

Logger::~Logger() {
}

VOID Logger::PrintLog(const WCHAR* fmt, ...) {
	WCHAR buf[4096];
	va_list args;

	va_start(args, fmt);
	vswprintf_s(buf, fmt, args);
	va_end(args);

	OutputDebugString(buf);

	// %AppData%/?„ë¡œ?íŠ¸ ëª?Log/?„ë¡œ?íŠ¸ ëª?log ?•ì‹?¼ë¡œ ë¡œê·¸ê°€ ?¨ëŠ”??
	std::wfstream outFile;
	WSTRING wstr = WSTRING(LogDirectory() + L"\\" + LogFile());
	outFile.open(wstr, std::ios_base::app);

	if (outFile.is_open()) {
		WSTRING s = buf;
		outFile << L"[" << Time::GetDateTimeString() << L"] " << s;
		outFile.close();
		OutputDebugString(s.c_str());
	} else {
		MessageBox(NULL, L"ë¡œê·¸ ?Œì¼???????†ìŠµ?ˆë‹¤.", L"ë¡œê±° ?¤ë¥˜", MB_OK);
	}

}

WSTRING Logger::LogDirectory() {
	WCHAR Path[1024];
	WCHAR* AppDataLocal;

	SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, nullptr, &AppDataLocal);
	wcscpy_s(Path, AppDataLocal);
	wcscat_s(Path, L"\\");
	wcscat_s(Path, PerGameSettings::GameName());
	CreateDirectory(Path, NULL);
	wcscat_s(Path, L"\\Log");
	CreateDirectory(Path, NULL);

	return Path;
}

WSTRING Logger::LogFile() {
	WCHAR File[1024];
	wcscpy_s(File, PerGameSettings::GameName());
	wcscat_s(File, PerGameSettings::BootTime());
	wcscat_s(File, L".log");
	return File;
}

VOID Logger::PrintDebugSeperator() {
	WSTRING s = L"\n---------------------------------------------------------------------------------------\n\n";

#ifdef _DEBUG
	std::wfstream outFile;
	outFile.open(WSTRING(LogDirectory() + L"\\" + LogFile()), std::ios_base::app);

	if (outFile.is_open()) {
		outFile << s;
		outFile.close();
	} else {
		MessageBox(NULL, L"Unable to open log file...", L"Log Error", MB_OK);
	}
#endif
}

BOOL Logger::IsMTailRunning() {
	bool exists = false;
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(snapshot, &entry)) {
		while (Process32Next(snapshot, &entry)) {
			if (!_wcsicmp(entry.szExeFile, L"mTAIL.exe"))
				exists = true;
		}
	}

	CloseHandle(snapshot);
	return exists;
}

VOID Logger::StartMTail() {
	if (IsMTailRunning()) {
		Logger::PrintLog(L"--MTail failed to start - Already Running\n");
		return;
	}

	Logger::PrintLog(L"--Starting MTail\n");
	WCHAR path[MAX_PATH] = { 0 };
	GetCurrentDirectoryW(MAX_PATH, path);
	WSTRING url = path + WSTRING(L"/mTail.exe");
	WSTRING params = L" \"" + LogDirectory() + L"\\" + LogFile() + L"\" /start";
	ShellExecute(0, NULL, url.c_str(), params.c_str(), NULL, SW_SHOWDEFAULT);
}