#pragma once
#include "Engine/Simulation.h"

class Application : public SystemDLL::Simulation {
	// Application
public:
	Application();
	~Application();
	
public:
	VOID SetupPerGameSettings();
	VOID Initialize();
	VOID Update();

};