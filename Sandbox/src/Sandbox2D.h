#pragma once
#include "PolyEngine.h"

using namespace PolyEngine;

class Sandbox2D : public Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Event& event) override;
private:
	OrthographicCameraController m_CameraController;

	Ref<VertexArray> m_VertexArray;
	Ref<Shader> m_Shader;

	int m_Grid[2] = {2, 2};
	float m_Rotation = 0;
	float m_Spacing = 1.11f;

	glm::vec4 m_SquareColor = { 0.8f, 0.2f, 0.3f, 1.0f };
};