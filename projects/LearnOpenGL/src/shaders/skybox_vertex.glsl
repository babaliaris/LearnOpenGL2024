#version 330 core

layout(location=0) in vec3 m_Position;

out vec3 m_TexCoord;

uniform mat4 u_view;
uniform mat4 u_proj;

void main()
{
    gl_Position = u_proj * u_view * vec4(m_Position, 1.0f);

    m_TexCoord = m_Position;
}