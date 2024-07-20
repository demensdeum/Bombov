#include "BgfxRender.h"
#include <bgfx/platform.h>
#include "SDLSystem.h"
#include <SDL2/SDL_syswm.h>
#include <fstream>
#include <iostream>

namespace DemensDeum::Bombov
{
    bgfx::VertexLayout BgfxRender::Vertex3D_UV::ms_layout;

    std::vector<char> readFile(const std::string &filename)
    {
        std::ifstream file(filename, std::ios::ate | std::ios::binary);

        if (!file.is_open())
        {
            throw std::runtime_error("failed to open file!");
        }

        size_t fileSize = (size_t)file.tellg();
        std::vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);

        file.close();

        return buffer;
    }

    bgfx::TextureHandle BgfxRender::loadTexture(const char *filepath)
    {
        SDL_Surface *surface = SDL_LoadBMP(filepath);
        if (!surface)
        {
            throw std::runtime_error("Failed to load texture: " + std::string(SDL_GetError()));
        }

        const bgfx::Memory *mem = bgfx::alloc(surface->w * surface->h * 4);
        uint8_t *dst = (uint8_t *)mem->data;
        uint8_t *src = (uint8_t *)surface->pixels;

        for (int y = 0; y < surface->h; ++y)
        {
            for (int x = 0; x < surface->w; ++x)
            {
                uint8_t *pixel = &src[(y * surface->pitch) + (x * surface->format->BytesPerPixel)];
                dst[(y * surface->w + x) * 4 + 0] = pixel[2]; // R
                dst[(y * surface->w + x) * 4 + 1] = pixel[1]; // G
                dst[(y * surface->w + x) * 4 + 2] = pixel[0]; // B
                dst[(y * surface->w + x) * 4 + 3] = 255;      // A
            }
        }

        bgfx::TextureHandle textureHandle = bgfx::createTexture2D(
            uint16_t(surface->w),
            uint16_t(surface->h),
            false,
            1,
            bgfx::TextureFormat::RGBA8,
            0,
            mem);

        SDL_FreeSurface(surface);
        return textureHandle;
    }

    void BgfxRender::setWindow(SDL_Window *window)
    {
        this->window = window;

        SDL_SysWMinfo wmi;
        SDL_VERSION(&wmi.version);
        if (!SDL_GetWindowWMInfo(window, &wmi))
        {
            throw std::runtime_error(std::string("Can't get wmi"));
            return;
        }

        bgfx::PlatformData platformData{};
#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
        platformData.ndt = wmi.info.x11.display;
        platformData.nwh = (void *)(uintptr_t)wmi.info.x11.window;
#elif BX_PLATFORM_OSX
        pd.ndt = NULL;
        pd.nwh = wmi.info.cocoa.window;
#elif BX_PLATFORM_WINDOWS
        pd.ndt = NULL;
        pd.nwh = wmi.info.win.window;
#elif BX_PLATFORM_STEAMLINK
        pd.ndt = wmi.info.vivante.display;
        pd.nwh = wmi.info.vivante.window;
#endif
        platformData.context = NULL;
        platformData.backBuffer = NULL;
        platformData.backBufferDS = NULL;

        bgfx::Init init;
#if BGFX_MODE == BGFX_MODE_OPENGL
        init.type = bgfx::RendererType::OpenGL;
#elif BFGX_MODE == BGFX_MODE_VULKAN
        init.type = bgfx::RendererType::Vulkan;
#endif
        init.resolution.width = SDLSystem::screenWidth;
        init.resolution.height = SDLSystem::screenHeight;
        init.resolution.reset = BGFX_RESET_VSYNC;
        init.platformData = platformData;

        if (!bgfx::init(init))
        {
            throw std::runtime_error("Failed to initialize bgfx");
        }

        bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);
        bgfx::setViewRect(0, 0, 0, SDLSystem::screenWidth, SDLSystem::screenHeight);

        Vertex3D_UV::init();

        u_modelMatrix = bgfx::createUniform("u_modelMatrix", bgfx::UniformType::Mat4);
        u_viewMatrix = bgfx::createUniform("u_viewMatrix", bgfx::UniformType::Mat4);
        u_projMatrix = bgfx::createUniform("u_projectionMatrix", bgfx::UniformType::Mat4);


#if BGFX_MODE == BGFX_MODE_OPENGL
        vertexShaderCode = readFile("BgfxVertexShader.glsl");
#elif BGFX_MODE == BGFX_MODE_VULKAN
        vertexShaderCode = readFile("BgfxVertexShader.spirv");
#endif
        bgfx::ShaderHandle vertexShader = bgfx::createShader(bgfx::makeRef(vertexShaderCode.data(), vertexShaderCode.size()));
        if (!bgfx::isValid(vertexShader))
        {
            throw std::runtime_error("Failed to create vertex shader");
        }
        else {
            std::cout << "Vertex shader load success!" << std::endl;
        }

#if BGFX_MODE == BGFX_MODE_OPENGL
        fragmentShaderCode = readFile("BgfxFragmentShader.glsl");
#elif BGFX_MODE == BGFX_MODE_VULKAN
        fragmentShaderCode = readFile("BgfxFragmentShader.spirv");
#endif
        bgfx::ShaderHandle fragmentShader = bgfx::createShader(bgfx::makeRef(fragmentShaderCode.data(), fragmentShaderCode.size()));
        if (!bgfx::isValid(fragmentShader))
        {
            throw std::runtime_error("Failed to create fragment shader");
        }
        else {
            std::cout << "Fragment shader load success!" << std::endl;
        }        

        program = bgfx::createProgram(vertexShader, fragmentShader, true);

        if (!bgfx::isValid(program))
        {
            throw std::runtime_error("Failed to create program");
        }

    }

    std::vector<BgfxRender::Vertex3D_UV> BgfxRender::verticesVectorFromMap(std::shared_ptr<Map> map)
{
    std::vector<Vertex3D_UV> vertices;
    float cubeSize = 1.f;

    for (int y = 0; y < map->height; ++y)
    {
        for (int x = 0; x < map->width; ++x)
        {
            float cubeY0 = map->isSolid(x, y) ? 0 : -cubeSize;
            float cubeX0 = -cubeSize + x * cubeSize;
            float cubeZ0 = -1.f - y * cubeSize;

            float texX0 = 0.0f;
            float texY0 = 0.0f;
            float texX1 = 1.0f;
            float texY1 = 1.0f;

            // Front face
            vertices.push_back(Vertex3D_UV{cubeX0, cubeY0, cubeZ0, texX0, texY1});
            vertices.push_back(Vertex3D_UV{cubeX0, cubeY0 + cubeSize, cubeZ0, texX0, texY0});
            vertices.push_back(Vertex3D_UV{cubeX0 + cubeSize, cubeY0 + cubeSize, cubeZ0, texX1, texY0});
            vertices.push_back(Vertex3D_UV{cubeX0, cubeY0, cubeZ0, texX0, texY1});
            vertices.push_back(Vertex3D_UV{cubeX0 + cubeSize, cubeY0 + cubeSize, cubeZ0, texX1, texY0});
            vertices.push_back(Vertex3D_UV{cubeX0 + cubeSize, cubeY0, cubeZ0, texX1, texY1});

            // Back face
            vertices.push_back(Vertex3D_UV{cubeX0 + cubeSize, cubeY0, cubeZ0 + cubeSize, texX1, texY1});
            vertices.push_back(Vertex3D_UV{cubeX0, cubeY0 + cubeSize, cubeZ0 + cubeSize, texX0, texY0});
            vertices.push_back(Vertex3D_UV{cubeX0, cubeY0, cubeZ0 + cubeSize, texX0, texY1});
            vertices.push_back(Vertex3D_UV{cubeX0 + cubeSize, cubeY0, cubeZ0 + cubeSize, texX1, texY1});
            vertices.push_back(Vertex3D_UV{cubeX0 + cubeSize, cubeY0 + cubeSize, cubeZ0 + cubeSize, texX1, texY0});
            vertices.push_back(Vertex3D_UV{cubeX0, cubeY0 + cubeSize, cubeZ0 + cubeSize, texX0, texY0});

            // Top face
            vertices.push_back(Vertex3D_UV{cubeX0, cubeY0 + cubeSize, cubeZ0, texX0, texY0});
            vertices.push_back(Vertex3D_UV{cubeX0, cubeY0 + cubeSize, cubeZ0 + cubeSize, texX0, texY1});
            vertices.push_back(Vertex3D_UV{cubeX0 + cubeSize, cubeY0 + cubeSize, cubeZ0 + cubeSize, texX1, texY1});
            vertices.push_back(Vertex3D_UV{cubeX0, cubeY0 + cubeSize, cubeZ0, texX0, texY0});
            vertices.push_back(Vertex3D_UV{cubeX0 + cubeSize, cubeY0 + cubeSize, cubeZ0 + cubeSize, texX1, texY1});
            vertices.push_back(Vertex3D_UV{cubeX0 + cubeSize, cubeY0 + cubeSize, cubeZ0, texX1, texY0});

            // Bottom face
            vertices.push_back(Vertex3D_UV{cubeX0, cubeY0, cubeZ0, texX0, texY0});
            vertices.push_back(Vertex3D_UV{cubeX0 + cubeSize, cubeY0, cubeZ0 + cubeSize, texX1, texY1});
            vertices.push_back(Vertex3D_UV{cubeX0 + cubeSize, cubeY0, cubeZ0, texX1, texY0});
            vertices.push_back(Vertex3D_UV{cubeX0, cubeY0, cubeZ0, texX0, texY0});
            vertices.push_back(Vertex3D_UV{cubeX0, cubeY0, cubeZ0 + cubeSize, texX0, texY1});
            vertices.push_back(Vertex3D_UV{cubeX0 + cubeSize, cubeY0, cubeZ0 + cubeSize, texX1, texY1});

            // Left face
            vertices.push_back(Vertex3D_UV{cubeX0, cubeY0, cubeZ0, texX0, texY1});
            vertices.push_back(Vertex3D_UV{cubeX0, cubeY0, cubeZ0 + cubeSize, texX0, texY0});
            vertices.push_back(Vertex3D_UV{cubeX0, cubeY0 + cubeSize, cubeZ0, texX1, texY1});
            vertices.push_back(Vertex3D_UV{cubeX0, cubeY0 + cubeSize, cubeZ0, texX1, texY1});
            vertices.push_back(Vertex3D_UV{cubeX0, cubeY0, cubeZ0 + cubeSize, texX0, texY0});
            vertices.push_back(Vertex3D_UV{cubeX0, cubeY0 + cubeSize, cubeZ0 + cubeSize, texX1, texY0});

            // Right face
            vertices.push_back(Vertex3D_UV{cubeX0 + cubeSize, cubeY0, cubeZ0, texX1, texY1});
            vertices.push_back(Vertex3D_UV{cubeX0 + cubeSize, cubeY0 + cubeSize, cubeZ0 + cubeSize, texX0, texY0});
            vertices.push_back(Vertex3D_UV{cubeX0 + cubeSize, cubeY0, cubeZ0 + cubeSize, texX1, texY0});
            vertices.push_back(Vertex3D_UV{cubeX0 + cubeSize, cubeY0, cubeZ0, texX1, texY1});
            vertices.push_back(Vertex3D_UV{cubeX0 + cubeSize, cubeY0 + cubeSize, cubeZ0, texX0, texY1});
            vertices.push_back(Vertex3D_UV{cubeX0 + cubeSize, cubeY0 + cubeSize, cubeZ0 + cubeSize, texX0, texY0});
        }
    }

    return vertices;
}

    std::string previousRendereredSceneName = "NONE";

    void BgfxRender::setScene(std::shared_ptr<DemensDeum::Bombov::Scene> scene)
    {
        if (scene->name == previousRendereredSceneName) {
            return;
        }
        previousRendereredSceneName = scene->name;

        this->scene = scene;
        camera = scene->getCamera();

        verticesVector = verticesVectorFromMap(scene->getMap());
        vertexBuffer = bgfx::createVertexBuffer(
            bgfx::makeRef(
                verticesVector.data(),
                sizeof(decltype(verticesVector)::value_type) * verticesVector.size()),
            Vertex3D_UV::ms_layout);

        texture = loadTexture("brick.texture.bmp");
    }

    void BgfxRender::render()
    {
        std::shared_ptr<Matrix4> modelMatrix = std::make_shared<Matrix4>();
        bgfx::setUniform(u_modelMatrix, modelMatrix->glRepresentation());

        std::shared_ptr<Matrix4> viewMatrix = camera->viewMatrix();
        bgfx::setUniform(u_viewMatrix, viewMatrix->glRepresentation());

        std::shared_ptr<Matrix4> projectionMatrix = std::make_shared<Matrix4>();
        projectionMatrix->becomePerspective(45.f, SDLSystem::screenAspect, 0.001f, 800.f);
        bgfx::setUniform(u_projMatrix, projectionMatrix->glRepresentation());

        bgfx::setVertexBuffer(0, vertexBuffer);
        bgfx::setTexture(0, s_texture0, texture);

        bgfx::submit(0, program);
        bgfx::frame();
    }
}