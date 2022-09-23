CMAKE_MINIMUM_REQUIRED(VERSION 3.24)

project(vulk)

set(CXX_FLAGS "-O2 -Wall -std=c++17")

# VULKAN
FILE(GLOB SOURCE_FILES src/**.cpp)

add_executable(vulk ${SOURCE_FILES})

target_include_directories(
	vulk PRIVATE
	src/include
)

target_link_libraries(
	vulk PRIVATE
	glfw
	vulkan
	dl
	pthread
	Xi
	Xrandr
	X11
	Xxf86vm
)