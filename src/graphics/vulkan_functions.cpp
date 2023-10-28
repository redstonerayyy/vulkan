#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstring>

// log debug messages
static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData) {

    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

    return VK_FALSE;
}

std::vector<VkLayerProperties> enumerateVkLayers(){
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    return availableLayers;
}

std::vector<VkExtensionProperties> enumerateVkExtensions(){
    uint32_t extensioncount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensioncount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensioncount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensioncount, availableExtensions.data());

    return availableExtensions;
}

bool checkLayer(const char* layerName, std::vector<VkLayerProperties> &availableLayers){
    for (const auto &layerProperties : availableLayers) {
        if (strcmp(layerName, layerProperties.layerName) == 0) {
            return true;
        }
    }

    return false;
}


VkInstance vulkan_init(){
    std::vector<VkLayerProperties> availableLayers = enumerateVkLayers();
    std::vector<VkExtensionProperties> availableExtensions = enumerateVkExtensions();

    const std::vector<const char*> requiredValidationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };


    for (const char* layerName : requiredValidationLayers) {
        if (!checkLayer(layerName, availableLayers)) {
            std::cout << layerName << " layer not found\n";
        }
    }

    std::cout << "available extensions:\n";

    for (const auto& extension : availableExtensions) {
        std::cout << '\t' << extension.extensionName << '\n';
    }

    VkInstance instance;

    VkApplicationInfo appinfo{};
    appinfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appinfo.pApplicationName = "Minecraft";
    appinfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appinfo.pEngineName = "Custom";
    appinfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appinfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createinfo{};
    createinfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createinfo.pApplicationInfo = &appinfo;

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

    const bool enableValidationLayers = true;
    if (enableValidationLayers) {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    createinfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createinfo.ppEnabledExtensionNames = extensions.data();
    createinfo.enabledLayerCount = 0;

    if (enableValidationLayers) {
        createinfo.enabledLayerCount = static_cast<uint32_t>(requiredValidationLayers.size());
        createinfo.ppEnabledLayerNames = requiredValidationLayers.data();
    } else {
        createinfo.enabledLayerCount = 0;
    }

    if (vkCreateInstance(&createinfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }

    return instance;
}

void vulkan_terminate(VkInstance instance){
    vkDestroyInstance(instance, nullptr);
}
