#include "MyD3D12Project.h"
#include "Engine/Simulation.h"
#include "Platform/Win32/WinEntry.h"

class MyD3D12Project : public SystemDLL::Simulation {
	// Application
public:
	MyD3D12Project() {};
	~MyD3D12Project() {};

public:
	VOID SetupPerGameSettings();
	VOID Initialize() {};
	//VOID Update() {};
}; 

ENTRY_APP(MyD3D12Project)

VOID MyD3D12Project::SetupPerGameSettings() {
	PerGameSettings::SetGameName(IDS_PERGAMENAME);
	PerGameSettings::SetShortName(IDS_SHORTNAME);
	PerGameSettings::SetMainIcon(IDI_MAINICON);
	PerGameSettings::SetSplashURL(IDS_SPLASHURL);
}
