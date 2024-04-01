#pragma once
#include "OrthographicCamera.h"
#include "Texture.h"

namespace PolyEngine
{
	struct RenderProps
	{
		glm::vec3 Position = {0,0,0};
		glm::vec2 Size = { 1,1 };
		float Rotation = 0;
		Ref<Texture2D> Texture;
		float TilingFactor= 1.0f;
		glm::vec4 Color = { 1.0f, 1.0f, 1.0f, 1.0f };
	};

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();
		static void Flush();

		// Primitives
		static void DrawQuad(const RenderProps& renderProps);
	private:
		static void DrawRotatedQuad(const RenderProps& renderProps);
		static void DrawNormalQuad(const RenderProps& renderProps);
	};
}