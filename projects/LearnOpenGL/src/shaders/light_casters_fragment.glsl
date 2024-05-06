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


struct PointLight
{
    vec3    position;
    vec3    diffuse;
    float   brightness;
    float   kc;
    float   kl;
    float   kq;
};

struct Material
{
    sampler2D   diffuse;
    sampler2D   specular;
    float       shininess;
};


uniform vec3                u_CamPos;
uniform DirectionalLight    u_directionalLight;
uniform PointLight          u_pointLight;
uniform Material            u_material;
uniform float               u_ambientFactor;


vec4 calculateAmbientLight();
vec4 calculateImpactedLight(vec3 diffuse, float brightness, vec3 direction);
vec4 calculateSpecularLight(vec3 diffuse, float brightness, vec3 direction);



void main()
{
    vec4 ambient                = calculateAmbientLight();

    vec4 diffuse_directional    = calculateImpactedLight(u_directionalLight.diffuse,
                                    u_directionalLight.brightness, u_directionalLight.direction);

    vec4 specular_directional   = calculateSpecularLight(u_directionalLight.diffuse,
                                    u_directionalLight.brightness, u_directionalLight.direction);


    vec4 total_light = ambient + diffuse_directional + specular_directional;

    aColor = texture(u_material.diffuse, aTexCoord) * total_light;
}


vec4 calculateAmbientLight()
{
    return vec4(1.0f, 1.0f, 1.0f, 1.0f) * u_ambientFactor;
}


vec4 calculateImpactedLight(vec3 diffuse, float brightness, vec3 direction)
{

    float impactedFactor = max( dot(normalize(-direction), normalize(aNormal)), 0.0f);

    vec4 impactedLight = vec4(diffuse * brightness * impactedFactor, 1.0f);

    return impactedLight;
}



vec4 calculateSpecularLight(vec3 diffuse, float brightness, vec3 direction)
{
    vec3 camDir     = normalize(aFragPos - u_CamPos);

    vec3 reflected = normalize(reflect(normalize(direction), aNormal));

    float specFactor = pow(max(dot(reflected, -camDir), 0.0f), u_material.shininess);

    vec4 specularLight = vec4(diffuse * brightness * specFactor, 1.0f);

    return specularLight;
}



