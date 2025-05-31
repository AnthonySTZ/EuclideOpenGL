cmake_minimum_required(VERSION 3.10)
project(Euclide)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE HEADERS src/*.h)

set(IMGUI_SOURCES
    $ENV{IMGUI}/imgui.cpp
    $ENV{IMGUI}/imgui_demo.cpp
    $ENV{IMGUI}/imgui_draw.cpp
    $ENV{IMGUI}/imgui_widgets.cpp
    $ENV{IMGUI}/imgui_tables.cpp
    $ENV{IMGUI}/backends/imgui_impl_glfw.cpp
    $ENV{IMGUI}/backends/imgui_impl_opengl3.cpp
)

set(GLAD_SOURCES
    $ENV{GLAD}/src/glad.c
)

add_executable(Euclide ${SRC_FILES} ${HEADERS} ${IMGUI_SOURCES} ${GLAD_SOURCES})

add_custom_command(
    TARGET Euclide PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/Engine/Core/Rendering/shaders ${CMAKE_BINARY_DIR}/src/Engine/Core/Rendering/shaders
    COMMENT "Copying shaders..."
)

add_custom_command(
    TARGET Euclide PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/assets
    COMMENT "Copying assets..."
)

# IMPORT GLFW
if(DEFINED ENV{GLFW})
    target_include_directories(Euclide PRIVATE $ENV{GLFW}/include)
    target_link_directories(Euclide PRIVATE $ENV{GLFW}/lib-vc2022)
    target_link_libraries(Euclide PRIVATE glfw3.lib)
    message(STATUS "Using GLFW include directory: $ENV{GLFW}/include")
else()
    message(WARNING "GLFW environment variable not set. Include directories might be missing.")
endif()

# IMPORT GLM
if(DEFINED ENV{GLM})
    target_include_directories(Euclide PRIVATE $ENV{GLM})
    message(STATUS "Using GLM include directory: $ENV{GLM}")
else()
    message(WARNING "GLM environment variable not set. Include directories might be missing.")
endif()

# IMPORT GLAD
if(DEFINED ENV{GLAD})
    target_include_directories(Euclide PRIVATE $ENV{GLAD}/include)
    message(STATUS "Using GLAD include directory: $ENV{GLAD}/include")
else()
    message(WARNING "GLAD environment variable not set. Include directories might be missing.")
endif()

# IMPORT IMGUI
if(DEFINED ENV{IMGUI})
    target_include_directories(Euclide PRIVATE $ENV{IMGUI} $ENV{IMGUI}/backends)
    message(STATUS "Using IMGUI include directory: $ENV{IMGUI}")
else()
    message(WARNING "IMGUI environment variable not set. Include directories might be missing.")
endif()