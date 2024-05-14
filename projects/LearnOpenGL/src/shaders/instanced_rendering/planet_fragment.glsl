#version 330 core

in VS
{
    vec2 aTexCoord;
} vs_in;

struct Material
{
    int numOfDiffuse;
    int numOfSpecular;

    sampler2D diffuse0;
    sampler2D diffuse1;
    sampler2D diffuse2;
    sampler2D diffuse3;

    sampler2D specular0;
    sampler2D specular1;
    sampler2D specular2;
    sampler2D specular3;
};

uniform Material u_material;

out vec4 m_FragColor;
void main()
{
    if (u_material.numOfDiffuse > 0 && u_material.numOfSpecular >= 0)
    {
        m_FragColor = texture(u_material.diffuse0, vs_in.aTexCoord);
    }

    else
    {
        m_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    }
}
