#include "SystemDLL.h"
#include "SystemFunc.h"

SYSTEM_DLL HRESULT InitDevice() {
	//return GET_SINGLE(Device)->InitDevice();
	return S_OK;
}

SYSTEM_DLL VOID SystemRelease() {
	
}

SYSTEM_DLL VOID BeginRender() {

}

SYSTEM_DLL VOID EndRender() {

}

SYSTEM_DLL ID3D12Device* GetDevice() {
	return nullptr;
}
