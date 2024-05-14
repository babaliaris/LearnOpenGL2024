#version 330 core
layout(location=0) in vec3 m_Pos;
layout(location=1) in vec3 m_Normal;
layout(location=2) in vec2 m_TexCoord;
layout(location=3) in mat4 m_instanceModel;

out VS
{
    vec2 aTexCoord;

} vs_out;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;
uniform int  u_instancedDraw;

void main()
{
    //Instance Drawing.
    if (u_instancedDraw == 1)
    {
        gl_Position = u_proj * u_view * m_instanceModel * vec4(m_Pos, 1.0f);
    }

    //Regular Drawing.
    else
    {
        gl_Position = u_proj * u_view * u_model * vec4(m_Pos, 1.0f);
    }

    vs_out.aTexCoord = m_TexCoord;
}
