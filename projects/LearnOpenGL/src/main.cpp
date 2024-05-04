#include "core/application.h"

#include "layers/coordinate_systems.h"



int main(void)
{
    LearnOpenGL::Application *app = new LearnOpenGL::Application("LearnOpenGL", 800, 600);

    LearnOpenGL::CoordinateSystems *coordinate_systems = new LearnOpenGL::CoordinateSystems();
    app->appendLayer(coordinate_systems);

    app->Run();

    delete app;

    return 0;
}
