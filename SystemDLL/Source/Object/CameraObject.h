#pragma once

class SYSTEM_DLL CameraObject : public GameObject {
public:
	CameraObject();
	~CameraObject();
public:
	VOID Initialize();
	VOID Update();
	VOID Render();
	VOID Release();
private:
	Camera* m_Camera;

	XMFLOAT4X4 mWorld = MathHelper::Identity4x4();
	XMFLOAT4X4 mView = MathHelper::Identity4x4();
	XMFLOAT4X4 mProj = MathHelper::Identity4x4();
public:
	Camera* GetCamera() { return m_Camera; }
};