#version 330 core

layout(location=0) in vec2 v_Pos;
layout(location=1) in vec2 v_TexCoord;

out vec2 m_TexCoord;

void main()
{
    gl_Position = vec4(v_Pos, 0.0f, 1.0f);
    m_TexCoord  = v_TexCoord;
}