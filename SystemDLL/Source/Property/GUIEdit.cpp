#include "SystemDLL.h"
#include "GUIEdit.h"
#include "../Engine/Inspector.h"


GUIEdit::GUIEdit(HWND parent, XMFLOAT3 pos, WSTRING text, DWORD flag) : GUILayout() {
    m_Flag = flag;
    m_hID = InspectorView::GetGUIID();

    m_Position = XMFLOAT3(pos.x, pos.y, pos.z);
    m_Text = text;
    m_hWnd = CreateWindowEx(NULL, L"Edit", text.c_str(), WS_CHILD | WS_VISIBLE | WS_BORDER, m_Position.x, m_Position.y, m_Width, m_Height, parent, m_hID, NULL, NULL);
}

GUIEdit::~GUIEdit() {
    Release();
}

VOID GUIEdit::PreInitialize() {
    return VOID();
}

VOID GUIEdit::Initialize() {
    m_hID = InspectorView::GetGUIID();

    WSTRING value = L"";
    switch (m_Property->Type) {
    case PrimitiveType::FLOAT:
        float* fvalue = reinterpret_cast<float*>(m_Property->Data);
        value = std::to_wstring(*fvalue);
        break;
    }
    m_hWnd = CreateWindowEx(NULL, L"Edit", value.c_str(), WS_CHILD | WS_VISIBLE | WS_BORDER, m_Position.x + 80, m_Position.y, m_Width, m_Height, ParentHandle(), m_hID, NULL, NULL);
}

VOID GUIEdit::Progress() {
    if (m_Flag & GUI_NUMONLY) {
        NumberCheck();
    }
}

VOID GUIEdit::Render(HDC hdc) {
    //TextOut(hdc, m_Position.x, m_Position.y + 2, m_Text.c_str(), wcslen(m_Text.c_str()));
}

VOID GUIEdit::Release() {
    DestroyWindow(m_hWnd);
}

VOID GUIEdit::ValueChanged() {

}

VOID GUIEdit::NumberCheck() {
    WCHAR str[256];

    GetWindowText(Handle(), str, _countof(str));

    WSTRING wstr(str);

    LPWSTR pBuff = str;

    bool bProblem = false;
    bool bDecimalPoint = false;

    for (int indx = 0; indx < wstr.length(); indx++) {
        char nChar = str[indx];

        if (((nChar >= '0') && (nChar <= '9')) ||
            nChar == 46 ||
            (nChar == '-' && indx == 0)) {
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
        SetWindowText(Handle(), m_Text.c_str());
        Edit_SetSel(Handle(), m_LOCaret, m_HICaret);
        MessageBeep(MB_OK);
    } else {
        m_Text = wstr.c_str();
        m_LOCaret = LOWORD(Edit_GetSel(Handle())); 
        m_HICaret = HIWORD(Edit_GetSel(Handle()));
    }
}
