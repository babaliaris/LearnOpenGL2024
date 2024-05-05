#pragma once
#include <string>

namespace LearnOpenGL
{
    class Application;

    class Layer
    {
        friend class Application;
        
        public:
        Layer(const std::string &name, Application *app = nullptr);
        virtual ~Layer();

        virtual void onAttach(Application *app);
        virtual void onDettach(Application *app);
        virtual void onStart(Application *app);
        virtual void onUpdate(Application *app);

        inline const std::string &getName() const {return m_name;}
        inline Application *getApp() const {return m_app;}


        protected:
        Layer *findLayer (const std::string &name);

        private:
        Application *m_app;
        std::string m_name;
        bool m_hasStarted;
    };
}