#version 330 core
out vec4 aColor;

in vec2 aTexCoord;

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

void main()
{
    //Diffuse texture.
    if (u_material.numOfDiffuse > 0 && u_material.numOfSpecular >= 0)
    {
        aColor = texture(u_material.diffuse0, aTexCoord) + texture(u_material.specular0, aTexCoord) * 0.0001;
    }

    //Debug Color.
    else
    {
        aColor = vec4(0.5, 0.5, 0.5, 1.0);
    }
}