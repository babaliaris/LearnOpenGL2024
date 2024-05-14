#version 330 core

in vec3 fColor;

out vec4 m_FragColor;
void main()
{
    m_FragColor = vec4(fColor, 1.0f);
}
