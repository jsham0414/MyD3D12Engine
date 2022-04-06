#include "SystemDLL.h"
#include "Simulation.h"
#include "Engine/SplashScreen.h"

using namespace DirectX;

namespace SystemDLL {

	Simulation::Simulation() : Win32::Window(L"MainApplication", NULL) {
		
	}

	Simulation::~Simulation() {

	}

	VOID Simulation::PreInitialize() {
		Logger::PrintLog(L"Game Name : %s\n", PerGameSettings::GameName());
		Logger::PrintLog(L"Boot Time : %s\n", Time::GetDateTimeString().c_str());
		Logger::PrintLog(L"Engine Mode : %s\n", Engine::EngineModeToString().c_str());

		Win32::Window::RegisterNewClass();
		Win32::Window::Initialize();

		if (FAILED(Device::GetInstance()->InitDevice(Handle()))) {
			Logger::GetInstance()->PrintLog(L"D3D12 초기???�패");
			return;
		}

		ObjectManager::GetInstance()->AddObject(Factory<GameObject>::CreateInstance());
		ObjectManager::GetInstance()->AddObject(Factory<GameObject>::CreateInstance());
		//ObjectManager::GetInstance()->AddObject(Factory<GameObject, GameObject>::CreateInstance());
		//ObjectManager::GetInstance()->AddObject(Factory<GameObject, GameObject>::CreateInstance());

		SplashScreen::Close();
	}

	VOID Simulation::Update() {
		ObjectManager::GetInstance()->Update();

		Render();
	}

	VOID Simulation::OnResize() {
		if (Device::GetInstance()->GetDevice()) {
			Device::GetInstance()->OnResize();
		}
	}

	VOID Simulation::Render() {
		Device::GetInstance()->BeginRender();
		ObjectManager::GetInstance()->Render();
		Device::GetInstance()->EndRender();
	}

	VOID Simulation::Release() {
	}


	LRESULT Simulation::MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		switch (msg) {
		case WM_SIZE:
			OnResize();
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}

		return Window::MessageHandler(hWnd, msg, wParam, lParam);
	}
}