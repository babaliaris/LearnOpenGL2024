#version 330 core
layout(location=0) in vec3 m_Pos;
layout(location=1) in vec3 m_Normal;
layout(location=2) in vec2 m_TexCoord;

out VS
{
    vec2 aTexCoord;

} vs_out;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;

void main()
{
    gl_Position = u_proj * u_view * u_model * vec4(m_Pos, 1.0f);

    vs_out.aTexCoord = m_TexCoord;
}
