#version 460

layout(location = 0) smooth out vec2 TexCoords;

void main() {
    TexCoords = vec2((gl_VertexIndex << 1) & 2, gl_VertexIndex & 2);
	gl_Position = vec4(TexCoords * 2.0f - 1.0f, 0.0f, 1.0f);
}