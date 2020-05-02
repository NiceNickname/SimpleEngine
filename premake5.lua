workspace "Engine"
   configurations { "Debug", "Release" }
   platforms { "Win32", "Win64"}

   include "Engine/vendor/GLEW"
   include "Engine/vendor/GLFW"

project "Engine"
   location "Engine"
   kind "ConsoleApp"
   language "C++"
   staticruntime "On"

   targetdir "out/bin/%{cfg.buildcfg}-%{cfg.architecture}"
   objdir "out/obj/%{cfg.buildcfg}-%{cfg.architecture}"

   files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }

   defines { "GLEW_STATIC" }

   includedirs { "%{prj.name}/vendor/GLFW/include", "%{prj.name}/vendor/GLEW/include" }
   

   
   links 
   {
        "opengl32.lib",
        "GLFW",
        "GLEW"
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

   