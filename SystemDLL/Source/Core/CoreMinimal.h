#pragma once

#include "CoreDefinitions.h"

#include "Engine/OEngine.h"

#include "Common/Logger.h"
#include "Common/Time.h"
#include "Core/PerGameSettings.h"
#include "D3D12/MathHelper.h"
#include "D3D12/d3dUtil.h"
#include "D3D12/Device.h"
#include "Property/GUILayout.h"
#include "Common/Factory.h"

#include "Manager/ObjectManager.h"

#ifdef WIN32

#include "Platform/WIN32/Win32Utils.h"
#include "Platform/WIN32/Win32Caption.h"
#include "Platform/WIN32/SubObject.h"
#include "Platform/WIN32/Window.h"
#include "Platform/WIN32/IApplication.h"

#endif
