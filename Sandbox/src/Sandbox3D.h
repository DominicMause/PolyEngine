#pragma once
#include "PolyEngine.h"

using namespace PolyEngine;

class Sandbox3D : public Layer
{
public:
	Sandbox3D();
	virtual ~Sandbox3D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Event& event) override;
private:
	ShaderLibrary m_ShaderLibrary;
	Ref<VertexArray> m_SquareVertexArray;

	Ref<Texture2D> m_Texture;
	Ref<Texture2D> m_TextureUser;

	OrthographicCameraController m_CameraController;

	Timestep m_Ts = 0;

	glm::vec3 m_SquareColor = { 0.8f, 0.2f, 0.3f };
};