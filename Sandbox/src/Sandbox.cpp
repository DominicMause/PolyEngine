#include <PolyEngine.h>
#include <PolyEngine/Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "Sandbox3D.h"

class Sandbox : public PolyEngine::Application
{
public: 
	Sandbox() 
	{
		//PushLayer(new Sandbox3D());
		PushLayer(new Sandbox2D());
	}

	~Sandbox() 
	{

	}

};

PolyEngine::Application* PolyEngine::CreateApplication()
{
	return new Sandbox();
}