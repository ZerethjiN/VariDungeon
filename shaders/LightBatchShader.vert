#version 460

struct Light {
    mat4 model;
    vec2 pos;
    float radius;
    float intensity;
    vec4 color;
};

layout(push_constant, std430) uniform VertexPushConstant {
    mat4 proj;
};

layout(std430, set = 0, binding = 0) readonly buffer lightBuffer {
    Light lights[];
};

layout(location = 0) out LightData {
    flat vec2 pos;
    flat float radius;
    flat float intensity;
    flat vec4 color;
    smooth vec2 worldPos;
} lightData;

const vec2[4] lightRectPos = {
    vec2(-1, -1),
    vec2(-1, +1),
    vec2(+1, -1),
    vec2(+1, +1)
};

void main() {
    vec4 spriteCorner = vec4(lightRectPos[gl_VertexIndex] * lights[gl_InstanceIndex].radius, 0, 1);
    gl_Position = proj * lights[gl_InstanceIndex].model * spriteCorner;
    lightData.worldPos = (lights[gl_InstanceIndex].model * spriteCorner).xy;

    lightData.pos = lights[gl_InstanceIndex].pos;
    lightData.radius = lights[gl_InstanceIndex].radius;
    lightData.intensity = lights[gl_InstanceIndex].intensity;
    lightData.color = lights[gl_InstanceIndex].color;
}