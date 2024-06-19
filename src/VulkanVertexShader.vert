#version 310 es

layout(location = 0) in vec4 vertex;
layout(location = 1) in vec2 uvIn;
layout(location = 0) out vec2 uvOut;

layout(set = 0, binding = 0) uniform UBO {
    mat4 projectionMatrix;
    mat4 viewMatrix;
    mat4 modelMatrix;
} ubo;

void main() {
    gl_Position = ubo.projectionMatrix * ubo.viewMatrix * ubo.modelMatrix * vertex;
    // gl_Position = vertex;
    uvOut = uvIn;
}
