#version 330 core

layout(location = 0) out vec4 fragmentColor;

in vec3 fragNormal;

void main()
{
    vec3 color = fragNormal * 0.5 + 0.5;
    fragmentColor = vec4(color, 1.0);
}