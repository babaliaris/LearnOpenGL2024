#version 330 core

out vec4 m_FragColor;

//in vec2 aTexCoord;
in vec3 aNormal;
in vec3 aFragPos;

//0 = reflection
//1 = refraction.
uniform int u_mode;

uniform vec3 u_camPos;

uniform samplerCube u_skyboxTexture;

void main()
{
    vec3 light_dir = normalize(aFragPos - u_camPos);

    //Reflection.
    if (u_mode == 0)
    {
        vec3 reflected_light = reflect(light_dir, normalize(aNormal));

        m_FragColor = texture(u_skyboxTexture, reflected_light);
    }

    //Refraction.
    else if (u_mode == 1)
    {
        vec3 refracted_light = refract(light_dir, normalize(aNormal), 0.6f);

        m_FragColor = texture(u_skyboxTexture, refracted_light);
    }

    //Debug color.
    else
    {
        m_FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    }
}