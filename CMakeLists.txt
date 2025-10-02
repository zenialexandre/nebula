cmake_minimum_required(VERSION 3.26)

project(nebula VERSION 0.1.0)

# This moves the SDL dll to the right place (when BUILD_SHARED_LIBS is ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_CXX_STANDARD 17)

add_library(glad STATIC 
    libs/glad/glad.c
    libs/glad/include/glad/glad.h
    libs/glad/include/KHR/khrplatform.h
)

add_library(glm INTERFACE)
target_link_directories(glm INTERFACE 
    libs/glm/
)

add_library(nebula_common STATIC
    src/modules/common/Module.cpp
    src/modules/common/Module.hpp
    src/modules/common/WrapModule.hpp
    src/modules/common/LuaBidings.hpp
)
target_link_libraries(nebula_common PUBLIC
    lua-5.4.8
)

add_library(nebula_time STATIC
    src/modules/time/DeltaTime.cpp
    src/modules/time/DeltaTime.hpp
    src/modules/time/Instant.hpp
    src/modules/time/Time.cpp
    src/modules/time/Time.hpp
    src/modules/time/WrapTime.cpp
    src/modules/time/WrapTime.hpp
)
target_link_libraries(nebula_time PUBLIC
    nebula_common
)

add_library(nebula_window STATIC
    src/modules/window/Window.cpp
    src/modules/window/Window.h
)
target_link_libraries(nebula_window PUBLIC 
    SDL3::SDL3
    nebula_common
)

add_library(nebula_ecs STATIC
    src/modules/ecs/Hash.hpp
    src/modules/ecs/Definitions.hpp
    src/modules/ecs/IdStorage.hpp
    src/modules/ecs/Table.hpp
    src/modules/ecs/Type.hpp
    src/modules/ecs/World.hpp
    src/modules/ecs/WrapWorld.hpp
    src/modules/ecs/WrapWorld.cpp
    src/modules/ecs/RenderComponents.hpp
)
target_link_libraries(nebula_ecs PUBLIC
    nebula_common
)

add_library(nebula_graphics STATIC
    src/modules/graphics/Graphics.cpp
    src/modules/graphics/Graphics.h
    src/modules/graphics/Camera.h
    src/modules/graphics/Camera.cpp
    src/modules/graphics/Renderer.h
    src/modules/graphics/Renderer.cpp
    src/modules/graphics/Texture.cpp
    src/modules/graphics/Texture.h
    src/modules/graphics/Shader.cpp
    src/modules/graphics/Shader.h
)
target_link_libraries(nebula_graphics PUBLIC 
    SDL3::SDL3
    lua-5.4.8
    glad
    nebula_ecs
    nebula_common
)

add_library(nebula_data STATIC
    src/modules/data/ImageFile.cpp
    src/modules/data/ImageFile.h
    src/modules/data/TextFile.cpp
    src/modules/data/TextFile.h
)
target_link_libraries(nebula_data PUBLIC
    nebula_common
)

add_library(nebula_scripts STATIC
    src/modules/scripts/NebulaSetup.cpp
    src/modules/scripts/NebulaSetup.hpp
)
target_link_libraries(nebula_scripts PUBLIC
    lua-5.4.8
    nebula_time
    nebula_window
    nebula_ecs
    nebula_graphics
)

set(NEBULA_MODULES
    nebula_time
    nebula_window
    nebula_graphics
    nebula_data
    nebula_ecs
    nebula_common
    nebula_scripts
)

set(NEBULA_LIBRARIES
    SDL3::SDL3
    lua-5.4.8
    glad
    glm
)

include_directories(
    BEFORE
    src
    libs
    libs/glad/include
    src/modules
)

# Uncomment to use static lib
# option(BUILD_SHARED_LIBS OFF)
add_subdirectory(libs/SDL3)
add_subdirectory(libs/lua-5.4.8)

add_executable(nebula)
target_sources(nebula PRIVATE src/nebula.cpp)
target_link_libraries(nebula ${NEBULA_MODULES} ${NEBULA_LIBRARIES})
#target_include_directories(nebula PRIVATE libs/glad/include/)