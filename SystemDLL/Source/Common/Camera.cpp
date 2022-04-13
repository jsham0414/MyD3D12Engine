#include "SystemDLL.h"

Camera* Camera::instance;

Camera::Camera() {
	instance = this;

	Initialize();
}

Camera::~Camera() {
}

VOID Camera::Initialize() {
	m_Eye = XMFLOAT3(0, 5, -5);
	m_At = XMFLOAT3(0, 0, 0);
	m_Up = XMFLOAT3(0, 1, 0);
}

VOID Camera::Update() {
	// Build the view matrix.
	XMVECTOR eye = XMLoadFloat3(&m_Eye);
	XMVECTOR at = XMLoadFloat3(&m_At);//XMVectorZero();// XMVectorSet(m_Position.x, m_Position.y, m_Position.z, 1.0f);
	XMVECTOR up = XMLoadFloat3(&m_Up);

	XMMATRIX view = XMMatrixLookAtLH(eye, at, up);
	XMStoreFloat4x4(&mView, view);

	XMMATRIX world = XMLoadFloat4x4(&mWorld);

	XMMATRIX proj = XMLoadFloat4x4(&Device::GetInstance()->Proj());
	XMMATRIX worldViewProj = world * view * proj;

	// Update the constant buffer with the latest worldViewProj matrix.
	ObjectConstants objConstants;
	XMStoreFloat4x4(&objConstants.WorldViewProj, XMMatrixTranspose(worldViewProj));
	Device::GetInstance()->GetObjectCB()->CopyData(0, objConstants);
}

VOID Camera::Release() {
	return VOID();
}
