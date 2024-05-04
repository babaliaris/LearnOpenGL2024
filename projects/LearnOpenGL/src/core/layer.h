#pragma once
#include <string>

namespace LearnOpenGL
{
    class Application;

    class Layer
    {
        friend class Application;
        
        public:
        Layer(const std::string &name);
        virtual ~Layer();

        virtual void onAttach(Application *app);
        virtual void onDettach(Application *app);
        virtual void onStart(Application *app);
        virtual void onUpdate(Application *app);

        inline const std::string &getName() const {return m_name;}

        private:
        std::string m_name;
        bool m_hasStarted;
    };
}