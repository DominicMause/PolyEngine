#pragma once
#include "Core.h"

namespace PolyEngine {

	class POLY_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application* CreateApplication();

}
