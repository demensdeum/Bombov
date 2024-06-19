#include "VulkanRender.h"
#include <print>

namespace DemensDeum::Bombov {

void VulkanRender::setScene(std::shared_ptr<Scene> scene) {
    std::print("VulkanRender setScene\n");
}

void VulkanRender::render() {
    std::print("VulkanRender render\n");
}

}