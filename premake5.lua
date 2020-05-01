workspace "Engine"
   configurations { "Debug", "Release" }
   platforms { "x86", "x64"}

project "Engine"
   location "Engine"
   kind "ConsoleApp"
   language "C++"
   targetdir "out/bin/%{cfg.buildcfg}-%{cfg.architecture}"
   objdir "out/obj/%{cfg.buildcfg}-%{cfg.architecture}"

   files { "**.h", "**.cpp" }

   defines { "GLEW_STATIC" }

   includedirs { "%{prj.name}/vendor/GLFW/include", "%{prj.name}/vendor/GLEW/include" }
   libdirs {"%{prj.name}/vendor/GLFW/lib", "%{prj.name}/vendor/GLEW/lib/Win32" }

   links 
   {
        "opengl32.lib",
        "glfw3.lib",
        "glew32s.lib"
   }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"