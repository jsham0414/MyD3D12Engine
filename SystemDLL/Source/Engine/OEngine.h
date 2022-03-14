#pragma once

class SYSTEM_DLL OEngine;

namespace Engine {
	enum EngineMode : INT {
		NONE,
		DEBUG,
		RELEASE,
		EDITOR,
		SERVER,
	};

	extern OEngine g_SystemEngine;

	VOID SetMode(EngineMode mode);
	EngineMode GetMode();
	WSTRING SYSTEM_DLL EngineModeToString();
}

using namespace Engine;
class SYSTEM_DLL OEngine {
public:
	OEngine();
	~OEngine();
private:
	EngineMode m_eEngineMode;

public:
	EngineMode GetEngineMode();
	VOID SetEngineMode(EngineMode mode);
};