#pragma once

#define GLFW_INCLUDE_VULKAN
#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>
#include <vulkan/vulkan.h>

#include <iostream>
#include <stdexcept>
#include <vector>
#include <optional>
#include <cstdint>
#include <fstream>
#include "Render.h"

#include <memory>
#include <vector>
#include "Vertex.h"

#include <vulkan/vulkan.h>
#include <functional>

namespace DemensDeum::Bombov {

class VulkanRender: public Render {
public:
    void setWindow(SDL_Window *window);

    void setScene(std::shared_ptr<Scene> scene) override;
    void render() override;

private:

    void updateUniformBuffer(VkDeviceMemory uniformBufferMemory, VkDevice device);

    uint32_t submissionNr = 0;
VkDeviceMemory uniformBufferMemory;

  VkSwapchainKHR swapchain;
  std::vector<VkImageView> swapchainImageViews;
  std::vector<VkFramebuffer> framebuffers;

    VkDevice device;
  VkPipeline pipeline = VK_NULL_HANDLE;

    std::vector<Vertex3D_UV> cube;

  std::vector<VkLayerProperties> supportedLayers;
  std::vector<const char *> requestedLayers;

    VkQueue graphicsQueue;
    VkQueue presentQueue;
    std::vector<VkFence> submissionFences;
    std::vector<VkSemaphore> oldImageReadySs;
    std::vector<VkSemaphore> imageReadySs;
    std::vector<VkSemaphore> renderDoneSs;
    std::vector<VkCommandBuffer> commandBuffers;

    SDL_Window *window = nullptr;
    bool initialized = false;
    std::function<void(void)> renderClosure;
    int start(SDL_Window *window);

    std::shared_ptr<Scene> scene;
};

}