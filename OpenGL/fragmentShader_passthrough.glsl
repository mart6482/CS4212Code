#version 330 core

layout(location=0) out vec4 fragmentColor;

uniform vec3 diffuseComponent;
uniform vec3 specularComponent;
uniform float PhongExponent;
uniform vec3 cameraPos;

uniform vec4 lightPosWorld[2];

uniform int shadingMode;
uniform int useFlatColor;
uniform vec3 flatColor;

in vec3 normal;
in vec3 vertexWorldPos;

void main(void){
    if (useFlatColor == 1){
        fragmentColor = vec4(flatColor, 1.0);
        return;
    }

    vec3 N = normalize(normal);
    vec3 V = normalize(cameraPos - vertexWorldPos);

    vec3 result = vec3(0.0);

    for (int i = 0; i < 2; i++){
        vec3 L = normalize(lightPosWorld[i].xyz - vertexWorldPos);

        float diff = max(dot(N, L), 0.0);
        vec3 diffuse = diffuseComponent * diff;

        if (shadingMode == 0){
            result += diffuse;
        }
        else{
            vec3 H = normalize(L + V);
            float spec = pow(max(dot(N, H), 0.0), PhongExponent);
            vec3 specular = specularComponent * spec;

            result += diffuse + specular;
        }
    }

    fragmentColor = vec4(result, 1.0);
}