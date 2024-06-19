#version 310 es
precision mediump int;
precision mediump float;

// Specify locations for user inputs and outputs
layout(location = 0) in mediump vec2 uvOut;
layout(location = 0) out vec4 fragColor;

// Specify binding for the sampler uniform
layout(binding = 0) uniform sampler2D uTexture;

void main() {
    fragColor = texture(uTexture, uvOut);
    //fragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
