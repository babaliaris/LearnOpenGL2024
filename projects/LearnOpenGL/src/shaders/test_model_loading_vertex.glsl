#version 330 core
layout(location=0) in vec3 m_Pos;
layout(location=1) in vec3 m_Normal;
layout(location=2) in vec2 m_TexCoord;

out vec2 aTexCoord;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;

uniform int u_instancedDraw;

void main()
{
    if (u_instancedDraw != 1)
    {
        gl_Position = u_proj * u_view * u_model * vec4(m_Pos, 1.0f);
    }

    else
    {
        gl_Position = u_proj * u_view * u_model * vec4(m_Pos, 1.0f);
    }


    aTexCoord   = m_TexCoord;
}