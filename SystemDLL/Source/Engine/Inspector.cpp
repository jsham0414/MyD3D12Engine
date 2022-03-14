#include "SystemDLL.h"
#include "Inspector.h"

namespace InspectorView {
	Inspector* m_pInspectorWindow;

	VOID SYSTEM_DLL InspectorView::Open() {
		if (m_pInspectorWindow != nullptr) {
			return;
		}

		m_pInspectorWindow = new Inspector();
	}

	VOID SYSTEM_DLL InspectorView::Close() {
		if (!m_pInspectorWindow)
			return;

		DestroyWindow(m_pInspectorWindow->Handle());
		SAFE_DELETE(m_pInspectorWindow);
	}
}

Inspector::Inspector() : Window(L"Inspector", NULL) {
	m_Flags = WF_NOTUSECAPTION;

	Size(300, 600);
	m_PaintOverride = true;

	Win32::Window::RegisterNewClass();
	Win32::Window::Initialize();

}

Inspector::~Inspector() {
}

LRESULT Inspector::MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {

	}

	return Window::MessageHandler(hWnd, msg, wParam, lParam);
}