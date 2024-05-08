#include "core/application.h"
#include "layers/cameraFunctionalityLayer.h"

#include "layers/coordinate_systems.h"
#include "layers/more_3D.h"
#include "layers/camera_layer.h"
#include "layers/camera_system.h"
#include "layers/colors.h"
#include "layers/lighting_maps.h"
#include "layers/light_casters.h"
#include "layers/test_model_loading.h"
#include "layers/model_full_phong.h"
#include "layers/stencil_buffer.h"
#include "layers/blending.h"
#include "layers/face_culling.h"
#include "layers/post_processing.h"
#include "layers/skybox.h"

#define COORDINATE_SYSTEMS "COORDINATE_SYSTEMS"
#define MORE_3D "MORE_3D"
#define CAMERA "CAMERA"
#define CAMERA_SYSTEM "CAMERA_SYSTEM"
#define COLORS "COLORS"
#define LIGHTING_MAPS "LIGHTING_MAPS"
#define LIGHT_CASTERS "LIGHT_CASTERS"
#define TEST_MODEL_LOADING "TEST_MODEL_LOADING"
#define MODEL_FULL_PHONG "MODEL_FULL_PHONG"
#define STENCIL_BUFFER "STENCIL_BUFFER"
#define BLENDING "BLENDING"
#define FACE_CULLING "FACE_CULLING"
#define POST_PROCESSING "POST_PROCESSING"
#define SKYBOX "SKYBOX"


int main(void)
{
    LearnOpenGL::Application *app = new LearnOpenGL::Application("LearnOpenGL", 800, 600);

    //Create a camera and append it to the layers.
    LearnOpenGL::CameraFunctionalityLayer *camFunctionality = new LearnOpenGL::CameraFunctionalityLayer(app);
    app->appendLayer(camFunctionality);

    //Choose example layer to start.
    std::string loadingLayer = SKYBOX;

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
        LearnOpenGL::CameraSystem *new_layer = new LearnOpenGL::CameraSystem(app);
        app->appendLayer(new_layer);
    }

    else if (loadingLayer == COLORS)
    {
        LearnOpenGL::ColorsLayer *new_layer = new LearnOpenGL::ColorsLayer(app);
        app->appendLayer(new_layer);
    }

    else if (loadingLayer == LIGHTING_MAPS)
    {
        LearnOpenGL::LightingMaps *new_layer = new LearnOpenGL::LightingMaps(app);
        app->appendLayer(new_layer);
    }

    else if (loadingLayer == LIGHT_CASTERS)
    {
        LearnOpenGL::LightingCasters *new_layer = new LearnOpenGL::LightingCasters(app);
        app->appendLayer(new_layer);
    }

    else if (loadingLayer == TEST_MODEL_LOADING)
    {
        LearnOpenGL::TestModelLoading *new_layer = new LearnOpenGL::TestModelLoading(app);
        app->appendLayer(new_layer);
    }

    else if (loadingLayer == MODEL_FULL_PHONG)
    {
        LearnOpenGL::ModelFullPhong *new_layer = new LearnOpenGL::ModelFullPhong(app);
        app->appendLayer(new_layer);
    }

    else if (loadingLayer == STENCIL_BUFFER)
    {
        LearnOpenGL::StencilBuffer *new_layer = new LearnOpenGL::StencilBuffer(app);
        app->appendLayer(new_layer);
    }

    else if (loadingLayer == BLENDING)
    {
        LearnOpenGL::Blending *new_layer = new LearnOpenGL::Blending(app);
        app->appendLayer(new_layer);
    }

    else if (loadingLayer == FACE_CULLING)
    {
        LearnOpenGL::FaceCulling *new_layer = new LearnOpenGL::FaceCulling(app);
        app->appendLayer(new_layer);
    }

    else if (loadingLayer == POST_PROCESSING)
    {
        LearnOpenGL::PostProcessing *new_layer = new LearnOpenGL::PostProcessing(app);
        app->appendLayer(new_layer);
    }

    else if (loadingLayer == SKYBOX)
    {
        LearnOpenGL::Skybox *new_layer = new LearnOpenGL::Skybox(app);
        app->appendLayer(new_layer);
    }

    glfwSetInputMode(app->getWindow()->getGlfwWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    app->Run();

    delete app;

    return 0;
}
