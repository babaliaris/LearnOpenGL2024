#version 330 core
layout(location=0) in vec3 m_Pos;
layout(location=1) in vec3 m_Normal;
layout(location=2) in vec2 m_TexCoord;
layout(location=3) in mat4 m_instanceModel;

out VS
{
    vec2 aTexCoord;
    vec3 aNormal;
    vec3 aFragPos;

} vs_out;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;
uniform mat4 u_normal;

uniform int u_instancedDraw;

void main()
{
    //Instanced Drawing.
    if (u_instancedDraw == 1)
    {
        gl_Position = u_proj * u_view * m_instanceModel * vec4(m_Pos, 1.0f);
    }

    //Regular.
    else
    {
        gl_Position = u_proj * u_view * u_model * vec4(m_Pos, 1.0f);
    }

    vs_out.aTexCoord   = m_TexCoord;
    vs_out.aNormal     = mat3(u_normal) * m_Normal; //LIGHTING WILL NOT WORK IN INSTANCE DRAW, FIX THIS!!!
    vs_out.aFragPos    = (u_model * vec4(m_Pos, 1.0f)).xyz;
}