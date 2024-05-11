#version 460
#extension GL_EXT_nonuniform_qualifier : require

layout(set = 0, binding = 2) uniform sampler2D texSampler[];

layout(push_constant, std430) uniform FragmentPushConstant {
    layout(offset = 64) vec4 ambientColor;
    int nbLights;
};

struct Light {
    vec2 pos;
    float radius;
    float intensity;
    vec4 color;
};

layout(std430, set = 0, binding = 1) readonly buffer lightBuffer {
    Light lights[];
};

layout(location = 0) flat in int textureIdx;
layout(location = 1) smooth in vec2 fragTexCoord;
layout(location = 2) flat in vec4 color;
layout(location = 3) flat in int isUnlit;
layout(location = 4) smooth in vec2 worldPos;

layout(location = 0) out vec4 outColor;

vec4 diffuseApplication() {
    vec4 diffusetotal = vec4(0, 0, 0, 1.0);

    for (int i = 0; i < nbLights; i++) {
        float dist = distance(worldPos, lights[i].pos);
        if (dist <= lights[i].radius) {
            float attenuation = clamp(1.0 - dist / lights[i].radius, 0.0, 1.0);
            diffusetotal += vec4(lights[i].color.xyz * attenuation * lights[i].intensity, 1);
        }
    }

    return vec4(ambientColor.xyz, 1.0) + diffusetotal;
}

void main() {
    vec4 pixel = texture(texSampler[textureIdx], fragTexCoord);
    if (isUnlit == 0) {
        outColor = color * pixel * vec4(diffuseApplication().xyz, 1);
    } else {
        outColor = color * pixel;
    }
}