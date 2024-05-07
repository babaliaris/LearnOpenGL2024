#version 330 core
out vec4 aColor;

in vec2 aTexCoord;
in vec3 aNormal;
in vec3 aFragPos;

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
    aColor = texture(u_material.diffuse0, aTexCoord);
}