#include "SystemDLL.h"
#include "SubObject.h"

namespace Win32 {
	SubObject::SubObject(WSTRING wsName, WSTRING wsTitle, HICON hIcon) : m_Name(wsName), m_Title(wsTitle), m_hIcon(hIcon), m_hWnd(NULL) {

	}

	SubObject::~SubObject() {

	}

	VOID SubObject::RegisterNewClass() {
		WNDCLASSEX wcEx;
		wcEx.cbSize = sizeof(WNDCLASSEX);
		wcEx.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
		wcEx.cbClsExtra = 0;
		wcEx.cbWndExtra = 0;

		wcEx.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcEx.hbrBackground = (HBRUSH) (CreateSolidBrush(RGB(40, 40, 40)));

		wcEx.hIcon = m_hIcon;
		wcEx.hIconSm = m_hIcon;

		wcEx.lpszClassName = m_Name.c_str();

		wcEx.lpszMenuName = nullptr;

		wcEx.hInstance = hInstance();

		wcEx.lpfnWndProc = SetupMessageHandler;

		RegisterClassEx(&wcEx);
	}

	LRESULT SubObject::SetupMessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		if (msg == WM_NCCREATE) {
			const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
			Win32::SubObject* const pWnd = static_cast<Win32::SubObject*>(pCreate->lpCreateParams);
			SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
			SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Win32::SubObject::AssignMessageHandler));
			pWnd->Handle(hWnd);
			return pWnd->MessageHandler(hWnd, msg, wParam, lParam);
		}
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	LRESULT SubObject::AssignMessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		Win32::SubObject* const pWnd = reinterpret_cast<Win32::SubObject*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
		return pWnd->MessageHandler(hWnd, msg, wParam, lParam);
	}

	LRESULT SubObject::MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}
