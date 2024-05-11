#version 460

struct SSBOVertex {
    vec2 position;
    vec2 texCoord;
};

struct SSBOSpriteData {
    SSBOVertex vertices[4];
    mat4 model;
    vec4 color;
    int textureIdx;
    int isUnlit;
    int _padding2;
    int _padding3;
};

layout(push_constant, std430) uniform VertexPushConstant {
    mat4 proj;
} ubo;

layout(std430, set = 0, binding = 0) readonly buffer ObjectBuffer {
	SSBOSpriteData spritesData[];
};

layout(location = 0) flat out int textureIdx;
layout(location = 1) smooth out vec2 fragTexCoord;
layout(location = 2) flat out vec4 color;
layout(location = 3) flat out int isUnlit;
layout(location = 4) smooth out vec2 worldPos;

void main() {
    gl_Position = ubo.proj * spritesData[gl_InstanceIndex].model * vec4(spritesData[gl_InstanceIndex].vertices[gl_VertexIndex].position.xy, 0, 1);
    fragTexCoord = spritesData[gl_InstanceIndex].vertices[gl_VertexIndex].texCoord.xy;
    worldPos = (spritesData[gl_InstanceIndex].model * vec4(spritesData[gl_InstanceIndex].vertices[gl_VertexIndex].position.xy, 0, 1)).xy;
    textureIdx = spritesData[gl_InstanceIndex].textureIdx;
    color = spritesData[gl_InstanceIndex].color;
    isUnlit = spritesData[gl_InstanceIndex].isUnlit;
}