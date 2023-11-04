# ------------ project stuff ------------ #
CMAKE_MINIMUM_REQUIRED(VERSION 3.24)
project(vulk)

# ------------ build options ------------ #
set(C_FLAGS "-O2 -Wall -std=c2x")
set(CXX_FLAGS "-O2 -Wall -std=c++20")

# ------------ dependencies ------------ #
add_subdirectory(thirdparty/glfw) # glfw for the window

find_package(Vulkan REQUIRED) # vulkan for 3D

# ------------ main executable ------------ #
FILE(GLOB SOURCE_FILES src/*.cpp src/graphics/*.cpp)

add_executable(vulk ${SOURCE_FILES})

target_include_directories(vulk PRIVATE
	src/include
	thirdparty/glfw/include
    thirdparty/glm
    ${Vulkan_INCLUDE_DIRS}
)

target_link_libraries(vulk PRIVATE
	glfw
	${Vulkan_LIBRARIES}
)
