#version 330 core
layout(location=0) in vec3 m_Pos;
layout(location=1) in vec3 m_Normal;
layout(location=2) in vec2 m_TexCoord;

out vec2 aTexCoord;
out vec3 aNormal;
out vec3 aFragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform mat3 normalMat;

void main()
{
    gl_Position = proj * view * model * vec4(m_Pos, 1.0f);

    aTexCoord   = m_TexCoord;
    aNormal     = normalize(normalMat * m_Normal); //ALWAYS NORMALIZE IT AFTER TRANSFORMATION.
    aFragPos    = (model * vec4(m_Pos, 1.0f)).xyz;
}