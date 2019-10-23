workspace "cA"
	configurations {"Debug", "Release"}
	targetdir "../builds/%{cfg.buildcfg}/%{cfg.platform}"
	objdir "./builds/obj/%{cfg.buildcfg}/%{cfg.platform}"
	location "./project-files"
	debugdir "./"
	libdirs {
		"../builds/%{cfg.buildcfg}/%{cfg.platform}"
	}
	
	configuration "macosx"	
		platforms { "x64" }
	configuration "not macosx"
		platforms { "x64", "x86" }

	configuration "windows"
		characterset "MBCS"
		systemversion "10.0"
		defines {
			"_CRT_SECURE_NO_WARNINGS",
			"WIN32_LEAN_AND_MEAN",
			"COBJMACROS",
			"INITGUID"
		}


project "cA"
	targetname "ca"

	kind "SharedLib"
	defines {
		"CA_BUILD_DLL"
	}

	-- kind "WindowedApp"
	language "C"
	files { "include/ca/*.h", "source/ca/*.c" }

	
	configuration "x64"
		libdirs {}
		
	--configuration "x86"
		--libdirs {}

	configuration "not macosx"
		includedirs {"./include"}

	

	configuration "windows"
		files { "source/ca/**.c", "source/ca/**.h" }
		defines {}
		links {"ws2_32","hid"}

	configuration "macosx"
		defines {}

	configuration "android"
		defines {}

	configuration "Debug"
		defines {"DEBUG"}
		symbols "On"	

	configuration "Release"
		defines {"NDEBUG"}
		optimize "On"

	configuration "Debug"
		defines {
			"RUSKA_DEBUG_LOGS",
			"_DEBUG"
		}



project "Client"
	targetname "client"
	kind "ConsoleApp"
	-- kind "WindowedApp"
	language "C"
	files { "./client/**.h", "./client/**.c" }
	-- filter { "files:source/*/**.c" }
		-- flags {"ExcludeFromBuild"}

	links {"ca"}
	configuration "Debug"
		defines {
			"CA_DEBUG_LOGS"
		}


	configuration "x64"
		libdirs {}
		
	--configuration "x86"
		--libdirs {}
		
	configuration "not macosx"
		includedirs {"./include"}
	configuration "macosx"
		sysincludedirs {"./include"}

	configuration "windows"
		defines {}
		links {}

	configuration "not windows"
		defines {}

	configuration "linux"
		defines {}

	configuration "macosx"
		defines {}

	configuration "android"
		defines {}

	configuration "Debug"
		defines {"DEBUG"}
		symbols "On"	

	configuration "Release"
		defines {"NDEBUG"}
		optimize "On"

project "Server"
	targetname "server"
	kind "ConsoleApp"
	-- kind "WindowedApp"
	language "C"
	files { "./server/**.h", "./server/**.c" }
	-- filter { "files:source/*/**.c" }
		-- flags {"ExcludeFromBuild"}

	links {"ca"}
	configuration "Debug"
		defines {
			"CA_DEBUG_LOGS"
		}


	configuration "x64"
		libdirs {}
		
	--configuration "x86"
		--libdirs {}
		
	configuration "not macosx"
		includedirs {"./include"}
	configuration "macosx"
		sysincludedirs {"./include"}

	configuration "windows"
		defines {}
		links {}

	configuration "not windows"
		defines {}

	configuration "linux"
		defines {}

	configuration "macosx"
		defines {}

	configuration "android"
		defines {}

	configuration "Debug"
		defines {"DEBUG"}
		symbols "On"	

	configuration "Release"
		defines {"NDEBUG"}
		optimize "On"