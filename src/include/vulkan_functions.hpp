#pragma once

#ifndef VULKAN_HPP
#define VULKAN_HPP

#include <vulkan.h>
#include <vector>

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback();
std::vector<VkLayerProperties> enumerateVkLayers();
std::vector<VkExtensionProperties> enumerateVkExtensions();
bool checkLayer(const char* layerName, std::vector<VkLayerProperties> &availableLayers);
VkInstance vulkan_init();

#endif
