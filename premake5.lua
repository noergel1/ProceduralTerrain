workspace "Vuse"
	architecture "x64"
	startproject "ProceduralTerrain"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	-- Include directories relative to root folder (solution directory)
	IncludeDir = {}
	IncludeDir["GLFW"] = "Vuse/vendor/GLFW/include"
	IncludeDir["GLAD"] = "Vuse/vendor/GLAD/include"
	IncludeDir["ImGui"] = "Vuse/vendor/imgui"
	IncludeDir["glm"] = "Vuse/vendor/glm"
	IncludeDir["stb_image"] = "Vuse/vendor/stb_image"
	IncludeDir["FastNoiseLite"] = "ProceduralTerrain/vendor/FastNoiseLite"

	group "Dependencies"
		include "Vuse/vendor/GLFW"
		include "Vuse/vendor/GLAD"
		include "Vuse/vendor/imgui"
	group ""

project "Vuse"
	location "Vuse"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin_obj/" .. outputdir .. "/%{prj.name}")

	pchheader "vuse_pch.h"
	pchsource "Vuse/src/vuse_pch.cpp"

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"CRT_SECURE_NO_DEPRECATE", 
		"_CRT_NONSTDC_NO_DEPRECATE",
		"IMGUI_API=__declspec(dllexport)"
	}

	includedirs{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links {
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"VUSE_PLATFORM_WINDOWS",
			"VUSE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "VUSE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "VUSE_RELEASE"
		runtime "Release"
		optimize "on"

		
	filter "configurations:Dist"
		defines "VUSE_DIST"
		runtime "Release"
		optimize "on"

project "ProceduralTerrain"
	location "ProceduralTerrain"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin_obj/" .. outputdir .. "/%{prj.name}")

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs{
		"Vuse/vendor/spdlog/include",
		"Vuse/src",
		"Vuse/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.FastNoiseLite}"
	}

	defines
	{
		"IMGUI_API=__declspec(dllimport)"
	}

	links {
		"Vuse"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"VUSE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "VUSE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "VUSE_RELEASE"
		runtime "Release"
		optimize "on"

		
	filter "configurations:Dist"
		defines "VUSE_DIST"
		runtime "Release"
		optimize "on"