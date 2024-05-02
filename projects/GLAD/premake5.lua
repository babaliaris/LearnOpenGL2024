project "GLAD"
    kind "StaticLib"
    language "C"
    targetdir "%{_WORKING_DIR}/builds/%{cfg.shortname}/"
    objdir "%{_WORKING_DIR}/obj/%{prj.name}_%{cfg.shortname}/"

    files {
        "src/**.c",
        "src/**.h"
    }

    includedirs {
        "src/include"
    }

    --All Platforms.
    filter{}
    
    filter "configurations:debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:dist"
        runtime "Release"
        optimize "on"

    filter "configurations:release"
        runtime "Release"
        optimize "on"
