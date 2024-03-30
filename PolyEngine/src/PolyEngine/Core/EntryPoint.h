#pragma once
#include "PolyEngine/Core/Core.h"

#ifdef PE_PLATFORM_WINDOWS

extern PolyEngine::Application* PolyEngine::CreateApplication();

int main(int argc, char** argv) 
{
	PolyEngine::Log::Init();
	PE_PROFILE_BEGIN_SESSION("Startup", "PolyEngine-Profile-Starup.json");
	auto app = PolyEngine::CreateApplication();
	PE_PROFILE_END_SESSION();
	PE_PROFILE_BEGIN_SESSION("Runtime", "PolyEngine-Profile-Runtime.json");
	app->Run();
	PE_PROFILE_END_SESSION();
	PE_PROFILE_BEGIN_SESSION("Shutdown", "PolyEngine-Profile-Shutdown.json");
	delete app;
	PE_PROFILE_END_SESSION();
}

#endif