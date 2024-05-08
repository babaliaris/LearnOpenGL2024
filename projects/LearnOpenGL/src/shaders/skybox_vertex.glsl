#version 330 core

layout(location=0) in vec3 m_Position;

out vec3 m_TexCoord;

uniform mat4 u_view;
uniform mat4 u_proj;

void main()
{
    //Remember, position.w is being set by the projection matrix!!!
    //even that we specify 1.0f in vec4(m_Position, 1.0f)!!!!!!!!!!
    vec4 clip_space_pos = u_proj * u_view * vec4(m_Position, 1.0f);

    //Make sure perspective division is always 1 : z/w = w/w = 1.
    gl_Position = clip_space_pos.xyww;

    m_TexCoord = m_Position;
}