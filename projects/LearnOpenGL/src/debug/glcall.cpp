#include "glcall.h"
#include <string>
#include <glad/glad.h>
#include <vamplogger/logger.h>


const char *GetOpenGLErrorMeaning(GLenum error)
{
    switch (error)
    {
        case GL_INVALID_ENUM:
            return "GL_INVALID_ENUM";

        case GL_INVALID_VALUE:
            return "GL_INVALID_VALUE";

        case GL_INVALID_OPERATION:
            return "GL_INVALID_OPERATION";

        case GL_OUT_OF_MEMORY:
            return "GL_OUT_OF_MEMORY";

        case GL_INVALID_FRAMEBUFFER_OPERATION:
            return "GL_INVALID_FRAMEBUFFER_OPERATION";

        default:
            return "Uknown Error";
    }
}




void LearnOpenGLClearAllErrors()
{
    while ( glGetError() );
}






void LearnOpenGLRetrieveErrors(const char *file, unsigned int line)
{
    while ( GLenum error = glGetError() )
    {
        VAMP_PRINTF_COLORED( VAMP_CLI_COLOR_RED, "[%s : %#08x]\n\t[%s : %d]\n\t[Message]: ", "GLError", error, file, line );
        VAMP_PRINTF_COLORED( VAMP_CLI_COLOR_CYAN, "%s\n", GetOpenGLErrorMeaning(error) );
        printf("\n\n");
    }
}