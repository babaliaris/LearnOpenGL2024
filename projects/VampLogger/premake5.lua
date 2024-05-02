project "VampLogger"
    kind "StaticLib"
    language "C++"
    targetdir "%{_WORKING_DIR}/builds/%{cfg.shortname}/"
    objdir "%{_WORKING_DIR}/obj/%{prj.name}_%{cfg.shortname}/"

    files {
        "src/**.cpp",
        "src/**.c",
        "src/**.h",
        "src/**.hpp"
    }

    --All Platforms.
    filter{}
    
    filter "configurations:debug"
        runtime "Debug"
        symbols "on"
        defines "VAMP_DEBUG"

    filter "configurations:dist"
        runtime "Release"
        optimize "on"

    filter "configurations:release"
        runtime "Release"
        optimize "on"
