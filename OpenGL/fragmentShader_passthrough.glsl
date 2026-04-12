#version 330 core

layout(location=0) out vec4 fragmentColor;

uniform vec3 diffuseComponent;
uniform vec3 specularComponent;
uniform float PhongExponent;
uniform vec3 cameraPos;

in vec4 normal;
in vec4 lightDir;
in vec4 vertexWorldPos;

void main(void){

    //calculate important vectors
    vec3 N = normalize(normal.xyz);
    vec3 L = normalize(lightDir.xyz);
    vec3 V = normalize(cameraPos - vertexWorldPos.xyz);
    vec3 H = normalize(L + V);

    //diffuse component
    float val = max(0.0, dot(N, L));
    vec3 diffuseShading = vec3( diffuseComponent.r * val, diffuseComponent.g * val, diffuseComponent.b * val );

    //Blinn-Phong component
    float spec = pow(max(dot(N, H), 0.0), PhongExponent);
    vec3 specularShading = specularComponent * spec;
    

    fragmentColor = vec4(diffuseShading + specularShading, 1.0);
}