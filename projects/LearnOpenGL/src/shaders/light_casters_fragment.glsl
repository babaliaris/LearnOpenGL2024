#version 330 core
out vec4 aColor;

in vec2 aTexCoord;
in vec3 aNormal;
in vec3 aFragPos;


struct DirectionalLight
{
    vec3    direction;
    vec3    diffuse;
    float   brightness;
};

struct Material
{
    sampler2D   diffuse;
    sampler2D   specular;
    float       shininess;
};


uniform vec3                u_CamPos;
uniform DirectionalLight    u_directionalLight;
uniform Material            u_material;
uniform float               m_ambientFactor;


vec4 calculateAmbientColor();
vec4 calculateDiffuseColor();
vec4 calculateSpecularColor(vec3 camDir);



void main()
{
    vec3 camDir     = normalize(aFragPos - u_CamPos);

    vec4 ambient_color  = calculateAmbientColor();
    vec4 diffuse_color  = calculateDiffuseColor();
    vec4 specular_color = calculateSpecularColor(camDir);

    aColor = ambient_color + diffuse_color + specular_color;
}


vec4 calculateAmbientColor()
{
    return texture(u_material.diffuse, aTexCoord) * m_ambientFactor;
}


vec4 calculateDiffuseColor()
{
    float diffFactor = max( dot(-normalize(u_directionalLight.direction), normalize(aNormal)), 0.0f);

    vec4 diffuseLight = vec4(u_directionalLight.diffuse * u_directionalLight.brightness * diffFactor, 1.0f);

    return texture(u_material.diffuse, aTexCoord) * diffuseLight;
}



vec4 calculateSpecularColor(vec3 camDir)
{
    vec3 reflected = normalize(reflect(normalize(u_directionalLight.direction), aNormal));

    float specFactor = pow(max(dot(reflected, -camDir), 0.0f), u_material.shininess);

    vec4 specularLight = vec4(u_directionalLight.diffuse * u_directionalLight.brightness * specFactor, 1.0f);

    return texture(u_material.specular, aTexCoord) * specularLight;
}
