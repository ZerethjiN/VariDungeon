#version 460
#define M_PI 3.1415926535897932384626433832795

precision highp float;

layout(location = 0) smooth in vec2 TexCoords;

layout(push_constant, std430) uniform FragmentPushConstant {
    ivec2 screenSize;
    vec2 aberationDirection;
    float aberationOffset;
    float seed;
};

layout(set = 0, binding = 0) uniform sampler2D texSampler;

layout(location = 0) out vec4 outColor;

//// ScanLine ////

vec2 curveRemapUV() {
    vec2 uv = TexCoords * 2.0 - 1.0;
    vec2 offset = abs(uv.yx) / vec2(8.0, 8.0);
    uv = uv + uv * offset * offset;
    uv = uv * 0.5 + 0.5;
    return uv;
}

vec4 scanLine(float uv, float resolution, float opacity) {
    float intensity = sin(uv * resolution * M_PI * 2.0);
    intensity = ((0.5 * intensity) + 0.5) * 0.9 + 0.1;
    return vec4(vec3(pow(intensity, opacity)), 1.0);
}

//// Noise ////

// float random(vec2 st) {
//     return fract(sin(dot(st.xy, vec2(12.9898,78.233))) * 43758.5453123);
// }

const float PHI = 1.61803398874989484820459;

float gold_noise(vec2 xy, float seed) {
    return fract(tan(distance(xy * PHI, xy) * seed) * xy.x);
}

//// Vignette ////

vec4 vignette(float opacity, float roundness) {
    float intensity = TexCoords.x * TexCoords.y * (1.0 - TexCoords.x) * (1.0 - TexCoords.y);
    return vec4(vec3(clamp(pow((screenSize.x / roundness) * intensity, opacity), 0.0, 1.0)), 1.0);
    // return clamp(pow((screenSize.x / roundness) * intensity, opacity), 0.0, 1.0);
}

const float brightness = 1.5;

void main() {
    vec4 rValue = texture(texSampler, vec2(TexCoords.x + (aberationDirection.x * aberationOffset / screenSize.x), TexCoords.y + (aberationDirection.y * aberationOffset / screenSize.y)));
    vec4 gValue = texture(texSampler, TexCoords);
    vec4 bValue = texture(texSampler, vec2(TexCoords.x + (aberationDirection.x * aberationOffset / screenSize.x), TexCoords.y + (aberationDirection.y * aberationOffset / screenSize.y)));
    vec4 color = vec4(rValue.r, gValue.g, bValue.b, 1);
    // color *= vec4(clamp(vec3(gold_noise(TexCoords * screenSize, seed + 0.1f)), 0.5, 1.0), 1.0);
    // color *= vignette(0.5, 10.0);// * vec4(1, 0, 0, 1);
    // color *= scanLine(TexCoords.y / 4, screenSize.y, 0.25);
    // color *= scanLine(TexCoords.x / 4, screenSize.x, 0.25);
    // color *= brightness;

    // vec4 vignetteColor = vec4(1, 0, 0, 1);
    // vignetteColor *= (1.0 - vignette(0.5, 10.0));

    outColor = vec4(color.rgb, 1);
}