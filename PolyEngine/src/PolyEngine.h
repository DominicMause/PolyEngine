#pragma once

// For use by PolyEngine applications

#include "PolyEngine/Core/Application.h"
#include "PolyEngine/Core/Layer.h"
#include "PolyEngine/Core/Log.h"
#include "PolyEngine/Core/Timestep.h"

#include "PolyEngine/Input/Input.h"
#include "PolyEngine/Input/KeyCodes.h"
#include "PolyEngine/Input/MouseCodes.h"
#include "PolyEngine/Input/OrthographicCameraController.h"

#include "PolyEngine/ImGui/ImGuiLayer.h"

// -- Renderer ----------------------------------------------
#include "PolyEngine/Renderer/Renderer.h"
#include "PolyEngine/Renderer/Renderer2D.h"
#include "PolyEngine/Renderer/RenderCommand.h"

#include "PolyEngine/Renderer/Buffer.h"
#include "PolyEngine/Renderer/Shader.h"
#include "PolyEngine/Renderer/Texture.h"
#include "PolyEngine/Renderer/VertexArray.h"

#include "PolyEngine/Renderer/OrthographicCamera.h"
// ----------------------------------------------------------

// -- Events ------------------------------------------------
#include "PolyEngine/Events/ApplicationEvent.h"
#include "PolyEngine/Events/MouseEvent.h"
#include "PolyEngine/Events/KeyEvent.h"
// ----------------------------------------------------------