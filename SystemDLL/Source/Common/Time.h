#pragma once
#include <string>

namespace Time {
	// 현재 시간을 스트링으로 반환한다.
	WSTRING SYSTEM_DLL GetTime(BOOL stripped = FALSE);

	// 현재 날짜를 스트링으로 반환한다.
	WSTRING SYSTEM_DLL GetDate(BOOL stripped = FALSE);

	// 현재 날짜와 시간을 스트링으로 반환한다.
	WSTRING SYSTEM_DLL GetDateTimeString(BOOL stripped = FALSE);
}