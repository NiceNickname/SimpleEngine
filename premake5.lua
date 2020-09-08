   workspace "Engine"
   configurations { "Debug", "Release" }
   platforms { "Win64", "Win32"}
   startproject "User"

   include "Engine/vendor/GLFW"
   include "Engine/vendor/imgui"
   include "Engine/vendor/Glad"

project "Engine"
   location "Engine"
   kind "StaticLib"
   language "C++"
   cppdialect "C++17"
   staticruntime "On"

   pchheader "pch.h"
	pchsource "Engine/src/pch.cpp"

   targetdir "%{prj.name}/out/bin/%{cfg.buildcfg}-%{cfg.architecture}"
   objdir "%{prj.name}/out/obj/%{cfg.buildcfg}-%{cfg.architecture}"

   characterset ("MBCS")

   files 
   { 
      "%{prj.name}/src/**.h", 
      "%{prj.name}/src/**.cpp",
      "%{prj.name}/vendor/stb_image/*.h",
      "%{prj.name}/vendor/stb_image/*.cpp",
      "%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
   }


   includedirs 
   { 
      "%{prj.name}/vendor/GLFW/include", 
      "%{prj.name}/vendor/Glad/include", 
      "%{prj.name}/vendor/stb_image",
      "%{prj.name}/vendor/imgui",
      "%{prj.name}/vendor/glm",
      "%{prj.name}/vendor/spdlog/include",
      "%{prj.name}/src"
   }
   
   
   links 
   {
        "opengl32.lib",
        "GLFW",
        "Glad",
        "ImGui"
   }

   filter "platforms:Win32"
      system "Windows"
      architecture "x86"


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
      "Engine/vendor/GLFW/include",
      "Engine/vendor/Glad/include",
      "Engine/vendor/stb_image",
      "Engine/vendor/imgui",
      "Engine/vendor/glm",
      "Engine/vendor/spdlog/include",
      "Engine/src"
	}

	links
	{
		"Engine"
	}

   filter "platforms:Win32"
      system "Windows"
      architecture "x86"


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


      
