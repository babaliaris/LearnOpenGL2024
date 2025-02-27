project "LearnOpenGL"
    targetname "learnOpenGL"
    kind "ConsoleApp"
    language "C++"
    targetdir "%{_WORKING_DIR}/builds/%{cfg.shortname}/"
    objdir "%{_WORKING_DIR}/obj/%{prj.name}_%{cfg.shortname}/"

    files {
        "src/**.cpp",
        "src/**.c",
        "src/**.h",
        "src/**.hpp"
    }

    includedirs {
        "%{_WORKING_DIR}/submodules/glfw/include",
        "%{_WORKING_DIR}/submodules/glm",
        "%{_WORKING_DIR}/projects/GLAD/src/include",
        "%{_WORKING_DIR}/projects/VampLogger/src/include",
        "%{_WORKING_DIR}/submodules/assimp/include",
        "%{_WORKING_DIR}/submodules/assimp/build/include"
    }

    libdirs {
        "%{_WORKING_DIR}/submodules/assimp/build/lib/",
        "%{_WORKING_DIR}/submodules/assimp/build/contrib/zlib/"
    }

    -- All configurations for LINUX.
    filter "system:linux"
        links {"GL", "X11", "pthread",
            "Xrandr", "Xi", "ldl", "GLFW",
            "GLAD", "VampLogger", "assimp",
            "zlibstatic" -- Required by ASSIMP
        }


    --All Platforms.
    filter{}
    
    filter "configurations:debug"
        runtime "Debug"
        symbols "on"
        defines {"VAMP_DEBUG", "LEARN_OPENGL_DEBUG"}

    filter "configurations:dist"
        runtime "Release"
        optimize "on"

    filter "configurations:release"
        runtime "Release"
        optimize "on"
