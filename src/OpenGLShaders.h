const std::string vertexShadersCode =
    R"(#version 100
attribute vec4 vertex;
attribute vec2 uvIn;
varying vec2 uvOut;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

void main() {
    //gl_Position = projectionMatrix * viewMatrix * modelMatrix * vertex;
    gl_Position = vertex;
    uvOut = uvIn;
})";

const std::string fragmentShadersCode = 
    R"(#version 100
    precision mediump int;
    precision mediump float;
    precision mediump sampler2D;
    precision mediump samplerCube;
    varying mediump vec2 uvOut;
    uniform sampler2D texture;
    void main() {
        //gl_FragColor = texture2D(texture, uvOut);
        gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    })";