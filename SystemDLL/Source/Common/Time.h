#pragma once
#include <string>

namespace Time {
	// ?�재 ?�간???�트링으�?반환?�다.
	WSTRING SYSTEM_DLL GetTime(BOOL stripped = FALSE);

	// ?�재 ?�짜�??�트링으�?반환?�다.
	WSTRING SYSTEM_DLL GetDate(BOOL stripped = FALSE);

	// ?�재 ?�짜?� ?�간???�트링으�?반환?�다.
	WSTRING SYSTEM_DLL GetDateTimeString(BOOL stripped = FALSE);
}