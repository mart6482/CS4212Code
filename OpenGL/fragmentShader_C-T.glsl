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

uniform float roughness;
uniform vec3 albedo;
uniform float metallic;

in vec3 normal;
in vec3 vertexWorldPos;

const float PI = 3.14159265;

//GGX Distribution (D)
float DistGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness * roughness;
    float a2 = a * a;

    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH * NdotH;   // <-- FIXED missing semicolon

    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return a2 / denom;
}

//Geometry (G)
float GeometryGGX(float NdotX, float roughness)
{
    float r = roughness + 1.0;
    float k = (r * r) / 8.0;

    return NdotX / (NdotX * (1.0 - k) + k);
}

float GeometryFinal(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);

    float ggxV = GeometryGGX(NdotV, roughness); 
    float ggxL = GeometryGGX(NdotL, roughness);

    return ggxV * ggxL;
}

//Fresnel Value (F)
vec3 FresnelApprox(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

void main(void)
{
    if (useFlatColor == 1)
    {
        fragmentColor = vec4(flatColor, 1.0);
        return;
    }

    if (shadingMode == 2)
    {
        vec3 intensity = normalize(normal) * 0.5 + 0.5;
        fragmentColor = vec4(intensity, 1.0);
        return;
    }

    vec3 N = normalize(normal);
    vec3 V = normalize(cameraPos - vertexWorldPos);

    vec3 albedoColor = albedo;
    vec3 F0 = vec3(0.04);
    F0 = mix(F0, albedoColor, metallic);

    vec3 result = vec3(0.0);

    for (int i = 0; i < 2; i++)
    {
        vec3 L = normalize(lightPosWorld[i].xyz - vertexWorldPos);
        vec3 H = normalize(V + L);

        float NdotL = max(dot(N, L), 0.0);
        // Cook-Torrance BRDF
        float D = DistGGX(N, H, roughness);
        float G = GeometryFinal(N, V, L, roughness);
        vec3  F = FresnelApprox(max(dot(H, V), 0.0), F0);

        vec3 numerator = D * G * F;

        float denom = 4.0 * max(dot(N, V), 0.0) * NdotL + 0.001;

        vec3 specular = numerator / denom;

        // energy conservation
        vec3 kS = F;
        vec3 kD = (1.0 - kS) * (1.0 - metallic);

        vec3 diffuse = kD * albedoColor / PI;

        result += (diffuse + specular) * NdotL;
    }

    fragmentColor = vec4(result, 1.0);
}