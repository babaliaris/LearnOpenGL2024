#version 330 core

out vec4 m_FragColor;

in vec3 m_TexCoord;

uniform samplerCube u_skyboxTexture;

void main()
{
    m_FragColor = texture(u_skyboxTexture, m_TexCoord);
}