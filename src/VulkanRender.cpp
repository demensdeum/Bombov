#include "VulkanRender.h"
#include <print>
#include <SDL2/SDL_vulkan.h>

namespace DemensDeum::Bombov {

void VulkanRender::setWindow(SDL_Window *window) {
    uint32_t extensionCount;
    const char** extensionNames = 0;
    SDL_Vulkan_GetInstanceExtensions(window, &extensionCount, nullptr);
    extensionNames = new const char *[extensionCount];
    SDL_Vulkan_GetInstanceExtensions(window, &extensionCount, extensionNames);
    
    VkInstanceCreateInfo instInfo = {};
    instInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instInfo.pNext = nullptr;
    instInfo.flags = 0;
    instInfo.pApplicationInfo = nullptr;
    instInfo.enabledLayerCount = 0;
    instInfo.ppEnabledLayerNames = nullptr;
    instInfo.enabledExtensionCount = extensionCount;
    instInfo.ppEnabledExtensionNames = extensionNames;

    VkInstance vkInst;
    vkCreateInstance(&instInfo, nullptr, &vkInst);

    uint32_t physicalDeviceCount;
    vkEnumeratePhysicalDevices(vkInst, &physicalDeviceCount, nullptr);
    std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);
    vkEnumeratePhysicalDevices(vkInst, &physicalDeviceCount, physicalDevices.data());
    VkPhysicalDevice physicalDevice = physicalDevices[0];

    uint32_t queueFamilyCount;
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);
    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

    VkSurfaceKHR surface;
    SDL_Vulkan_CreateSurface(window, vkInst, &surface);

    uint32_t graphicsQueueIndex = UINT32_MAX;
    uint32_t presentQueueIndex = UINT32_MAX;
    VkBool32 support;
    uint32_t i = 0;
    for (VkQueueFamilyProperties queueFamily : queueFamilies) {
        if (graphicsQueueIndex == UINT32_MAX && queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            graphicsQueueIndex = i;
        }
        if (presentQueueIndex == UINT32_MAX) {
            vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surface, &support);
            if(support) {
                presentQueueIndex = i;
            }
        }
        ++i;
    }

    float queuePriority = 1.0f;
    VkDeviceQueueCreateInfo queueInfo = {};
    queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueInfo.pNext = nullptr;
    queueInfo.flags = 0;
    queueInfo.queueFamilyIndex = graphicsQueueIndex;
    queueInfo.queueCount = 1;
    queueInfo.pQueuePriorities = &queuePriority;
    
    VkPhysicalDeviceFeatures deviceFeatures = {};
    const char* deviceExtensionNames[] = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
    VkDeviceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pNext = nullptr;
    createInfo.flags = 0;
    createInfo.queueCreateInfoCount = 1;
    createInfo.pQueueCreateInfos = &queueInfo;
    createInfo.enabledLayerCount = 0;
    createInfo.ppEnabledLayerNames = nullptr;
    createInfo.enabledExtensionCount = 1;
    createInfo.ppEnabledExtensionNames = deviceExtensionNames;
    createInfo.pEnabledFeatures = &deviceFeatures;

    VkDevice device;
    vkCreateDevice(physicalDevice, &createInfo, nullptr, &device);

    VkQueue graphicsQueue;
    vkGetDeviceQueue(device, graphicsQueueIndex, 0, &graphicsQueue);

    VkQueue presentQueue;
    vkGetDeviceQueue(device, presentQueueIndex, 0, &presentQueue);

    SDL_Log("Initialized with errors: %s", SDL_GetError());

    VkPipelineLayout pipelineLayout = VK_NULL_HANDLE;

	VkPipelineLayoutCreateInfo		pipelineLayoutInfo = {};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = 0;

	if (
        vkCreatePipelineLayout(
            device, 
            &pipelineLayoutInfo, 
            nullptr, 
            &pipelineLayout
    ) != VK_SUCCESS) {
		throw std::runtime_error("Pipeline: failed to create pipeline layout!");
    }

	VkShaderModule	shader = VK_NULL_HANDLE;
	Data shaderSource("shaders/test-compute.comp.spv" );

	VkShaderModuleCreateInfo moduleCreateInfo = {};

	moduleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	moduleCreateInfo.codeSize = shaderSource.getLength();
	moduleCreateInfo.pCode = reinterpret_cast<const uint32_t*>( shaderSource.getPtr());

	if (
        vkCreateShaderModule(
            device, &moduleCreateInfo, nullptr, &shader ) != VK_SUCCESS ) {
        throw std::runtime_error("Failed to create shader module!");
    }
		

	VkPipelineShaderStageCreateInfo stageInfo = {};	
	stageInfo.sType     = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	stageInfo.stage     = VK_SHADER_STAGE_COMPUTE_BIT;
	stageInfo.module    = shader;
	stageInfo.pName     = "main";    

	VkComputePipelineCreateInfo	pipelineInfo = {};
	pipelineInfo.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
	pipelineInfo.stage = stageInfo;
	pipelineInfo.layout = pipelineLayout;

	VkPipeline pipeline = VK_NULL_HANDLE;

	if (
        vkCreateComputePipelines(
            device,
            VK_NULL_HANDLE,
            1,
            &pipelineInfo,
            nullptr,
            &pipeline
    ) != VK_SUCCESS ) {
		throw std::runtime_error("Pipeline: failed to create compute pipeline!");
    }

    this->instance = vkInst;
    this->device = device;
}

void VulkanRender::setScene(std::shared_ptr<Scene> scene) {
    std::print("VulkanRender setScene\n");
}

void VulkanRender::render() {
    std::print("VulkanRender render\n");
}

}