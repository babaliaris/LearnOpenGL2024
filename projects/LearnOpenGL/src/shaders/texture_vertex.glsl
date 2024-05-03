#version 330 core
layout(location=0) in vec3 m_Pos;
layout(location=1) in vec2 m_TexCoord;

out vec2 aTexCoord;


void main()
{
    gl_Position = vec4(m_Pos, 1.0f);

    aTexCoord = m_TexCoord;
}