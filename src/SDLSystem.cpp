#include "SDLSystem.h"
#include <GL/glew.h>
#include <string>
#include <stdexcept>

namespace DemensDeum::Bombov {

void SDLSystem::init(GraphicsApiType graphicsApiType) {

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        std::string error = "Unable to initialize SDL: " + std::string(SDL_GetError());
        throw std::runtime_error(error);
    }

    if (graphicsApiType == OpenGL) {

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);


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
    }
}

}