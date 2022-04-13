#pragma once 

class Camera {
private:
	static Camera* instance;
public:
	static Camera* GetInstance() { return instance; }

public:
	Camera();
	~Camera();

public:
	VOID Initialize();
	VOID Update();
	VOID Release();

public:
	XMFLOAT3 m_Eye;
	XMFLOAT3 m_At;
	XMFLOAT3 m_Up;

	XMFLOAT4X4 mWorld;
	XMFLOAT4X4 mView;
	XMFLOAT4X4 mProj;

};