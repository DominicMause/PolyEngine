workspace "PolyEngine"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "PolyEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "PolyEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "PolyEngine/vendor/imgui"
IncludeDir["glm"] = "PolyEngine/vendor/glm"
IncludeDir["stb_image"] = "PolyEngine/vendor/stb_image"

include "PolyEngine/vendor/GLFW"
include "PolyEngine/vendor/Glad"
include "PolyEngine/vendor/imgui"

project "PolyEngine"
	location "PolyEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pepch.h"
	pchsource "PolyEngine/src/pepch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"PE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "PE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "PE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "PE_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"PolyEngine/vendor/spdlog/include",
		"PolyEngine/src",
		"PolyEngine/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"PolyEngine"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "PE_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "PE_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "PE_DIST"
		runtime "Release"
		optimize "On"
