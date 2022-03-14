#include "SystemDLL.h"

namespace Engine {
	OEngine g_SystemEngine;

	VOID SetMode(EngineMode mode) {
		g_SystemEngine.SetEngineMode(mode);
	}

	EngineMode GetMode() {
		return g_SystemEngine.GetEngineMode();
	}

	WSTRING SYSTEM_DLL EngineModeToString() {
		switch (Engine::GetMode()) {
		case EngineMode::DEBUG:		return L"Debug";
		case EngineMode::RELEASE:		return L"Debug";
		case EngineMode::EDITOR:		return L"EDITOR";
		case EngineMode::SERVER:		return L"SERVER";
		default:								return L"None";
		}
	}
}

OEngine::OEngine() {
#ifdef _DEBUG
	m_eEngineMode = EngineMode::DEBUG;
#else
	m_eEngineMode = EngineMode::RELEASE;
#endif
}

OEngine::~OEngine() {
}

EngineMode OEngine::GetEngineMode() {
	return m_eEngineMode;
}

VOID OEngine::SetEngineMode(EngineMode mode) {
	m_eEngineMode = mode;
}
