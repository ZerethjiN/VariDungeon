#version 460
#extension GL_EXT_nonuniform_qualifier : require

layout(set = 0, binding = 1) uniform sampler2D texSampler[];

layout(location = 0) flat in int textureIdx;
layout(location = 1) smooth in vec2 fragTexCoord;
layout(location = 2) flat in vec4 color;
layout(location = 3) smooth in vec2 worldPos;

layout(location = 0) out vec4 outColor;

void main() {
    vec4 pixel = texture(texSampler[textureIdx], fragTexCoord);
    outColor = color * pixel.r;
}