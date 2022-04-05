#pragma once

#include "Platform/WIN32/IApplication.h"
#include "Object/Box.h"

namespace SystemDLL {
	class SYSTEM_DLL Simulation : public Win32::IApplication, public Win32::Window {
	private:
		Box m_Box;
	public:
		Simulation();
		~Simulation();

		virtual VOID PreInitialize() override;
		virtual VOID Update() override;
		VOID OnResize();
		VOID Render();
		virtual VOID Release()PURE;
		LRESULT MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	};
}