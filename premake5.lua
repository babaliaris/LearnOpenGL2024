-- -------------------------------Compile Assimp------------------------------- --
function CompileAssimp()
    print("Compiling ASSIMP...")
    os.execute("cd submodules/assimp && mkdir -p build && cd build && cmake .. -DBUILD_SHARED_LIBS=off && make -j4")
end
CompileAssimp()
-- -------------------------------Compile Assimp------------------------------- --

workspace "LearnOpenGL"
    configurations { "debug", "dist", "release"}
    startproject "LearnOpenGL"


-- ||||||||||||||||||||Include Projects|||||||||||||||||||| --
include "projects/LearnOpenGL"
include "projects/VampLogger"

group "external"
    include "submodules/glfw"
    include "projects/GLAD"
group ""
-- ||||||||||||||||||||Include Projects|||||||||||||||||||| --