#version 460
#extension GL_EXT_nonuniform_qualifier : require

layout(set = 0, binding = 1) uniform sampler2D texSampler[];

layout(location = 0) in SpriteData {
    flat vec4 color;
    smooth vec2 fragTexCoord;
    flat int textureIdx;
    flat int isUseReflection;
    flat int isUnlit;
} spriteData;

layout(location = 0) out vec4 outColor;
layout(location = 1) out vec4 outUnlit;

void main() {
    vec4 pixel = texture(texSampler[spriteData.textureIdx], spriteData.fragTexCoord);
    float reflectness = 1.0f;
    // if (spriteData.isUseReflection != 0) {
    //     reflectness = 0.5f;
    // }

    outColor = spriteData.color * pixel * reflectness;
    outUnlit = vec4(spriteData.isUnlit) * outColor.w;
}