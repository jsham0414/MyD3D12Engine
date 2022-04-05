#include "SystemDLL.h"
#include "GUITextBox.h"
#include "../Engine/Inspector.h"

GUITextBox::GUITextBox(XMFLOAT3 pos, WSTRING text, HWND parent, DWORD flag)
	: GUILayout(pos, 100, 20) {
    m_Flag = flag;
	m_ParentHandle = parent;
}

GUITextBox::GUITextBox(HWND parent, PROPERTY* prop, DWORD flag) : GUILayout() {
    m_Flag = flag;
    m_ParentHandle = parent;

    m_hID = InspectorView::GetGUIID();

    m_Text = Factory<GUILabel>::CreateLabel(parent, XMFLOAT3(0, InspectorView::GetProperty()->size() * 25, 0), prop->Name, flag);
    m_Edit = Factory<GUIEdit>::CreateEdit(parent, XMFLOAT3(150, InspectorView::GetProperty()->size() * 25, 0), prop->ToString(), flag);
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
    m_Text->Progress();
    m_Edit->Progress();
}

VOID GUITextBox::Render(HDC hdc) {
    m_Text->Render(hdc);
    m_Edit->Render(hdc);
}

VOID GUITextBox::Release() {
	DestroyWindow(m_hWnd);
    SAFE_DELETE(m_Text);
    SAFE_DELETE(m_Edit);
}

VOID GUITextBox::ValueChanged() {
    // GUIEdit에 Function변수를 추가하여 람다식을 대입하고 그 람다식은 실행되었을 때 자동으로 세팅 된 변수에 값을 대입하는 기능을 추가해야 함.
    m_Edit->ValueChanged();
}