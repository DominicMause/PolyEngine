#pragma once
#include "RenderCommand.h"
#include "OrtographicCamera.h"
#include "Shader.h"

namespace PolyEngine
{

	class Renderer
	{
	public:
		static void BeginScene(OrtographicCamera& camera);
		static void EndScene();
		
		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& modelMatrix);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};

}