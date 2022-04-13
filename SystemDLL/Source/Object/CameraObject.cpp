#include "SystemDLL.h"
#include "CameraObject.h"

CameraObject::CameraObject() {
	Initialize();
}

CameraObject::~CameraObject() {
	Release();
}

VOID CameraObject::Initialize() {
	m_Camera = new Camera();
}

VOID CameraObject::Update() {
	m_Camera->Update();
}

VOID CameraObject::Render() {

}

VOID CameraObject::Release() {
	if (m_Camera != nullptr) {
		m_Camera->Release();
		SAFE_DELETE(m_Camera);
	}
}
