#include "SDLSystem.h"
#include <GL/glew.h>
#include <string>
#include <stdexcept>
#include "OpenGLRender.h"
#include "VulkanRender.h"

namespace DemensDeum::Bombov {

int SDLSystem::screenWidth = 640;
int SDLSystem::screenHeight = 480;
float SDLSystem::screenAspect = (float)screenWidth / (float)screenHeight;

void SDLSystem::init(GraphicsApiType graphicsApiType) {

    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        std::string error = "Unable to initialize SDL: " + std::string(SDL_GetError());
        throw std::runtime_error(error);
    }

    switch (graphicsApiType) {
        case OpenGL:
            initializeOpenGL();
            break;
        case Vulkan:
            initializeVulkan();
            break;
        case BGFX:
            throw std::runtime_error("BGFX render does not implemented");
            break;
    }
}

void SDLSystem::initializeVulkan() {
    auto render = std::make_shared<VulkanRender>();
    this->render = render;
}

void SDLSystem::initializeOpenGL() {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);

    window = SDL_CreateWindow(
        "Bombov", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        640, 
        480, 
        SDL_WINDOW_OPENGL
    );
    
    auto glContext = SDL_GL_CreateContext(window);

    if (glContext == NULL)
    {
        std::string error = "SDL_GL_CreateContext: " + std::string(SDL_GetError());
        throw std::runtime_error(error);
    }

    GLenum result = glewInit();

    if (result != GLEW_OK)
    {
        std::string error = "Error: %s\n" + std::string((const char *)glewGetErrorString(result));
        throw std::runtime_error(error);
    }

    SDL_GL_MakeCurrent(window, glContext);

    auto render = std::make_shared<OpenGLRender>();
    render->setWindow(window);
    this->render = render;    
}

void SDLSystem::pollEvents() {
    SDL_Event e;
    if (SDL_PollEvent(&e) != 0) {    
        if (e.type == SDL_QUIT) {
            pressedButtons.exitFromGame = true;
        }
        if (e.type == SDL_KEYDOWN){
            if (e.key.keysym.sym == SDLK_UP) {
                pressedButtons.forward = true;
            }
            if (e.key.keysym.sym == SDLK_DOWN) {
                pressedButtons.back = true;
            }
            if (e.key.keysym.sym == SDLK_LEFT) {
                pressedButtons.left = true;
            }
            if (e.key.keysym.sym == SDLK_RIGHT) {
                pressedButtons.right = true;
            }
        }
        if (e.type == SDL_KEYUP) {
            if (e.key.keysym.sym == SDLK_UP) {
                pressedButtons.forward = false;
            }
            if (e.key.keysym.sym == SDLK_DOWN) {
                pressedButtons.back = false;
            }
            if (e.key.keysym.sym == SDLK_LEFT) {
                pressedButtons.left = false;
            }
            if (e.key.keysym.sym == SDLK_RIGHT) {
                pressedButtons.right = false;
            }            
        }
    }
}

}