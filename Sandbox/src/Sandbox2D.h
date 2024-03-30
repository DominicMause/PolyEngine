#pragma once
#include "PolyEngine.h"
#include "Entity.h"
#include "Player.h"

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
	bool OnWindowResized(WindowResizeEvent& e);
	bool OnKeyPressed(KeyPressedEvent& e);
private:
	//OrthographicCameraController m_CameraController;
	OrthographicCamera m_Camera;
	Ref<VertexArray> m_VertexArray;
	Ref<Shader> m_Shader;

	Ref<Texture2D> m_Texture;
	Ref<Texture2D> m_TextureBG;
	Ref<Texture2D> m_TexturePlayer;

	std::vector<Entity> m_Entities;
	Player m_Player;
};