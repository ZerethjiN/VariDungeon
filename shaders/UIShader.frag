#version 460
#extension GL_EXT_nonuniform_qualifier : require

layout(set = 0, binding = 1) uniform sampler2D texSampler[];

layout(location = 0) in UIData {
    flat int textureIdx;
    smooth vec2 fragTexCoord;
    flat vec4 color;
} uiData;

layout(location = 0) out vec4 outColor;

void main() {
    vec4 pixel = texture(texSampler[uiData.textureIdx], uiData.fragTexCoord);
    outColor = uiData.color * pixel;
}