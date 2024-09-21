#version 460

layout(input_attachment_index = 0, set = 0, binding = 0) uniform subpassInput inputColor;
layout(input_attachment_index = 1, set = 0, binding = 1) uniform subpassInput inputUnlit;
layout(input_attachment_index = 2, set = 0, binding = 2) uniform subpassInput inputLight;
layout(push_constant, std430) uniform FragmentPushConstant {
    vec4 ambientColor;
};

layout(location = 0) out vec4 outColor;

vec4 diffuseApplication() {
    return vec4(ambientColor.xyz, 1.0) + subpassLoad(inputLight);
}

void main() {
    if (subpassLoad(inputUnlit).x != 0.f) {
        outColor = vec4(subpassLoad(inputColor).xyz, 1);
    } else {
        outColor = vec4(subpassLoad(inputColor).xyz, 1) * vec4(diffuseApplication().xyz, 1);
    }
}