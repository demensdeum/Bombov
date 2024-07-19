#include "BgfxRender.h"
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include "SDLSystem.h"
#include <SDL2/SDL_syswm.h>

namespace DemensDeum::Bombov {
void BgfxRender::setWindow(SDL_Window *window) {
    this->window = window;

    SDL_SysWMinfo wmi;
    SDL_VERSION(&wmi.version);
    if (!SDL_GetWindowWMInfo(window, &wmi)) {
        throw std::runtime_error(std::string("Can't get wmi"));
        return;
    }

    bgfx::PlatformData platformData {};
#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
    platformData.ndt = wmi.info.x11.display;
    platformData.nwh = (void*)(uintptr_t)wmi.info.x11.window;
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
    init.type = bgfx::RendererType::Count;
    init.resolution.width = SDLSystem::screenWidth;
    init.resolution.height = SDLSystem::screenHeight;
    init.resolution.reset = BGFX_RESET_VSYNC;
    init.platformData = platformData;

    bgfx::init(init);
    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);  
    bgfx::setViewRect(0, 0, 0, SDLSystem::screenWidth, SDLSystem::screenHeight);
}

void BgfxRender::setScene(std::shared_ptr<DemensDeum::Bombov::Scene> scene) {
    this->scene = scene;
}

void BgfxRender::render() {
    bgfx::touch(0);
    bgfx::frame();
}
}