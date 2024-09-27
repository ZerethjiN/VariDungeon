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
    int isText;
    int padding2;
    int padding3;
};

layout(push_constant, std430) uniform VertexPushConstant {
    mat4 proj;
} ubo;

layout(std430, set = 0, binding = 0) readonly buffer ObjectBuffer {
	SSBOSpriteData spritesData[];
};

layout(location = 0) out UIData {
    flat vec4 color;
    flat int textureIdx;
    smooth vec2 fragTexCoord;
    flat int isText;
} uiData;

void main() {
    gl_Position = ubo.proj * spritesData[gl_InstanceIndex].model * vec4(spritesData[gl_InstanceIndex].vertices[gl_VertexIndex].position.xy, 0, 1);
    uiData.fragTexCoord = spritesData[gl_InstanceIndex].vertices[gl_VertexIndex].texCoord.xy;
    // uiData.worldPos = (spritesData[gl_InstanceIndex].model * vec4(spritesData[gl_InstanceIndex].vertices[gl_VertexIndex].position.xy, 0, 1)).xy;
    uiData.textureIdx = spritesData[gl_InstanceIndex].textureIdx;
    uiData.color = spritesData[gl_InstanceIndex].color;
    uiData.isText = spritesData[gl_InstanceIndex].isText;
}