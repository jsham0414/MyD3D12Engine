#include "SystemDLL.h"
#include "GUILabel.h"

GUILabel::GUILabel(XMFLOAT3 pos, INT width, INT height, WSTRING text, DWORD flag) 
	: GUILayout(pos, width, height) {
	m_Text = text;
	m_Flag = flag;
}

GUILabel::~GUILabel() {
}

VOID GUILabel::PreInitialize() {
	return VOID();
}

VOID GUILabel::Initialize() {
}

VOID GUILabel::Progress() {

}

VOID GUILabel::Render(HDC hdc) {
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255));
	SetTextAlign(hdc, TA_LEFT);

	RECT rc = { m_Position.x, m_Position.y, m_Position.x + m_Width, m_Position.y + m_Height };
	DrawText(hdc, m_Text.c_str(), wcslen(m_Text.c_str()), &rc, m_Flag);
}

VOID GUILabel::Release() {

}
