#include <iostream>
#include <vulkan/vulkan.h>

#include "vulkan_functions.hpp"

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

int main() {
    VkInstance instance = createVulkanInstance();
    
    

    vkDestroyInstance(instance, nullptr);
}
