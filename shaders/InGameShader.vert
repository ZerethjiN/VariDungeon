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
    int isText;
    int isUseReflection;
    uvec2 spriteSize;
    vec2 reflectionBaseline;
};

layout(push_constant, std430) uniform VertexPushConstant {
    mat4 proj;
};

layout(std430, set = 0, binding = 0) readonly buffer ObjectBuffer {
	SSBOSpriteData spritesData[];
};

layout(location = 0) out SpriteData {
    flat vec4 color;
    smooth vec2 fragTexCoord;
    flat int textureIdx;
    flat int isUseReflection;
    flat int isUnlit;
} spriteData;

void main() {
    vec4 spritePos = vec4(spritesData[gl_InstanceIndex].vertices[gl_VertexIndex].position.xy, 0, 1);
    gl_Position = proj * spritesData[gl_InstanceIndex].model * spritePos;
    spriteData.fragTexCoord = spritesData[gl_InstanceIndex].vertices[gl_VertexIndex].texCoord.xy;
    // worldPos = (spritesData[gl_InstanceIndex].model * spritePos).xy;
    spriteData.textureIdx = spritesData[gl_InstanceIndex].textureIdx;
    spriteData.color = spritesData[gl_InstanceIndex].color;
    spriteData.isUseReflection = spritesData[gl_InstanceIndex].isUseReflection;
    spriteData.isUnlit = spritesData[gl_InstanceIndex].isUnlit;
}