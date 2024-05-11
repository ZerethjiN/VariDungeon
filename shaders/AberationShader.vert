#version 460

layout(push_constant, std430) uniform VertexPushConstant {
    mat4 proj;
    vec2 cameraPos;
} ubo;

layout(location = 0) smooth out vec2 TexCoords;
layout(location = 1) smooth out vec2 worldPos;

void main() {
    TexCoords = vec2((gl_VertexIndex << 1) & 2, gl_VertexIndex & 2);
	gl_Position = vec4(TexCoords * 2.0f - 1.0f, 0.0f, 1.0f);
    worldPos = (ubo.proj * vec4(ubo.cameraPos, 0, 1)).xy;
}