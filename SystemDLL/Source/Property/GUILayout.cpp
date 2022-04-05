#include "SystemDLL.h"

GUILayout::GUILayout(XMFLOAT3 pos, INT width, INT height) 
	: m_Position(pos), m_Width(width), m_Height(height) {
}

GUILayout::GUILayout() : m_Width(100), m_Height(20) {
}

GUILayout::~GUILayout() {
}