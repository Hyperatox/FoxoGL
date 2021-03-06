workspace "workspace"
	architecture "x86_64"
	startproject "project"
	configurations { "Debug", "Release" }

	flags
	{
		"MultiProcessorCompile"
	}

function ProjectHelper(name)
	project(name)
	location("vendor/" .. name)
	kind "StaticLib"

	filter "configurations:Debug"
		runtime "Debug"
		optimize "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "Speed"
	
	filter "system:windows"
		systemversion "latest"
		defines
		{
			"WIN32_LEAN_AND_MEAN",
			"NOMINMAX"
		}
	
	filter {}

	targetdir "bin/%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}/%{prj.name}"
	objdir "bin-int/%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}/%{prj.name}"

	cppdialect "C++20"
	cdialect "C11"
	staticruntime "On"
end

ProjectHelper "project"
	location "source"
	kind "ConsoleApp"
	language "C++"

	files
	{
		"%{prj.location}/**.cpp",
		"%{prj.location}/**.h"
	}

	includedirs
	{
		"%{wks.location}/vendor/glfw/include",
		"%{wks.location}/vendor/glad2/include",
		"%{wks.location}/vendor/glm"
	}

	defines
	{
		"GLFW_INCLUDE_NONE"
	}

	links
	{
		"glfw",
		"glad2"
	}

	filter "system:linux"
		links
		{
			"dl",
			"pthread",
			"X11"
		}

	filter "system:macosx"
		links
		{
			"CoreFoundation.framework",
			"Cocoa.framework",
			"IOKit.framework",
			"CoreVideo.framework"
		}

group "Dependencies"

ProjectHelper "glfw"
	language "C"

	files
	{
		"%{prj.location}/src/context.c",
		"%{prj.location}/src/egl_context.c",
		"%{prj.location}/src/egl_context.h",
		"%{prj.location}/src/init.c",
		"%{prj.location}/src/input.c",
		"%{prj.location}/src/internal.h",
		"%{prj.location}/src/monitor.c",
		"%{prj.location}/src/osmesa_context.c",
		"%{prj.location}/src/osmesa_context.h",
		"%{prj.location}/src/vulkan.c",
		"%{prj.location}/src/window.c"
	}

	filter "system:windows"
		files
		{
			"%{prj.location}/src/wgl_context.c",
			"%{prj.location}/src/wgl_context.h",
			"%{prj.location}/src/win32_init.c",
			"%{prj.location}/src/win32_joystick.c",
			"%{prj.location}/src/win32_joystick.h",
			"%{prj.location}/src/win32_monitor.c",
			"%{prj.location}/src/win32_platform.h",
			"%{prj.location}/src/win32_thread.c",
			"%{prj.location}/src/win32_time.c",
			"%{prj.location}/src/win32_window.c"
		}

		defines 
		{ 
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "system:linux"
		files
		{
			"%{prj.location}/src/glx_context.c",
			"%{prj.location}/src/glx_context.h",
			"%{prj.location}/src/linux_joystick.c",
			"%{prj.location}/src/linux_joystick.h",
			"%{prj.location}/src/posix_time.c",
			"%{prj.location}/src/posix_time.h",
			"%{prj.location}/src/posix_thread.c",
			"%{prj.location}/src/posix_thread.h",
			"%{prj.location}/src/x11_init.c",
			"%{prj.location}/src/x11_monitor.c",
			"%{prj.location}/src/x11_platform.h",
			"%{prj.location}/src/x11_window.c",
			"%{prj.location}/src/xkb_unicode.c",
			"%{prj.location}/src/xkb_unicode.h"
		}

		defines 
		{ 
			"_GLFW_X11"
		}
		
	filter "system:macosx"
		files
		{
			"%{prj.location}/src/cocoa_init.m",
			"%{prj.location}/src/cocoa_joystick.m",
			"%{prj.location}/src/cocoa_joystick.h",
			"%{prj.location}/src/cocoa_monitor.m",
			"%{prj.location}/src/cocoa_platform.h",
			"%{prj.location}/src/cocoa_time.c",
			"%{prj.location}/src/cocoa_window.m",
			"%{prj.location}/src/nsgl_context.m",
			"%{prj.location}/src/nsgl_context.h",
			"%{prj.location}/src/posix_thread.c",
			"%{prj.location}/src/posix_thread.h"
		}

		defines
		{ 
			"_GLFW_COCOA"
		}

ProjectHelper "glad2"
	language "C"

	files
	{
		"%{prj.location}/src/gl.c"
	}

	includedirs
	{
		"%{prj.location}/include"
	}