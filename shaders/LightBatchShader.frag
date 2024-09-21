#version 460

layout(location = 0) in LightData {
    flat vec2 pos;
    flat float radius;
    flat float intensity;
    flat vec4 color;
    smooth vec2 worldPos;
} lightData;

layout(location = 0) out vec4 outLight;

void main() {
    float dist = distance(lightData.worldPos, lightData.pos);
    float attenuation = clamp(1.0 - dist / lightData.radius, 0.0, 1.0);
    outLight = vec4(lightData.color.xyz, 1) * attenuation * lightData.intensity;
}