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
    // GUILabel�� GUIEdit�� ���ļ� ���� ��, �ϳ��� ������ �� ��

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
    // GUIEdit�� Function������ �߰��Ͽ� ���ٽ��� �����ϰ� �� ���ٽ��� ����Ǿ��� �� �ڵ����� ���� �� ������ ���� �����ϴ� ����� �߰��ؾ� ��.
    m_Edit->ValueChanged();
}