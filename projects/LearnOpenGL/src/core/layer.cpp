#include "layer.h"
#include "application.h"

namespace LearnOpenGL
{
    Layer::Layer(const std::string &name, Application *app)
    : m_app(app), m_name(name), m_hasStarted(false)
    {

    }


    Layer::~Layer()
    {
    }

    void Layer::onAttach(Application *app)
    {

    }

    void Layer::onDettach(Application *app)
    {

    }

    void Layer::onStart(Application *app)
    {

    }

    void Layer::onUpdate(Application *app)
    {

    }

    Layer *Layer::findLayer(const std::string &name)
    {
        for (Layer *layer : m_app->m_layers)
        {
            if (layer->getName() == name)
                return layer;
        }

        return nullptr;
    }
}