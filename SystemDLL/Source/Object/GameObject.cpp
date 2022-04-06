#include "SystemDLL.h"
#include "GameObject.h"
#include "Engine/Inspector.h"
#include "Property/GUILabel.h"
#include "Property/GUITextBox.h"
#include "Property/GUIVector3.h"

using Microsoft::WRL::ComPtr;
using namespace DirectX;
using namespace DirectX::PackedVector;
using namespace Win32::Utils;

struct Vertex {
	XMFLOAT3 Pos;
	XMFLOAT4 Color;
};

VOID GameObject::Initialize() {
	m_Position = new XMFLOAT3(0, 0, 0);

	BuildBoxGeometry();
}

VOID GameObject::Update() {
	// Convert Spherical to Cartesian coordinates.
	float x = mRadius * sinf(mPhi) * cosf(mTheta);
	float z = mRadius * sinf(mPhi) * sinf(mTheta);
	float y = mRadius * cosf(mPhi);

	// Build the view matrix.
	XMVECTOR pos = XMVectorSet(x, y, z, 1.0f);
	XMVECTOR target = XMVectorSet(m_Position->x, m_Position->y, m_Position->z, 1.0f);
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMMATRIX view = XMMatrixLookAtLH(pos, target, up);
	XMStoreFloat4x4(&mView, view);

	XMMATRIX world = XMLoadFloat4x4(&mWorld);
	XMMATRIX proj = XMLoadFloat4x4(&Device::GetInstance()->Proj());
	XMMATRIX worldViewProj = world * view * proj;

	// Update the constant buffer with the latest worldViewProj matrix.
	ObjectConstants objConstants;
	XMStoreFloat4x4(&objConstants.WorldViewProj, XMMatrixTranspose(worldViewProj));
	Device::GetInstance()->GetObjectCB()->CopyData(0, objConstants);
}

VOID GameObject::Render() {
	Device::GetInstance()->GetCommandList()->IASetVertexBuffers(0, 1, &mBoxGeo->VertexBufferView());
	Device::GetInstance()->GetCommandList()->IASetIndexBuffer(&mBoxGeo->IndexBufferView());
	Device::GetInstance()->GetCommandList()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	Device::GetInstance()->GetCommandList()->DrawIndexedInstanced(
		mBoxGeo->DrawArgs["box"].IndexCount,
		1, 0, 0, 0);
}

VOID GameObject::Release() {
	return VOID();
}

void GameObject::BuildBoxGeometry() {
	Device::GetInstance()->ResetCommendList();

	std::array<Vertex, 8> vertices =
	{
		Vertex({ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(Colors::White) }),
		Vertex({ XMFLOAT3(-1.0f, +1.0f, -1.0f), XMFLOAT4(Colors::Black) }),
		Vertex({ XMFLOAT3(+1.0f, +1.0f, -1.0f), XMFLOAT4(Colors::Red) }),
		Vertex({ XMFLOAT3(+1.0f, -1.0f, -1.0f), XMFLOAT4(Colors::Green) }),
		Vertex({ XMFLOAT3(-1.0f, -1.0f, +1.0f), XMFLOAT4(Colors::Blue) }),
		Vertex({ XMFLOAT3(-1.0f, +1.0f, +1.0f), XMFLOAT4(Colors::Yellow) }),
		Vertex({ XMFLOAT3(+1.0f, +1.0f, +1.0f), XMFLOAT4(Colors::Cyan) }),
		Vertex({ XMFLOAT3(+1.0f, -1.0f, +1.0f), XMFLOAT4(Colors::Magenta) })
	};

	std::array<std::uint16_t, 36> indices =
	{
		// front face
		0, 1, 2,
		0, 2, 3,

		// back face
		4, 6, 5,
		4, 7, 6,

		// left face
		4, 5, 1,
		4, 1, 0,

		// right face
		3, 2, 6,
		3, 6, 7,

		// top face
		1, 5, 6,
		1, 6, 2,

		// bottom face
		4, 0, 3,
		4, 3, 7
	};

	const UINT vbByteSize = (UINT)vertices.size() * sizeof(Vertex);
	const UINT ibByteSize = (UINT)indices.size() * sizeof(std::uint16_t);

	mBoxGeo = std::make_unique<MeshGeometry>();
	mBoxGeo->Name = "boxGeo";

	ThrowIfFailed(D3DCreateBlob(vbByteSize, &mBoxGeo->VertexBufferCPU));
	CopyMemory(mBoxGeo->VertexBufferCPU->GetBufferPointer(), vertices.data(), vbByteSize);

	ThrowIfFailed(D3DCreateBlob(ibByteSize, &mBoxGeo->IndexBufferCPU));
	CopyMemory(mBoxGeo->IndexBufferCPU->GetBufferPointer(), indices.data(), ibByteSize);

	mBoxGeo->VertexBufferGPU = d3dUtil::CreateDefaultBuffer(Device::GetInstance()->GetDevice(),
		Device::GetInstance()->GetCommandList(), vertices.data(), vbByteSize, mBoxGeo->VertexBufferUploader);

	mBoxGeo->IndexBufferGPU = d3dUtil::CreateDefaultBuffer(Device::GetInstance()->GetDevice(),
		Device::GetInstance()->GetCommandList(), indices.data(), ibByteSize, mBoxGeo->IndexBufferUploader);

	mBoxGeo->VertexByteStride = sizeof(Vertex);
	mBoxGeo->VertexBufferByteSize = vbByteSize;
	mBoxGeo->IndexFormat = DXGI_FORMAT_R16_UINT;
	mBoxGeo->IndexBufferByteSize = ibByteSize;

	SubmeshGeometry submesh;
	submesh.IndexCount = (UINT)indices.size();
	submesh.StartIndexLocation = 0;
	submesh.BaseVertexLocation = 0;

	mBoxGeo->DrawArgs["box"] = submesh;

	Device::GetInstance()->ExcuteCommendList();
}

VOID GameObject::LoadProperties(HWND hWnd) {
	InspectorView::AddProperty(Factory<GUITextBox>::CreateGUITextbox(hWnd, CREATE_PROPERTY(PrimitiveType::FLOAT, m_Position->x), GUI_NUMONLY));
	InspectorView::AddProperty(Factory<GUITextBox>::CreateGUITextbox(hWnd, CREATE_PROPERTY(PrimitiveType::FLOAT, m_Position->y), GUI_NUMONLY));
	InspectorView::AddProperty(Factory<GUITextBox>::CreateGUITextbox(hWnd, CREATE_PROPERTY(PrimitiveType::FLOAT, m_Position->z), GUI_NUMONLY));
}