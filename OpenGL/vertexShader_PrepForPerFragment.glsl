#version 330 core

layout(location=0) in vec3 in_Position;
layout(location=1) in vec3 in_Normal;

uniform mat4 projMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 normalMatrix;

out vec3 normal;
out vec3 vertexWorldPos;

void main(void)
{
    normal = normalize((normalMatrix * vec4(in_Normal, 0.0)).xyz);
    vertexWorldPos = (modelMatrix * vec4(in_Position, 1.0)).xyz;

    gl_Position = projMatrix * viewMatrix * vec4(vertexWorldPos, 1.0);
}