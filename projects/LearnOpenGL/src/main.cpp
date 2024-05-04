#include "core/application.h"

#include "layers/coordinate_systems.h"
#include "layers/more_3D.h"
#include "layers/camera_layer.h"
#include "layers/camera_system.h"

#define COORDINATE_SYSTEMS "COORDINATE_SYSTEMS"
#define MORE_3D "MORE_3D"
#define CAMERA "CAMERA"
#define CAMERA_SYSTEM "CAMERA_SYSTEM"


int main(void)
{
    LearnOpenGL::Application *app = new LearnOpenGL::Application("LearnOpenGL", 800, 600);

    //Choose example layer to start.
    std::string loadingLayer = CAMERA_SYSTEM;

    VAMP_INFO( "Loading: %s", loadingLayer.c_str() );

    if (loadingLayer == COORDINATE_SYSTEMS)
    {
        LearnOpenGL::CoordinateSystems *new_layer = new LearnOpenGL::CoordinateSystems();
        app->appendLayer(new_layer);
    }

    else if (loadingLayer == MORE_3D)
    {
        LearnOpenGL::More3D *new_layer = new LearnOpenGL::More3D();
        app->appendLayer(new_layer);
    }

    else if (loadingLayer == CAMERA)
    {
        LearnOpenGL::CameraLayer *new_layer = new LearnOpenGL::CameraLayer();
        app->appendLayer(new_layer);
    }

    else if (loadingLayer == CAMERA_SYSTEM)
    {
        LearnOpenGL::CameraSystem *new_layer = new LearnOpenGL::CameraSystem();
        app->appendLayer(new_layer);
    }

    app->Run();

    delete app;

    return 0;
}
