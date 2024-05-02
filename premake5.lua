workspace "LearnOpenGL"
    configurations { "debug", "dist", "release"}
    startproject "LearnOpenGL"


-- ||||||||||||||||||||Include Projects|||||||||||||||||||| --
include "projects/LearnOpenGL"

group "external"
    include "submodules/glfw"
    include "projects/GLAD"
group ""
-- ||||||||||||||||||||Include Projects|||||||||||||||||||| --