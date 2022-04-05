#pragma once

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#ifdef WIN32
#include <windows.h>
#include <windowsx.h>
#include <wrl.h>
#endif

#include <string> 
#include <algorithm> 
#include <list>
#include <cassert>
#include <vector>
#include <memory>

#include <dxgi1_4.h>
#include <d3d12.h>

#include <DirectXColors.h>
#include <D3D12/MathHelper.h>
#include <DirectXMath.h>

#include "Core/Core.h"