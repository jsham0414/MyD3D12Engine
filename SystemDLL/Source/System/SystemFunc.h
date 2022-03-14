#pragma once
//#define BUILD_DLL

SYSTEM_DLL HRESULT InitDevice();

SYSTEM_DLL VOID SystemRelease();
SYSTEM_DLL VOID BeginRender();
SYSTEM_DLL VOID EndRender();

SYSTEM_DLL ID3D12Device* GetDevice();
