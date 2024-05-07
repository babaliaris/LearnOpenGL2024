#version 330 core
layout(location=0) in vec3 m_Pos;
layout(location=1) in vec3 m_Normal;
layout(location=2) in vec2 m_TexCoord;

out vec2 aTexCoord;
out vec3 aNormal;
out vec3 aFragPos;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;
uniform mat4 u_normal;

void main()
{
    gl_Position = u_proj * u_view * u_model * vec4(m_Pos, 1.0f);

    aTexCoord   = m_TexCoord;
    aNormal     = mat3(u_normal) * m_Normal;
    aFragPos    = (u_model * vec4(m_Pos, 1.0f)).xyz;
}