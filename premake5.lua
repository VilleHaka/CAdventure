workspace "CAdventure"
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
		systemversion "8.1"
		defines {
			"_CRT_SECURE_NO_WARNINGS",
			"WIN32_LEAN_AND_MEAN",
			"COBJMACROS",
			"INITGUID"
		}


project "game"
	targetname "game"
	kind "ConsoleApp"
	-- kind "WindowedApp"
	language "C"
	files { "./game/**.h", "./game/**.c" }
	-- filter { "files:source/*/**.c" }
		-- flags {"ExcludeFromBuild"}

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


