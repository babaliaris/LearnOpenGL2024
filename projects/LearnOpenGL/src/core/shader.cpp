#include "shader.h"
#include <vamplogger/logger.h>
#include <glad/glad.h>
#include <fstream>
#include <string>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>
#include "../debug/glcall.h"



const char *LearnOpenGL::Shader::GetShaderFilename(GLenum shader_type)
{
    switch (shader_type)
    {
        case GL_VERTEX_SHADER:
            return m_vertex_path.c_str();

        case GL_FRAGMENT_SHADER:
            return m_fragment_path.c_str();
        
        default:
            return "Uknown Shader Type";
    }
}


unsigned int LearnOpenGL::Shader::CompileShader(const std::string &source, GLenum shader_type)
{
    glCALL(unsigned int shader = glCreateShader(shader_type));
    
    const char *src = source.c_str();

    glCALL(glShaderSource(shader, 1, &src, NULL));

    glCALL(glCompileShader(shader));

    int success, info_length;

    glCALL(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
    glCALL(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_length));

    if (!success)
    {
        char *info = new char[info_length];

        glCALL(glGetShaderInfoLog(shader, info_length, NULL, info));

        VAMP_ERROR("[%s]: %s", GetShaderFilename(shader_type), info);

        delete info;
    }

    return shader;
}



unsigned int LearnOpenGL::Shader::CreateProgram(const std::string &vertex_source, const std::string &fragment_source)
{
    glCALL(unsigned int program = glCreateProgram());

    glCALL(unsigned int vertex   = CompileShader(vertex_source, GL_VERTEX_SHADER));
    glCALL(unsigned int fragment = CompileShader(fragment_source, GL_FRAGMENT_SHADER));

    glCALL(glAttachShader(program, vertex));
    glCALL(glAttachShader(program, fragment));

    int success, info_length;
    GLenum finalizers[] = {GL_LINK_STATUS, GL_VALIDATE_STATUS};

    for (GLenum finalize : finalizers)
    {
        glCALL(finalize == GL_LINK_STATUS ? glLinkProgram(program) : glValidateProgram(program));

        glCALL(glGetProgramiv(program, finalize, &success));
        glCALL(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_length));

        if (!success)
        {
            char *info = new char[info_length];

            glCALL(glGetProgramInfoLog(program, info_length, NULL, info));

            if (info_length > 0)
            {
                VAMP_ERROR("[%s]: %s", finalize == GL_LINK_STATUS ? "Link Error" : "Validate Error" , info);
            }

            delete info;
        }
    }

    glCALL(glDeleteShader(vertex));
    glCALL(glDeleteShader(fragment));

    return program;
}



std::string LoadSourceFromFile(const char *filename)
{
    std::ifstream file(filename);
    std::stringstream buffer;

    if ( !file.is_open() )
    {
        VAMP_ERROR("Filename: %s, could not be opened.", filename);
        return "";
    }

    buffer << file.rdbuf();

    return buffer.str();
}




LearnOpenGL::Shader::Shader(const char *vertex_file, const char *fragment_file)
: m_id(0), m_vertex_path(vertex_file), m_fragment_path(fragment_file)
{
    std::string vertex_source = LoadSourceFromFile(vertex_file);
    std::string fragment_source = LoadSourceFromFile(fragment_file);

    m_id = CreateProgram(vertex_source, fragment_source);
}


LearnOpenGL::Shader::~Shader()
{
    glCALL(glDeleteProgram(m_id));
}


void LearnOpenGL::Shader::Bind()
{
    glCALL(glUseProgram(m_id));
}


void LearnOpenGL::Shader::Unbind()
{
    glCALL(glUseProgram(0));
}


void LearnOpenGL::Shader::SetUniform(const char *name, int value)
{
    this->Bind();

    glCALL(int location = glGetUniformLocation(m_id, name));

    if (location == -1)
    {
        VAMP_WARN("[Uniform]: %s, was not found.", name);
    }

    else
    {
        glCALL(glUniform1i(location, value));
    }

    this->Unbind();
}


void LearnOpenGL::Shader::SetUniform(const char *name, const glm::mat4 &mat)
{
    this->Bind();

    glCALL(int location = glGetUniformLocation(m_id, name));

    if (location == -1)
    {
        VAMP_WARN("[Uniform]: %s, was not found.", name);
    }

    else
    {
        glCALL(glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat)));
    }

    this->Unbind();
}