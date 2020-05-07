project "GLEW"
	kind "StaticLib"
	language "C"

	targetdir "out/bin/%{cfg.buildcfg}-%{cfg.architecture}"
    objdir "out/obj/%{cfg.buildcfg}-%{cfg.architecture}"

	files
	{
		"include/**.h",
		"src/**.c"
	}
	
	includedirs {"include"}
	
	defines 
	{ 
		"GLEW_STATIC"
	}

    
    filter "platforms:Win64"
        system "Windows"
        architecture "x86_64"
        

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"


	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"