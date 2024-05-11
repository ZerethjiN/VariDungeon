#version 460

layout(location = 0) smooth in vec2 TexCoords;
layout(location = 1) smooth in vec2 worldPos;

layout(set = 0, binding = 0) uniform sampler2D screenTexture;
layout(push_constant, std430) uniform FragmentPushConstant {
    layout(offset = 72) ivec2 screenSize;
    float aberationOffset;
    int nbShockwaves;
} ubo;

struct Shockwave {
    vec2 pos;
    float radius;
    float amplitude;
    float refraction;
    float padding1;
    float padding2;
    float padding3;
};

layout(std430, set = 0, binding = 1) readonly buffer shockwaveBuffer {
    Shockwave shockwaves[];
};

layout(location = 0) out vec4 outColor;

vec2 shockwaveApplication() {
    vec2 shockwaveTotal = vec2(0, 0);

    // vec4 worldPos = vec4(ubo.cameraPos, 0, 1) + vec4((TexCoords * 2.0f - 1.0f) * ubo.screenSize * 0.5, 0, 1);
    vec2 newWorldPos = worldPos - ubo.screenSize * 0.5; // ((TexCoords * 2.0f - 1.0f) * ubo.screenSize * 0.5);

    for (int i = 0; i < ubo.nbShockwaves; i++) {
        // vec2 secondPos = (shockwaves[i].pos) + ((TexCoords * 2.0f - 1.0f) + ubo.screenSize * 0.5);

        float dist = distance(newWorldPos, shockwaves[i].pos);
        if (dist <= shockwaves[i].radius) {
            float powDiff = 1.0 - pow(abs(dist * shockwaves[i].amplitude), shockwaves[i].refraction);
            float diffTime = dist * powDiff;
            vec2 diffUV = normalize(newWorldPos - shockwaves[i].pos);
            shockwaveTotal += (diffUV * diffTime);
        }
    }

    return shockwaveTotal;
}

void main() {
    vec2 newTexCoords = TexCoords;
    // newTexCoords += shockwaveApplication();

    vec4 rValue = texture(screenTexture, vec2(newTexCoords.x + (ubo.aberationOffset / ubo.screenSize.x), newTexCoords.y));
    vec4 gValue = texture(screenTexture, newTexCoords);
    vec4 bValue = texture(screenTexture, vec2(newTexCoords.x + (ubo.aberationOffset / ubo.screenSize.x), newTexCoords.y));
    vec4 color = vec4(rValue.r, gValue.g, bValue.b, 1);

    outColor = vec4(color.x, color.y, color.z, 1);
}