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
    m_Property = prop;

    m_Text = Factory<GUILabel>::CreateLabel(parent, XMFLOAT3(0, InspectorView::GetGUILayout()->size() * 25, 0), prop->Name, flag);
    m_Edit = Factory<GUIEdit>::CreateEdit(parent, XMFLOAT3(150, InspectorView::GetGUILayout()->size() * 25, 0), prop->ToString(), flag);
    m_Edit->Property(prop);
}

GUITextBox::~GUITextBox() {
	Release();
}

VOID GUITextBox::PreInitialize() {
}

VOID GUITextBox::Initialize() {
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
    m_Edit->ValueChanged();
}