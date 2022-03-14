#pragma once

namespace Win32 {
	class SYSTEM_DLL SubObject {
	public:
		SubObject(WSTRING wsName, WSTRING wsTitle, HICON hIcon);
		virtual ~SubObject();
	public:
		virtual VOID RegisterNewClass();
		virtual VOID Initialize() PURE;

	protected:
		static LRESULT CALLBACK SetupMessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static LRESULT AssignMessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		virtual LRESULT MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	protected:
		WSTRING m_Name;
		WSTRING m_Title;
		HICON m_hIcon;

		HWND m_hWnd;

	public:
		HWND Handle() { return m_hWnd; }

	public:
		VOID Handle(HWND hWnd) { m_hWnd = hWnd; }
	};
}