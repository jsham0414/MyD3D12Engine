#include "SystemDLL.h"
#include "GUIVector3.h"
#include "../Engine/Inspector.h"
#include <cstring>

GUIVector3::GUIVector3(XMFLOAT3 pos, INT width, INT height, HWND parent, DWORD flag)
    : GUILayout(pos, width, height) {
    m_Flag = flag;
    m_ParentHandle = parent;
    Initialize();
}

GUIVector3::~GUIVector3() {
    Release();
}

VOID GUIVector3::PreInitialize() {
    return VOID();
}

VOID GUIVector3::Initialize() {
    m_hID = InspectorView::GetGUIID();

    m_hWnd = CreateWindowEx(NULL, L"Edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER, m_Position.x, m_Position.y, m_Width, m_Height, ParentHandle(), m_hID, NULL, NULL);
}

VOID GUIVector3::Progress() {
    if (m_Flag & GUI_NUMONLY) {
        NumberCheck();
    }
}

VOID GUIVector3::Render(HDC hdc) {
    return VOID();
}

VOID GUIVector3::Release() {
    DestroyWindow(m_hWnd);
}

VOID GUIVector3::NumberCheck() {
    WCHAR str[256];

    GetWindowText(Handle(), str, _countof(str));

    WSTRING wstr(str);

    LPWSTR pBuff = str;

    bool bProblem = false;
    bool bDecimalPoint = false;

    for (int indx = 0; indx < wstr.length(); indx++) {
        char nChar = str[indx];

        if (((nChar >= '0') && (nChar <= '9')) ||
            nChar == 46) {
        } else {
            if (nChar == '.' && indx > 0 && !bDecimalPoint) {
                bDecimalPoint = true;
            } else {
                bProblem = true;
                break;
            }
        }
    }

    if (bProblem) {
        SetWindowText(Handle(), m_LastGood.c_str());
        Edit_SetSel(Handle(), m_LOCaret, m_HICaret); // SendMessage(Handle(), EM_SETSEL, m_LOCaret, m_HICaret);
        MessageBeep(MB_OK);
    } else {
        m_LastGood = wstr.c_str();
        m_LOCaret = LOWORD(Edit_GetSel(Handle())); // LOWORD(SendMessage(Handle(), EM_GETSEL, NULL, NULL)); ¿Í °°´Ù
        m_HICaret = HIWORD(Edit_GetSel(Handle()));
    }
}
