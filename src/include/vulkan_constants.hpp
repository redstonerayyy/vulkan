#pragma once

#ifndef VULKAN_CONSTANTS_HPP
#define VULKAN_CONSTANTS_HPP

#include <vector>
#include <vulkan/vulkan.h>

const std::vector<const char*> requiredValidationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

const bool enableValidationLayers = true;

#endif
