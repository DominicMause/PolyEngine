#pragma once
#include "PolyEngine/Core/Core.h"

#ifdef PE_PLATFORM_WINDOWS

extern PolyEngine::Application* PolyEngine::CreateApplication();

int main(int argc, char** argv) 
{
	PolyEngine::Log::Init();

	PE_CORE_WARN("Ready");

	auto app = PolyEngine::CreateApplication();
	app->Run();
	delete app;
}

#endif