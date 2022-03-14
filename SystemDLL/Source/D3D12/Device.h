#pragma once
#include "UploadBuffer.h"
#include <DirectXMath.h>

using namespace Microsoft::WRL;
using namespace DirectX;

struct ObjectConstants {
    XMFLOAT4X4 WorldViewProj = MathHelper::Identity4x4();
};

class SYSTEM_DLL Device {
private:
    static Device* instance;
public:
    static Device* GetInstance() { 
        if (instance == nullptr)
            instance = new Device();
        return instance;
    }
private:
    Device();
public:
    ~Device();
public:
    virtual void CreateRtvAndDsvDescriptorHeaps();

	HRESULT InitDevice(HWND hWnd);

    VOID Initialize();

    VOID ResetCommendList();

    VOID ExcuteCommendList();

    void BuildBoxGeometry();

    VOID BeginRender();
    VOID EndRender();

    void BuildConstantBuffers();

    void BuildDescriptorHeaps();

    VOID BuildRootSignature();

    VOID BuildShadersAndInputLayout();

    VOID BuildPSO();

    void GetHardwareAdapter(IDXGIFactory2* pFactory, IDXGIAdapter1** ppOutAdapter);
    virtual void OnResize();
    HINSTANCE AppInst() const;
    HWND MainWnd() const;
    float AspectRatio() const;
    bool Get4xMsaaState() const;
    void Set4xMsaaState(bool value);
    void CreateSwapChain();
    void CreateCommandObjects();

    void FlushCommandQueue();

    ID3D12Resource* CurrentBackBuffer()const;
    D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferView()const;
    D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView()const;
private:
    ComPtr<IDXGIFactory4> m_dxgiFactory;
    ComPtr<IDXGISwapChain> m_SwapChain;
    ComPtr<ID3D12Device> m_Device;
    ComPtr<ID3D12Fence> m_Fence;

    std::unique_ptr<UploadBuffer<ObjectConstants>> m_ObjectCB = nullptr;

    HINSTANCE m_hAppInst = nullptr; // application instance handle
    HWND      m_hWnd = nullptr; // main window handle
    bool      m_AppPaused = false;  // is the application paused?
    bool      m_Minimized = false;  // is the application minimized?
    bool      m_Maximized = false;  // is the application maximized?
    bool      m_Resizing = false;   // are the resize bars being dragged?
    bool      m_FullscreenState = false;// fullscreen enabled

    // Set true to use 4X MSAA (�4.1.8).  The default is false.
    bool      m_4xMsaaState = false;    // 4X MSAA enabled
    UINT      m_4xMsaaQuality = 0;      // quality level of 4X MSAA

    UINT64 m_CurrentFence = 0;

    ComPtr<ID3D12CommandQueue> m_CommandQueue;
    ComPtr<ID3D12CommandAllocator> m_DirectCmdListAlloc;
    ComPtr<ID3D12GraphicsCommandList> m_CommandList;

    static const int SwapChainBufferCount = 2;
    int m_CurrBackBuffer = 0;
    ComPtr<ID3D12Resource> m_SwapChainBuffer[SwapChainBufferCount];
    ComPtr<ID3D12Resource> m_DepthStencilBuffer;

    ComPtr<ID3DBlob> m_vsByteCode = nullptr;
    ComPtr<ID3DBlob> m_psByteCode = nullptr;

    ComPtr<ID3D12RootSignature> m_RootSignature = nullptr;
    ComPtr<ID3D12DescriptorHeap> m_CbvHeap = nullptr;
    ComPtr<ID3D12DescriptorHeap> m_RtvHeap;
    ComPtr<ID3D12DescriptorHeap> m_DsvHeap;

    std::vector<D3D12_INPUT_ELEMENT_DESC> m_InputLayout;

    ComPtr<ID3D12PipelineState> m_PSO = nullptr;

    D3D12_VIEWPORT m_ScreenViewport;
    D3D12_RECT m_ScissorRect;

    UINT m_RtvDescriptorSize = 0;
    UINT m_DsvDescriptorSize = 0;
    UINT m_CbvSrvUavDescriptorSize = 0;

    // Derived class should set these in derived constructor to customize starting values.
    WSTRING m_MainWndCaption = L"d3d App";
    D3D_DRIVER_TYPE m_d3dDriverType = D3D_DRIVER_TYPE_HARDWARE;
    DXGI_FORMAT m_BackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
    DXGI_FORMAT m_DepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
    int m_ClientWidth = 800;
    int m_ClientHeight = 600;


    XMFLOAT4X4 mWorld = MathHelper::Identity4x4();
    XMFLOAT4X4 mView = MathHelper::Identity4x4();
    XMFLOAT4X4 mProj = MathHelper::Identity4x4();

    float mTheta = 1.5f * XM_PI;
    float mPhi = XM_PIDIV4;
    float mRadius = 5.0f;
    std::unique_ptr<MeshGeometry> mBoxGeo = nullptr;

    XMFLOAT4X4 m_Proj;

public:
    ID3D12Device* GetDevice() { return m_Device.Get(); }
    ID3D12GraphicsCommandList* GetCommandList();
    UploadBuffer<ObjectConstants>* GetObjectCB() { return m_ObjectCB.get(); }
    const XMFLOAT4X4 Proj() { return m_Proj; }
};