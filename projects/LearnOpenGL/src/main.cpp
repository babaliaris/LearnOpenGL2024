#include "core/application.h"

#include "layers/coordinate_systems.h"
#include "layers/more_3D.h"
#include "layers/camera_layer.h"

#define COORDINATE_SYSTEMS "COORDINATE_SYSTEMS"
#define MORE_3D "MORE_3D"
#define CAMERA "CAMERA"


int main(void)
{
    LearnOpenGL::Application *app = new LearnOpenGL::Application("LearnOpenGL", 800, 600);

    //Choose example layer to start.
    std::string loadingLayer = CAMERA;

    VAMP_INFO( "Loading: %s", loadingLayer.c_str() );

    if (loadingLayer == COORDINATE_SYSTEMS)
    {
        LearnOpenGL::CoordinateSystems *coordinate_systems = new LearnOpenGL::CoordinateSystems();
        app->appendLayer(coordinate_systems);
    }

    else if (loadingLayer == MORE_3D)
    {
        LearnOpenGL::More3D *more_2d = new LearnOpenGL::More3D();
        app->appendLayer(more_2d);
    }

    else if (loadingLayer == CAMERA)
    {
        LearnOpenGL::CameraLayer *camera_layer = new LearnOpenGL::CameraLayer();
        app->appendLayer(camera_layer);
    }

    app->Run();

    delete app;

    return 0;
}
