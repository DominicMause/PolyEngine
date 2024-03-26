#include <PolyEngine.h>
#include "imgui/imgui.h"
#include <string>
#include <iostream>

using namespace PolyEngine;

class ExampleLayer : public Layer
{
public:
	ExampleLayer()
		:Layer("Example"){}

	void OnUpdate() override
	{
		
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("MousePos");
		auto [x, y] = Input::GetMousePosition();
		std::ostringstream stream;
		stream << x << ", " << y;
		ImGui::Text(stream.str().c_str());
		ImGui::End();
	}

	void OnEvent(PolyEngine::Event& event)
	{
		
	}

};

class Sandbox : public Application 
{
public: 
	Sandbox() 
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox() 
	{

	}

};

PolyEngine::Application* PolyEngine::CreateApplication()
{
	return new Sandbox();
}