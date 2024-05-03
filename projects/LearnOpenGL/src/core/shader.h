#pragma once
#include <string>

namespace LearnOpenGL
{
    class Shader
    {
        public:
        Shader(const char *vertex_file, const char *fragment_file);
        ~Shader();

        void Bind();
        void Unbind();

        private:
        unsigned int m_id;
        std::string m_vertex_path, m_fragment_path;

        private:
        const char *GetShaderFilename(unsigned int shader_type);
        unsigned int CompileShader(const std::string &source, unsigned int shader_type);
        unsigned int CreateProgram(const std::string &vertex_source, const std::string &fragment_source);
    };
}