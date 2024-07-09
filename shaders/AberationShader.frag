#version 460

layout(location = 0) smooth in vec2 TexCoords;
layout(location = 1) smooth in vec2 worldPos;

layout(set = 0, binding = 0) uniform sampler2D screenTexture;
layout(push_constant, std430) uniform FragmentPushConstant {
    layout(offset = 72) ivec2 screenSize;
    vec2 aberationDirection;
    float aberationOffset;
    float _padding1;
} ubo;

layout(location = 0) out vec4 outColor;

void main() {
    vec4 rValue = texture(screenTexture, vec2(TexCoords.x + (ubo.aberationDirection.x * ubo.aberationOffset / ubo.screenSize.x), TexCoords.y + (ubo.aberationDirection.y * ubo.aberationOffset / ubo.screenSize.y)));
    vec4 gValue = texture(screenTexture, TexCoords);
    vec4 bValue = texture(screenTexture, vec2(TexCoords.x + (ubo.aberationDirection.x * ubo.aberationOffset / ubo.screenSize.x), TexCoords.y + (ubo.aberationDirection.y * ubo.aberationOffset / ubo.screenSize.y)));
    vec4 color = vec4(rValue.r, gValue.g, bValue.b, 1);

    outColor = vec4(color.x, color.y, color.z, 1);
}