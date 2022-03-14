#include "SystemDLL.h"
#include "IApplication.h"
#include "Common/CmdLineArgs.h"

extern Win32::IApplication* EntryApplication();

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, INT) {
	auto EntryApp = EntryApplication();

	PerGameSettings GameSettings;
	EntryApp->SetupPerGameSettings();

	CmdLineArgs::ReadArguments();

	Logger logger;

	EntryApp->PreInitialize();

	//SplashScreen::AddMessage(L"Starting Application...");
	EntryApp->Initialize();


	MSG msg = { 0 };
	while (msg.message != WM_QUIT) {
		// 윈도우 메시지가 올 경우 처리
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {
			EntryApp->Update();
		}
	}

	PostQuitMessage(0);

	return 0;
}