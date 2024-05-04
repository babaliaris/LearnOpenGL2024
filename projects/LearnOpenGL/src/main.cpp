#include "core/application.h"




int main(void)
{
    LearnOpenGL::Application *app = new LearnOpenGL::Application("LearnOpenGL", 800, 600);

    app->Run();

    delete app;

    return 0;
}
