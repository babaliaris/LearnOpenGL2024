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
    vec3    attenuation;
    float   brightness;
};


struct SpotLight
{
    vec3 position;
    vec3 direction;
    vec3 diffuse;
    vec3 attenuation;
    float brightness;
    float cutoff;
    float outer;
};

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


uniform int                 u_numberOfDirectionalLights;
uniform int                 u_numberOfPointLights;
uniform int                 u_numberOfSpotLight;
uniform vec3                u_CamPos;
uniform DirectionalLight    u_directionalLight;
uniform PointLight          u_pointLight;
uniform SpotLight           u_spotLight;
uniform Material            u_material;
uniform float               u_ambientFactor;


vec4 calculateAmbientLight();
vec4 calculateImpactedLight(vec3 diffuse, float brightness, vec3 direction);
vec4 calculateSpecularLight(vec3 diffuse, float brightness, vec3 direction);
vec3 attenuateLight(vec3 diffuse, vec3 position, vec3 coefficients);
vec3 calculateSpotLight();



void main()
{
    //------------------Initialize Lights------------------//
    vec4 ambient = calculateAmbientLight();

    vec4 impacted_directional = vec4(0.0f, 0.0f, 0.0f, 0.0f);
    vec4 specular_directional = vec4(0.0f, 0.0f, 0.0f, 0.0f);

    vec3 point_attenuated   = vec3(0.0f, 0.0f, 0.0f);
    vec4 point_impacted     = vec4(0.0f, 0.0f, 0.0f, 0.0f);
    vec4 point_specular     = vec4(0.0f, 0.0f, 0.0f, 0.0f);

    vec3 spot_light     = vec3(0.0f, 0.0f, 0.0f);
    vec4 spot_impacted  = vec4(0.0f, 0.0f, 0.0f, 0.0f);
    vec4 spot_specular  = vec4(0.0f, 0.0f, 0.0f, 0.0f);
    //------------------Initialize Lights------------------//


    //Calculate Directional Lighting.
    if (u_numberOfDirectionalLights > 0)
    {
        impacted_directional    = calculateImpactedLight(u_directionalLight.diffuse,
                                        u_directionalLight.brightness, u_directionalLight.direction);

        specular_directional   = calculateSpecularLight(u_directionalLight.diffuse,
                                        u_directionalLight.brightness, u_directionalLight.direction);
    }


    //Calculate Point Lighting.
    if (u_numberOfPointLights > 0)
    {
        point_attenuated = attenuateLight(u_pointLight.diffuse, u_pointLight.position, u_pointLight.attenuation);
        point_impacted   = calculateImpactedLight(point_attenuated, u_pointLight.brightness, aFragPos - u_pointLight.position);
        point_specular   = calculateSpecularLight(point_attenuated, u_pointLight.brightness, aFragPos - u_pointLight.position);
    }


    //Calculate Spot Lighting.
    if (u_numberOfSpotLight > 0)
    {
        spot_light     = attenuateLight(calculateSpotLight(), u_spotLight.position, u_spotLight.attenuation);
        spot_impacted  = calculateImpactedLight(spot_light, u_spotLight.brightness, aFragPos - u_spotLight.position);
        spot_specular  = calculateSpecularLight(spot_light, u_spotLight.brightness, aFragPos - u_spotLight.position);
    }

    vec4 total_diffuse  = ambient + impacted_directional + point_impacted + spot_impacted;
    vec4 total_specular = specular_directional + point_specular + spot_specular;

    //Diffuce and Specular maps.
    if (u_material.numOfDiffuse == 1 && u_material.numOfSpecular == 1)
    {
        aColor = texture(u_material.diffuse0, aTexCoord) * total_diffuse + texture(u_material.specular0, aTexCoord) * total_specular;
    }

    //Diffuse only.
    else if (u_material.numOfDiffuse == 1 && u_material.numOfSpecular == 0)
    {
        aColor = texture(u_material.diffuse0, aTexCoord) * total_diffuse;
    }

    //No textures at all.
    else
    {
        aColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);
    }
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

    float specFactor = pow(max(dot(reflected, -camDir), 0.0f), 64.0f);

    vec4 specularLight = vec4(diffuse * brightness * specFactor, 1.0f);

    return specularLight;
}



vec3 attenuateLight(vec3 diffuse, vec3 position, vec3 coefficients)
{
    float light_distance    = length(aFragPos - position);
    float attenuation       = 1 / ( coefficients.x + coefficients.y * light_distance + coefficients.z * pow(light_distance, 2) );

    return diffuse * attenuation;
}


vec3 calculateSpotLight()
{
    vec3 lightDir = normalize(aFragPos - u_spotLight.position);

    float theta     = dot(-lightDir, -normalize(u_spotLight.direction));
    float ephilon   = u_spotLight.cutoff - u_spotLight.outer;
    float intensity = clamp( (theta - u_spotLight.outer) / ephilon, 0.0f, 1.0f );

    if (theta > u_spotLight.outer)
    {
        return u_spotLight.diffuse * intensity;
    }

    return vec3(0.0f, 0.0f, 0.0f);
}
