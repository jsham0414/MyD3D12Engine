#include "SystemDLL.h"
#include "IApplication.h"
#include "Common/CmdLineArgs.h"
#include "Engine/Hierarchy.h"
#include "Engine/Inspector.h"
#include "Engine/SplashScreen.h"

extern Win32::IApplication* EntryApplication();

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, INT) {
	auto EntryApp = EntryApplication();

	PerGameSettings GameSettings;
	EntryApp->SetupPerGameSettings();

	SplashScreen::Open();
	CmdLineArgs::ReadArguments();

	Logger logger;

	EntryApp->PreInitialize();

	InspectorView::Open();
	HierarchyView::Open();

	//SplashScreen::AddMessage(L"Starting Application...");
	EntryApp->Initialize();


	MSG msg = { 0 };
	while (msg.message != WM_QUIT) {
		// ?�도??메시지가 ??경우 처리
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {
			EntryApp->Update();
			InspectorView::Update();
		}
	}

	EntryApp->Release();

	PostQuitMessage(0);

	return 0;
}