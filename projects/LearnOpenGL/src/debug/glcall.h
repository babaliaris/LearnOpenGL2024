#pragma once

void LearnOpenGLClearAllErrors();
void LearnOpenGLRetrieveErrors(const char *file, unsigned int line);




#ifdef LEARN_OPENGL_DEBUG
    #define glCALL(code) LearnOpenGLClearAllErrors(); code; LearnOpenGLRetrieveErrors(__FILE__, __LINE__)

#else
    #define glCALL(code) code
#endif