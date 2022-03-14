#include "SystemDLL.h"

PerGameSettings* PerGameSettings::inst;

PerGameSettings::PerGameSettings() {
	inst = this;

	wcscpy_s(inst->m_wcGameName, L"undefined");
	wcscpy_s(inst->m_wcShortName, L"undefined");
	wcscpy_s(inst->m_wcBootTime, L"undefined");

	wcscpy_s(inst->m_wcBootTime, Time::GetDateTimeString(TRUE).c_str());
	wcscpy_s(inst->m_wcSplashURL, L"..\\Olympus\\Conent\\Image\\OlympusSplash.bmp");

}

PerGameSettings::~PerGameSettings() {
}
