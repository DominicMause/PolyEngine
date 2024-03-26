#include <PolyEngine.h>

class ExampleLayer : public PolyEngine::Layer
{
public:
	ExampleLayer()
		:Layer("Example"){}

	void OnUpdate() override
	{
		PE_INFO("Layer ({0}): Update", GetName());
	}

	void OnEvent(PolyEngine::Event& event)
	{
		PE_TRACE("{0}", event);
	}
};

class Sandbox : public PolyEngine::Application 
{
public: 
	Sandbox() 
	{
		PushOverlay(new PolyEngine::ImGuiLayer());
	}

	~Sandbox() 
	{

	}

};

PolyEngine::Application* PolyEngine::CreateApplication()
{
	return new Sandbox();
}