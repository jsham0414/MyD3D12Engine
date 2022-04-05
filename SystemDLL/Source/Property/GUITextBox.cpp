#include "SystemDLL.h"
#include "GUITextBox.h"
#include "../Engine/Inspector.h"

GUITextBox::GUITextBox(XMFLOAT3 pos, WSTRING text, HWND parent, DWORD flag)
	: GUILayout(pos, 100, 20) {
    m_Flag = flag;
	m_ParentHandle = parent;
}

GUITextBox::GUITextBox(HWND parent, PROPERTY* prop, DWORD flag) : GUILayout() {
    m_Text = Factory<GUILabel>::CreateLabel(parent, prop->Name, flag);
}

GUITextBox::~GUITextBox() {
	Release();
}

VOID GUITextBox::PreInitialize() {
    return VOID();
}

VOID GUITextBox::Initialize() {
    // GUILabel과 GUIEdit을 합쳐서 만들 것, 하나로 만들지 말 것

    //m_Text = Factory<GUILabel>::CreateLabel
}

VOID GUITextBox::Progress() {
    if (m_Flag & GUI_NUMONLY) {
        NumberCheck();
    }
}

VOID GUITextBox::Render(HDC hdc) {
    switch (m_Property->Type) {
    case PrimitiveType::FLOAT:
        SetBkMode(hdc, TRANSPARENT);
        SetTextColor(hdc, RGB(255, 255, 255));
        SetTextAlign(hdc, TA_LEFT);

        TextOut(hdc, m_Position.x, m_Position.y + 2, m_Property->Name, wcslen(m_Property->Name));
        break;
    }
}

VOID GUITextBox::Release() {
	DestroyWindow(m_hWnd);
}

VOID GUITextBox::NumberCheck() {
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
        SetWindowText(Handle(), m_LastGood.c_str());
        Edit_SetSel(Handle(), m_LOCaret, m_HICaret); // SendMessage(Handle(), EM_SETSEL, m_LOCaret, m_HICaret);
        MessageBeep(MB_OK);
    } else {
        m_LastGood = wstr.c_str();
        m_LOCaret = LOWORD(Edit_GetSel(Handle())); // LOWORD(SendMessage(Handle(), EM_GETSEL, NULL, NULL)); 와 같다
        m_HICaret = HIWORD(Edit_GetSel(Handle()));
    }
}
