#version 330 core

out vec4 m_FragColor;
in vec2 m_TexCoord;

uniform sampler2D u_sceneTexture;

void main()
{
    m_FragColor = texture(u_sceneTexture, m_TexCoord) * vec4(0.8f, 0.0f, 0.0f, 0.5f);
}