#include "SDLSystem.h"
#include <GL/glew.h>
#include <print>
#include <string>
#include <stdexcept>
#include "OpenGLRender.h"
#include "VulkanRender.h"
#include <SDL2/SDL_vulkan.h>
#define GLFW_INCLUDE_VULKAN
#include <vulkan/vulkan.h>

namespace DemensDeum::Bombov {

uint SDLSystem::screenWidth = 640;
uint SDLSystem::screenHeight = 480;
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
    const char *windowTitle = "Bombov (Vulkan)";

    SDL_Vulkan_LoadLibrary(nullptr);
    SDL_Window* window = SDL_CreateWindow(
        windowTitle, 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        screenWidth, 
        screenHeight, 
        SDL_WINDOW_VULKAN
    );
    
    auto render = std::make_shared<VulkanRender>();
    render->setWindow(window);
    this->render = render;
}

void SDLSystem::quit() {
    // auto vulkanRender = static_pointer_cast<VulkanRender>(render);
    // vkDestroyDevice(vulkanRender->device, nullptr);
    // vkDestroyInstance(vulkanRender->instance, nullptr);
    // SDL_DestroyWindow(window);
    // SDL_Vulkan_UnloadLibrary();    
    // SDL_Quit();    
}

void SDLSystem::initializeOpenGL() {
    const char *windowTitle = "Bombov (OpenGL)";

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);

    window = SDL_CreateWindow(
        windowTitle, 
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
    SDL_PollEvent(&e);
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