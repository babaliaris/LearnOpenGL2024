#pragma once
#include <string>
#include <glm/glm.hpp>

namespace LearnOpenGL
{
    class Shader
    {
        public:
        Shader(const char *vertex_file, const char *fragment_file);
        Shader(const std::string &vertex_file, const std::string &fragment_file);
        ~Shader();

        void Bind();
        void Unbind();

        void SetUniform(const char *name, int value);
        void SetUniform(const char *name, float value);
        void SetUniform(const char *name, const glm::mat4 &mat);
        void SetUniform(const char *name, const glm::mat3 &mat);
        void SetUniform(const char *name, const glm::vec3 &vec3);

        private:
        unsigned int m_id;
        std::string m_vertex_path, m_fragment_path;

        private:
        const char *GetShaderFilename(unsigned int shader_type);
        unsigned int CompileShader(const std::string &source, unsigned int shader_type);
        unsigned int CreateProgram(const std::string &vertex_source, const std::string &fragment_source);
    };
}