#pragma once

class SYSTEM_DLL GameObject {
public:
	GameObject() {};
	~GameObject() {};
public:
	VOID Initialize();
	VOID Update();
	VOID Render();
	VOID Release();
	void BuildBoxGeometry();
private:
	std::unique_ptr<MeshGeometry> mBoxGeo = nullptr;

	XMFLOAT4X4 mWorld = MathHelper::Identity4x4();
	XMFLOAT4X4 mView = MathHelper::Identity4x4();
	XMFLOAT4X4 mProj = MathHelper::Identity4x4();

	float mTheta = 1.5f * XM_PI;
	float mPhi = XM_PIDIV4;
	float mRadius = 5.0f;

	WSTRING m_Name = L"Box";
public:
	MeshGeometry* GetGeometry() { return mBoxGeo.get(); }

	WSTRING GetName() { return m_Name; }
};