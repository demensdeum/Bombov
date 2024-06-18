#include "OpenGLRender.h"
#include <print>
#include <vector>

#include <SDLSystem.h>
#include "OpenGLShaders.h"

namespace DemensDeum::Bombov {

OpenGLRender::OpenGLRender() {}

std::vector<OpenGLRender::Vertex> OpenGLRender::verticesVectorFromMap(std::shared_ptr<Map> map) {
  std::vector<Vertex> vertices;

  for (int y = 0; y < map->height; ++y) {
    for (int x = 0; x < map->width; ++x) {

      if (map->isSolid(x, y)) {

        float cubeX0 = x;
        float cubeY0 = y;
        float cubeZ0 = 0.0f;
        float cubeSize = 1.0f;

        float texX0 = 0.0f;
        float texY0 = 0.0f;
        float texX1 = 1.0f;
        float texY1 = 1.0f;

        // Front face
        vertices.push_back({{cubeX0, cubeY0, cubeZ0}, {texX0, texY1}});
        vertices.push_back({{cubeX0 + cubeSize, cubeY0, cubeZ0}, {texX1, texY1}});
        vertices.push_back({{cubeX0 + cubeSize, cubeY0 + cubeSize, cubeZ0}, {texX1, texY0}});
        vertices.push_back({{cubeX0, cubeY0 + cubeSize, cubeZ0}, {texX0, texY0}});
        vertices.emplace_back(vertices.back());
        vertices.emplace_back(vertices[0]);

        // Back face
        vertices.push_back({{cubeX0 + cubeSize, cubeY0, cubeZ0 + cubeSize}, {texX1, texY1}});
        vertices.push_back({{cubeX0, cubeY0, cubeZ0 + cubeSize}, {texX0, texY1}});
        vertices.push_back({{cubeX0, cubeY0 + cubeSize, cubeZ0 + cubeSize}, {texX0, texY0}});
        vertices.push_back({{cubeX0 + cubeSize, cubeY0 + cubeSize, cubeZ0 + cubeSize}, {texX1, texY0}});
        vertices.emplace_back(vertices.back());
        vertices.emplace_back(vertices[vertices.size() - 6]);

        // Top face
        vertices.push_back({{cubeX0, cubeY0 + cubeSize, cubeZ0}, {texX0, texY0}});
        vertices.push_back({{cubeX0 + cubeSize, cubeY0 + cubeSize, cubeZ0}, {texX1, texY0}});
        vertices.push_back({{cubeX0 + cubeSize, cubeY0 + cubeSize, cubeZ0 + cubeSize}, {texX1, texY1}});
        vertices.push_back({{cubeX0, cubeY0 + cubeSize, cubeZ0 + cubeSize}, {texX0, texY1}});
        vertices.emplace_back(vertices.back());
        vertices.emplace_back(vertices[vertices.size() - 8]);

        // Bottom face
        vertices.push_back({{cubeX0, cubeY0, cubeZ0}, {texX0, texY0}});
        vertices.push_back({{cubeX0 + cubeSize, cubeY0, cubeZ0}, {texX1, texY0}});
        vertices.push_back({{cubeX0 + cubeSize, cubeY0, cubeZ0 + cubeSize}, {texX1, texY1}});
        vertices.push_back({{cubeX0, cubeY0, cubeZ0 + cubeSize}, {texX0, texY1}});

        vertices.emplace_back(vertices.back());
        vertices.emplace_back(vertices[vertices.size() - 12]);

        // Left face
        vertices.push_back({{cubeX0, cubeY0, cubeZ0}, {texX0, texY1}});
        vertices.push_back({{cubeX0, cubeY0, cubeZ0 + cubeSize}, {texX0, texY0}});
        vertices.push_back({{cubeX0, cubeY0 + cubeSize, cubeZ0 + cubeSize}, {texX1, texY0}});
        vertices.push_back({{cubeX0, cubeY0 + cubeSize, cubeZ0}, {texX1, texY1}});
        vertices.emplace_back(vertices.back());
        vertices.emplace_back(vertices[vertices.size() - 16]);

        // Right face
        vertices.push_back({{cubeX0 + cubeSize, cubeY0, cubeZ0}, {texX1, texY1}});
        vertices.push_back({{cubeX0 + cubeSize, cubeY0, cubeZ0 + cubeSize}, {texX1, texY0}});
        vertices.push_back({{cubeX0 + cubeSize, cubeY0 + cubeSize, cubeZ0 + cubeSize}, {texX0, texY0}});
        vertices.push_back({{cubeX0 + cubeSize, cubeY0 + cubeSize, cubeZ0}, {texX0, texY1}});
        vertices.emplace_back(vertices.back());
        vertices.emplace_back(vertices[vertices.size() - 20]);
      }
    }
  }

  return vertices;
}

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

auto texture = SDL_LoadBMP("brick.texture.bmp");

SDL_Surface* duplicateSurface(SDL_Surface* original) {
    if (!original) {
        fprintf(stderr, "Original surface is NULL!\n");
        return NULL;
    }

    SDL_Surface* duplicate = SDL_CreateRGBSurfaceWithFormat(0, 
                                                            original->w, 
                                                            original->h, 
                                                            original->format->BitsPerPixel, 
                                                            original->format->format);
    if (!duplicate) {
        fprintf(stderr, "SDL_CreateRGBSurfaceWithFormat Error: %s\n", SDL_GetError());
        return NULL;
    }

    if (SDL_BlitSurface(original, NULL, duplicate, NULL) != 0) {
        fprintf(stderr, "SDL_BlitSurface Error: %s\n", SDL_GetError());
        SDL_FreeSurface(duplicate);
        return NULL;
    }

    return duplicate;
}

void OpenGLRender::render() {

	auto camera = scene->getCamera();

    glClearColor(0.2f, 0.35f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

	auto textureWidth = 256;
	auto textureHeight = 256;

    auto surface = duplicateSurface(texture);

	// auto surface = SDL_CreateRGBSurfaceWithFormat(
    //                                             0, 
    //                                             textureWidth, 
    //                                         	   textureHeight, 
    //                                             24, 
    //                                             SDL_PIXELFORMAT_BGR24
	// 											);

	// std::vector<Vertex> verticesVector = verticesVectorFromMap(scene->getMap());

	std::vector<Vertex> verticesVector;
    // verticesVector.push_back(Vertex{{0.f, 0.f, -2.f}, {0.0f, 0.0f}});
    // verticesVector.push_back(Vertex{{1.f, 0.f, -2.f}, {1.0f, 0.0f}});
    // verticesVector.push_back(Vertex{{0.f, -1.f, -2.f}, {0.0f, 1.0f}});

    verticesVector.push_back(Vertex{{-1.f, -1.f, 0.f}, {0.0f, 0.0f}});
    verticesVector.push_back(Vertex{{0.f, 1.f, 0.f}, {1.0f, 0.0f}});
    verticesVector.push_back(Vertex{{1.f, -1.f, 0.f}, {0.0f, 1.0f}});


	std::vector<GLuint> indicesVector;
	for (int i = 0; i < verticesVector.size(); i++) {
		indicesVector.push_back(i);
	}

    Vertex *vertices = verticesVector.data();
    GLuint *indices = indicesVector.data();

	GLsizei verticesSize = sizeof(Vertex) * verticesVector.size();
	GLsizei indicesSize = sizeof(GLuint) * indicesVector.size(); 
	GLsizei indicesCount = indicesVector.size(); // map->width * map->height * 6 sides * 2 triangles per side * 3 points per triangle

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
    glUseProgram(shader_program);

    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

	GLuint vbo, indexBuffer;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

	GLint vertexSlot = glGetAttribLocation(shader_program, "vertex");
    glVertexAttribPointer(vertexSlot, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glEnableVertexAttribArray(vertexSlot);

    GLint uvSlot = glGetAttribLocation(shader_program, "uvIn");
    glVertexAttribPointer(uvSlot, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Vertex::TextureUV));
    glEnableVertexAttribArray(uvSlot);

    auto projectionMatrix = std::make_shared<Matrix4>();
    projectionMatrix->becomePerspective(45.f, SDLSystem::screenAspect, 0, 800);
    GLint projectionMatrixUniform = glGetUniformLocation(shader_program, "projectionMatrix");
    glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, (const GLfloat *)projectionMatrix->glRepresentation());    

    auto cubesMatrix = std::make_shared<Matrix4>();
    GLint modelMatrixUniform = glGetUniformLocation(shader_program, "modelMatrix");
    glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, (const GLfloat *)cubesMatrix->glRepresentation());

    auto viewMatrix = camera->viewMatrix();
    GLint viewMatrixUniform = glGetUniformLocation(shader_program, "viewMatrix");
    glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, (const GLfloat *)viewMatrix->glRepresentation());

	glActiveTexture(GL_TEXTURE0);

	if (surface == nullptr) {
		throw std::runtime_error("CANT LOAD TEXTURE!!!");
	}

    auto surfaceLength = surface->w * surface->h * 3;

    auto palleteMode = GL_RGB;

    // in OpenGL ES 2 GL_BGR does not work

    for (auto i = 0; i < surfaceLength; i += 3) {
        auto pixels = (Uint8 *) surface->pixels;

        auto blueComponent = pixels[i];
        auto greenComponent = pixels[i + 1];
        auto redComponent = pixels[i + 2];

        pixels[i] = redComponent;
        pixels[i + 1] = greenComponent;
        pixels[i + 2] = blueComponent;
    }    

    GLuint textureBinding;
    glGenTextures(1, &textureBinding);
    glBindTexture(GL_TEXTURE_2D, textureBinding);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(
        GL_TEXTURE_2D,
        0, 
        palleteMode, 
        surface->w, 
        surface->h, 
        0, 
        palleteMode, 
        GL_UNSIGNED_BYTE, 
        surface->pixels
    );
    
	glActiveTexture(GL_TEXTURE0);

    SDL_FreeSurface(surface);

    //glEnable(GL_CULL_FACE);

    GLint textureSlot = glGetUniformLocation(shader_program, "texture");
    glUniform1i(textureSlot, 0);

    // glDrawElements(
	// 	GL_TRIANGLES, 
	// 	indicesCount,
    //     GL_UNSIGNED_INT, 
	// 	0
	// );

    glDrawArrays(
        GL_TRIANGLES,
        0,
        3
    );

    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &indexBuffer);
    glDeleteTextures(1, &textureBinding);	

    SDL_GL_SwapWindow(window);
}

}