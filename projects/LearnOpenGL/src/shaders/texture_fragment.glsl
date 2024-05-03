#version 330 core
out vec4 aColor;

in vec2 aTexCoord;

uniform sampler2D m_texture; 

void main()
{
    aColor = texture(m_texture, aTexCoord);
}