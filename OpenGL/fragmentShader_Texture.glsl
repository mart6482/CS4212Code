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
uniform sampler2D textureSampler;
uniform int useTexture;

in vec3 normal;
in vec3 vertexWorldPos;
in vec2 vTexCoord;

void main(void){
    vec4 texColor = texture(textureSampler, vTexCoord);
    if (useFlatColor == 1){
        fragmentColor = vec4(flatColor, 1.0);
        return;
    }

    if(shadingMode == 2){
        vec3 intensity = normalize(normal) * 0.5 + 0.5;
        fragmentColor = vec4(intensity, 1.0);
        return;
    }

    vec3 N = normalize(normal);
    vec3 V = normalize(cameraPos - vertexWorldPos);

    vec3 result = vec3(0.0);

    for (int i = 0; i < 2; i++){
        vec3 L = normalize(lightPosWorld[i].xyz - vertexWorldPos);
        
        vec3 diffuse;
        float diff = max(dot(N, L), 0.0);
        if(useTexture == 1){
            diffuse = diffuseComponent * texColor.rgb * diff;
        }else{
            diffuse = diffuseComponent * diff;
        }
        

        if (shadingMode == 0){
            result += diffuse;
        }
        else if(shadingMode == 1){
            vec3 H = normalize(L + V);
            float spec = pow(max(dot(N, H), 0.0), PhongExponent);
            vec3 specular = specularComponent * spec;

            result += diffuse + specular;
        }
    }

    fragmentColor = vec4(result, 1.0);
    
}