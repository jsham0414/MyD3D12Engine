#pragma once

#define ENTRY_APP(x) Win32::IApplication* EntryApplication() { return new x; }

namespace Win32 {
	class SYSTEM_DLL IApplication {
		// Application
	public:
		IApplication();
		virtual ~IApplication() {};

	public:
		// 게임 초기 변수 세팅
		virtual VOID SetupPerGameSettings()PURE;
		virtual VOID PreInitialize()PURE;
		virtual VOID Initialize()PURE;
		virtual VOID Update()PURE;

	};

	IApplication* EntryApplication();
}
