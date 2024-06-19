#include "Render.h"
#include <SDL2/SDL.h>
#include <vulkan/vulkan.hpp>

namespace DemensDeum::Bombov {

class VulkanRender: public Render {

public:
    void setWindow(SDL_Window *window);
    void setScene(std::shared_ptr<Scene> scene) override;
    void render() override;

    VkInstance vkInst;
    VkDevice device;
};

}