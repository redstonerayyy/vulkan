CMAKE_MINIMUM_REQUIRED(VERSION 3.24)

project(vulkan)

set(CXX_FLAGS "-O2 -Wall -stdc++=17")

# VULKAN
FILE(GLOB SOURCE_FILES src/**.cpp)

add_executable(vulkan ${SOURCE_FILES})

target_include_directories(
	vulkan PRIVATE
	src/include
)


