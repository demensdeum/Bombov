#include "OpenGLRender.h"
#include <print>
#include <vector>

namespace DemensDeum::Bombov {

const std::string vertexShadersCode =
    R"(#version 100
attribute vec4 vertex;
attribute vec2 uvIn;
varying vec2 uvOut;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

void main() {
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vertex;
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
        gl_FragColor = texture2D(texture, uvOut);
    })";

typedef struct {
    GLfloat Position[3];
	GLfloat TextureUV[2];
} Vertex;

OpenGLRender::OpenGLRender() {}

void OpenGLRender::setWindow(SDL_Window *window) {
    this->window = window;
}

void OpenGLRender::setScene(std::shared_ptr<Scene> scene) {
    this->scene = scene;
}

void OpenGLRender::CheckCompileErrors(GLuint object, const std::string objectType)
{
	GLint success;
	GLchar infoLog[1024];

	glGetShaderiv(object, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(object, 1024, NULL, infoLog);
		throw std::runtime_error("Error while compiling " + objectType + " shader: " + infoLog);
	}
}

void OpenGLRender::CheckLinkErrors(GLint programID)
{
	GLint success;
	GLchar infoLog[1024];

	glGetProgramiv(programID, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(programID, 1024, NULL, infoLog);
		throw std::runtime_error("Error while linking shader: " + std::string(infoLog));
	}
}

void OpenGLRender::render() {

    glClearColor(0.2f, 0.35f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

	auto textureWidth = 256;
	auto textureHeight = 256;

	auto surface = SDL_CreateRGBSurfaceWithFormat(
                                                0, 
                                                textureWidth, 
                                            	textureHeight, 
                                                24, 
                                                SDL_PIXELFORMAT_RGB24
												);

	std::vector<Vertex> verticesVector;
	std::vector<GLuint> indicesVector;

	for (uint32_t i = 0; i < 8; i++)
	{
		float u = 0;
		float v = 0;

		Vertex vertex;
		vertex.Position[0] = 1;
		vertex.Position[1] = 1;
		vertex.Position[2] = 1;
		vertex.TextureUV[0] = u;
		vertex.TextureUV[1] = v;

		verticesVector.push_back(vertex);
		indicesVector.push_back(i);
	}

    Vertex *vertices = verticesVector.data();
    GLuint *indices = indicesVector.data();

	GLsizei verticesSize = sizeof(Vertex) * verticesVector.size();
	GLsizei indicesSize = sizeof(GLuint) * indicesVector.size(); 
	GLsizei indicesCount = indicesVector.size();

	GLuint vertexShaderID, fragmentShaderID, GeometryShaderID;
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

	auto vc = vertexShadersCode.c_str();
	glShaderSource(vertexShaderID, 1, &vc, NULL);

	glCompileShader(vertexShaderID);
    
	CheckCompileErrors(vertexShaderID, "Vertex");

	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	auto fc = fragmentShadersCode.c_str();
	glShaderSource(fragmentShaderID, 1, &fc, NULL);
	glCompileShader(fragmentShaderID);
	CheckCompileErrors(fragmentShaderID, "Fragment");

	auto programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);
	CheckLinkErrors(programID);

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	GLuint shader_program = programID;
	GLint pos = glGetAttribLocation(shader_program, "vertex");

    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

	GLuint vbo, indexBuffer;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glEnableVertexAttribArray(pos);

    glUseProgram(shader_program);

    auto modelMatrix = cubeMatrix;
    GLint modelMatrixUniform = glGetUniformLocation(shader_program, "modelMatrix");
    glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, modelMatrix->glRepresentation());

    auto viewMatrix = camera->matrix();
    GLint viewMatrixUniform = glGetUniformLocation(shader_program, "viewMatrix");
    glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix->glRepresentation());

	glActiveTexture(GL_TEXTURE0);

    GLint uvSlot = glGetAttribLocation(shader_program, "uvIn");
    glVertexAttribPointer(uvSlot, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) (sizeof(Vertex::Position)));
    glEnableVertexAttribArray(uvSlot);

	if (surface == nullptr) {
		throw std::runtime_error("CANT LOAD TEXT_TEXTURE!!!");
	}

    auto surfaceLength = surface->w * surface->h * 3;

    auto palleteMode = GL_BGR;

    GLuint textureBinding;
    glGenTextures(1, &textureBinding);
    glBindTexture(GL_TEXTURE_2D, textureBinding);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, palleteMode, surface->w, surface->h, 0, palleteMode, GL_UNSIGNED_BYTE, surface->pixels);
    
	glActiveTexture(GL_TEXTURE0);

    SDL_FreeSurface(surface);

    glEnable(GL_CULL_FACE);

    GLint textureSlot = glGetUniformLocation(shader_program, "texture");
    glUniform1i(textureSlot, 0);

    glDrawElements(
		GL_TRIANGLES, 
		indicesCount,
        GL_UNSIGNED_INT, 
		0
	);

    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &indexBuffer);
    glDeleteTextures(1, &textureBinding);	

    SDL_GL_SwapWindow(window);
}

}