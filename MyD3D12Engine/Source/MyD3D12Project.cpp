#include "MyD3D12Project.h"
#include "Engine/Simulation.h"
#include "Platform/Win32/WinEntry.h"
#include <Engine/SplashScreen.h>
#include <Engine/Inspector.h>
#include <Engine/Hierarchy.h>

class MyD3D12Project : public SystemDLL::Simulation {
	// Application
public:
	MyD3D12Project() {};
	virtual ~MyD3D12Project() {};

public:
	VOID SetupPerGameSettings();
	VOID Initialize() {};
	virtual VOID Release();
	//VOID Update() {};
}; 

ENTRY_APP(MyD3D12Project)

VOID MyD3D12Project::SetupPerGameSettings() {
	PerGameSettings::SetGameName(IDS_PERGAMENAME);
	PerGameSettings::SetShortName(IDS_SHORTNAME);
	PerGameSettings::SetMainIcon(IDI_MAINICON);
	PerGameSettings::SetSplashURL(IDS_SPLASHURL);
}

VOID MyD3D12Project::Release() {
	ObjectManager::GetInstance()->Release();

	SplashScreen::Close();
	InspectorView::Close();
	HierarchyView::Close();
}