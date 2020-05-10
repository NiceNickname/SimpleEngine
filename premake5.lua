workspace "Engine"
   configurations { "Debug", "Release" }
   platforms { "Win64"}
   startproject "User"

   include "Engine/vendor/GLEW"
   include "Engine/vendor/GLFW"
   include "Engine/vendor/imgui"

project "Engine"
   location "Engine"
   kind "StaticLib"
   language "C++"
   cppdialect "C++17"
   staticruntime "On"

   targetdir "%{prj.name}/out/bin/%{cfg.buildcfg}-%{cfg.architecture}"
   objdir "%{prj.name}/out/obj/%{cfg.buildcfg}-%{cfg.architecture}"

   files 
   { 
      "%{prj.name}/src/**.h", 
      "%{prj.name}/src/**.cpp",
      "%{prj.name}/vendor/stb_image/*.h",
      "%{prj.name}/vendor/stb_image/*.cpp"
   }

   defines { "GLEW_STATIC" }

   includedirs 
   { "%{prj.name}/vendor/GLFW/include", 
      "%{prj.name}/vendor/GLEW/include", 
      "%{prj.name}/vendor/stb_image",
      "%{prj.name}/vendor/imgui",
      "%{prj.name}/src" 
   }
   
   
   links 
   {
        "opengl32.lib",
        "GLFW",
        "GLEW",
        "ImGui"

   }

   filter "platforms:Win64"
      system "Windows"
      architecture "x86_64"

   filter "system:windows"
		systemversion "latest"
      
   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"



project "User"
	location "User"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir "%{prj.name}/out/bin/%{cfg.buildcfg}-%{cfg.architecture}"
   objdir "%{prj.name}/out/obj/%{cfg.buildcfg}-%{cfg.architecture}"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Engine/vendor/GLEW/include",
      "Engine/vendor/GLFW/include",
      "Engine/vendor/stb_image",
      "Engine/vendor/imgui",
		"Engine/src"
	}

	links
	{
		"Engine"
	}

   filter "platforms:Win64"
      system "Windows"
      architecture "x86_64"

   filter "system:windows"
		systemversion "latest"
      
   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
      
