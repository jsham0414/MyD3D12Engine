#pragma once
#include <string>

namespace Time {
	// ?„μ¬ ?κ°„???¤νΈλ§μΌλ΅?λ°ν™?λ‹¤.
	WSTRING SYSTEM_DLL GetTime(BOOL stripped = FALSE);

	// ?„μ¬ ? μ§λ¥??¤νΈλ§μΌλ΅?λ°ν™?λ‹¤.
	WSTRING SYSTEM_DLL GetDate(BOOL stripped = FALSE);

	// ?„μ¬ ? μ§?€ ?κ°„???¤νΈλ§μΌλ΅?λ°ν™?λ‹¤.
	WSTRING SYSTEM_DLL GetDateTimeString(BOOL stripped = FALSE);
}