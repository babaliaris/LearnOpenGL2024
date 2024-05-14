#version 330 core
out vec4 aColor;

in vec2 aTexCoord;
in vec3 aNormal;
in vec3 aFragPos;


struct DirectionalLight
{
    vec3    position;
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
uniform DirectionalLight    u_placedLight;
uniform Material            u_material;
uniform float               m_ambientFactor;


vec4 calculateAmbientColor();
vec4 calculateDiffuseColor(vec3 lightDir);
vec4 calculateSpecularColor(vec3 lightDir, vec3 camDir);



void main()
{
    vec3 lightDir   = normalize(aFragPos - u_placedLight.position);
    vec3 camDir     = normalize(aFragPos - u_CamPos);

    vec4 ambient_color  = calculateAmbientColor();
    vec4 diffuse_color  = calculateDiffuseColor(lightDir);
    vec4 specular_color = calculateSpecularColor(lightDir, camDir);

    aColor = ambient_color + diffuse_color + specular_color;
}


vec4 calculateAmbientColor()
{
    return texture(u_material.diffuse, aTexCoord) * m_ambientFactor;
}


vec4 calculateDiffuseColor(vec3 lightDir)
{
    float diffFactor = max( dot(-lightDir, normalize(aNormal)), 0.0f);

    vec4 diffuseLight = vec4(u_placedLight.diffuse * u_placedLight.brightness * diffFactor, 1.0f);

    return texture(u_material.diffuse, aTexCoord) * diffuseLight;
}



vec4 calculateSpecularColor(vec3 lightDir, vec3 camDir)
{
    //vec3 reflected = normalize(reflect(lightDir, aNormal));

    //-lightDir: from fragment to light
    //-camDir: from fragment to camera.
    vec3 halfVector = normalize( -lightDir - camDir );

    float specFactor = pow(max(dot(halfVector, aNormal), 0.0f), u_material.shininess);

    vec4 specularLight = vec4(u_placedLight.diffuse * u_placedLight.brightness * specFactor, 1.0f);

    return texture(u_material.specular, aTexCoord) * specularLight;
}
