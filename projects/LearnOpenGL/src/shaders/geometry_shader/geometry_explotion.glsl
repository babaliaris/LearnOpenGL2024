#version 330 core
layout(triangles) in;
layout(triangle_strip, max_vertices=3) out;

in VS
{
    vec2 aTexCoord;
    vec3 aNormal;
    vec3 aFragPos;
} vs_in[];

out vec2 aTexCoord;
out vec3 aNormal;
out vec3 aFragPos;

uniform float u_time;


vec3 getTriangleNormal()
{
    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
    return normalize(cross(a, b));
}

vec4 explodedVertex(vec4 position, vec3 normal)
{
    float magnitude = 2.0;
    vec3 direction  = normal * ((sin(u_time) + 1.0) / 2.0) * magnitude; 
    return position + vec4(direction, 0.0);
}

void main()
{
    vec3 normal = getTriangleNormal();

    gl_Position = explodedVertex( gl_in[0].gl_Position, normal );
    aTexCoord   = vs_in[0].aTexCoord;
    aNormal     = vs_in[0].aNormal;
    aFragPos    = vs_in[0].aFragPos;
    EmitVertex();

    gl_Position = explodedVertex( gl_in[1].gl_Position, normal );
    aTexCoord   = vs_in[1].aTexCoord;
    aNormal     = vs_in[1].aNormal;
    aFragPos    = vs_in[1].aFragPos;
    EmitVertex();

    gl_Position = explodedVertex( gl_in[2].gl_Position, normal );
    aTexCoord   = vs_in[2].aTexCoord;
    aNormal     = vs_in[2].aNormal;
    aFragPos    = vs_in[2].aFragPos;
    EmitVertex();

    EndPrimitive();
}