#include <PolyEngine.h>

class Sandbox : public PolyEngine::Application 
{
public: 
	Sandbox() 
	{

	}

	~Sandbox() 
	{

	}

};

PolyEngine::Application* PolyEngine::CreateApplication()
{
	return new Sandbox();
}