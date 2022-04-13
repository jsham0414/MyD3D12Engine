#pragma once

class SYSTEM_DLL GameObject {
public:
	GameObject() {};
	~GameObject() {};
public:
	VOID Initialize();
	VOID Update();
	VOID Render(int iIdx);
	VOID Release();

	VOID BuildBoxGeometry();
	VOID BuildConstantBuffers();
	virtual VOID LoadProperties(HWND hWnd);
private:
	std::unique_ptr<UploadBuffer<ObjectConstants>> mObjectCB = nullptr;
	std::unique_ptr<MeshGeometry> mBoxGeo = nullptr;
	std::vector<PROPERTY*> m_Property;

	//XMFLOAT3* m_Position;
	XMFLOAT3 m_Position;
	XMFLOAT4X4 mWorld = MathHelper::Identity4x4();
	XMFLOAT4X4 mView = MathHelper::Identity4x4();
	XMFLOAT4X4 mProj = MathHelper::Identity4x4();

	float mTheta = 1.5f * XM_PI;
	float mPhi = XM_PIDIV4;
	float mRadius = 5.0f;

	INT m_Index;

	WSTRING m_Name = L"Box";
public:
	MeshGeometry* GetGeometry() { return mBoxGeo.get(); }

	WSTRING GetName() { return m_Name; }
	VOID Position(XMFLOAT3 pos) { m_Position = pos; }
};