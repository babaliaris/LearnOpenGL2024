#version 330 core
layout(points) in;
layout(triangle_strip, max_vertices=5) out;

void main()
{
    gl_Position = gl_in[0].gl_Position + vec4(-0.2f, -0.2f, 0.0f, 1.0f); //Bottom Left.
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(0.2f, -0.2f, 0.0f, 1.0f); //Bottom Right.
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(-0.2f, 0.2f, 0.0f, 1.0f); //Top Left.
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(0.2f, 0.2f, 0.0f, 1.0f); //Top Right.
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(0.0f, 0.4f, 0.0f, 1.0f); //Roof (Middle highest point).
    EmitVertex();

    EndPrimitive();
}