#version 330 core

out vec4 m_FragColor;
in vec2 m_TexCoord;

uniform sampler2D u_sceneTexture;

//0 = none
//1 = inverse
//2 = grayscale
//3 = Sharpen Kernel
//4 = Blur Kernel
//5 = Edge Detection Kernel
uniform int u_effect;


vec4 calculateKernelEffect(float[9] kernel);

void main()
{
    vec4 current_color  = texture(u_sceneTexture, m_TexCoord);
    float alpha         = current_color.w;

    if (u_effect == 1)
    {
        m_FragColor = vec4(1.0f - vec3(current_color), alpha);
    }

    else if (u_effect == 2)
    {
        float average = (current_color.x + current_color.y + current_color.z) / 3.0f;
        m_FragColor = vec4(average, average, average, alpha);
    }

    else if (u_effect == 3)
    {
        float sharpKernel[9] = float[](
        -1, -1, -1,
        -1,  9, -1,
        -1, -1, -1
        );

        m_FragColor = calculateKernelEffect(sharpKernel);
    }

    else if (u_effect == 4)
    {
        float blurKernel[9] = float[](
            1.0 / 16, 2.0 / 16, 1.0 / 16,
            2.0 / 16, 4.0 / 16, 2.0 / 16,
            1.0 / 16, 2.0 / 16, 1.0 / 16 
        );

        m_FragColor = calculateKernelEffect(blurKernel);
    }

    else if (u_effect == 5)
    {
        float edgeDetectionKernel[9] = float[](
            1, 1, 1,
            1,-8, 1,
            1, 1, 1
        );

        m_FragColor = calculateKernelEffect(edgeDetectionKernel);
    }

    else
    {
        m_FragColor = current_color;
    }
}


vec4 calculateKernelEffect(float[9] kernel)
{
    float offset = 1.0 / 300.0;  

    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // top-left
        vec2( 0.0f,    offset), // top-center
        vec2( offset,  offset), // top-right
        vec2(-offset,  0.0f),   // center-left
        vec2( 0.0f,    0.0f),   // center-center
        vec2( offset,  0.0f),   // center-right
        vec2(-offset, -offset), // bottom-left
        vec2( 0.0f,   -offset), // bottom-center
        vec2( offset, -offset)  // bottom-right
    );

    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(u_sceneTexture, m_TexCoord.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i];

    return vec4(col, 1.0);
}