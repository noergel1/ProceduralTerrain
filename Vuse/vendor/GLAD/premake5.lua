project "GLAD"
	kind "StaticLib"
	language "C"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin_obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/glad/glad.h",
		"include/KHR/khrplatform.h",
		"src/gl.c"
	}

	includedirs 
	{
		"include"
	}

	defines
	{
	}

	filter "system:linux"
		pic "On"
		systemversion "latest"

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		runtime "Release"
		optimize "on"
		symbols "off"