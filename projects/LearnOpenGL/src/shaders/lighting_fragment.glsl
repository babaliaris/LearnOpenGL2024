#version 330 core
out vec4 aColor;

in vec2 aTexCoord;
in vec3 aNormal;
in vec3 aFragPos;

uniform sampler2D m_texture; 

uniform vec3 m_LightPos;
uniform vec3 m_CamPos;

void main()
{
    vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);

    float ambientStrength = 0.2f;

    vec3 ambientLight = lightColor * ambientStrength;

    vec3 lightDir = normalize(aFragPos - m_LightPos);

    float diffFactor = max( dot(-lightDir, normalize(aNormal)), 0.0f);

    vec3 diffuseLight = lightColor * diffFactor;

    //Specular Calculation.
    vec3 camDir = normalize(aFragPos - m_CamPos);

    vec3 reflected = normalize(reflect(lightDir, aNormal));

    float specStrength = 0.5f;

    float specFactor = pow(max(dot(reflected, -camDir), 0.0f),64);

    vec3 specularLight = lightColor * specFactor * specStrength;

    //Final light.
    vec3 phong = ambientLight + diffuseLight + specularLight;

    aColor = texture(m_texture, aTexCoord) * vec4(phong, 1.0f);
}