cmake_minimum_required(VERSION 3.26)

# Build in release mode: 
# cmake -B release -DCMAKE_BUILD_TYPE=Release
# cmake --build build --config Release

project(nebula VERSION 0.1.0)

# This moves the SDL dll to the right place (when BUILD_SHARED_LIBS is ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_CXX_STANDARD 17)

# Uncomment to use static lib
option(BUILD_SHARED_LIBS OFF)

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
    src/modules/common/WrapType.hpp
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

add_library(nebula_ecs STATIC
    src/modules/ecs/Hash.hpp
    src/modules/ecs/Definitions.hpp
    src/modules/ecs/IdStorage.hpp
    src/modules/ecs/Table.hpp
    src/modules/ecs/Type.hpp
    src/modules/ecs/World.hpp
    src/modules/ecs/WrapWorld.hpp
    src/modules/ecs/WrapWorld.cpp
    src/modules/ecs/WrapPosition.hpp
    src/modules/ecs/WrapPosition.cpp
    src/modules/ecs/WrapScale.hpp
    src/modules/ecs/WrapScale.cpp
    src/modules/ecs/WrapQuad.hpp
    src/modules/ecs/WrapQuad.cpp
    src/modules/ecs/WrapSprite.hpp
    src/modules/ecs/WrapSprite.cpp
    src/modules/ecs/WrapText.hpp
    src/modules/ecs/WrapText.cpp
    src/modules/ecs/WrapColor.hpp
    src/modules/ecs/WrapColor.cpp
    src/modules/ecs/WrapRotation.hpp
    src/modules/ecs/WrapRotation.cpp
    src/modules/ecs/WrapCollisionBox.hpp
    src/modules/ecs/WrapCollisionBox.cpp
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
    src/modules/graphics/Font.cpp
    src/modules/graphics/Font.hpp
    src/modules/graphics/WrapGraphics.cpp
    src/modules/graphics/WrapGraphics.hpp
    src/modules/graphics/WrapTexture.cpp
    src/modules/graphics/WrapTexture.hpp
    src/modules/graphics/WrapFont.cpp
    src/modules/graphics/WrapFont.hpp
)
target_link_libraries(nebula_graphics PUBLIC 
    SDL3::SDL3
    lua-5.4.8
    freetype
    glad
    nebula_ecs
    nebula_common
)
target_include_directories(nebula_graphics PUBLIC
    resources/shaders/fragShader.glsl
    resources/shaders/vertexShader.glsl
)

add_library(nebula_window STATIC
    src/modules/window/Window.cpp
    src/modules/window/Window.h
    src/modules/window/WrapWindow.cpp
    src/modules/window/WrapWindow.hpp
)
target_link_libraries(nebula_window PUBLIC 
    SDL3::SDL3
    nebula_common
    nebula_graphics
)

add_library(nebula_data STATIC
    src/modules/data/ImageFile.cpp
    src/modules/data/ImageFile.h
    src/modules/data/TextFile.cpp
    src/modules/data/TextFile.h
    src/modules/data/File.hpp
)
target_link_libraries(nebula_data PUBLIC
    nebula_common
)

add_library(nebula_keyboard STATIC
    src/modules/keyboard/Keyboard.cpp
    src/modules/keyboard/Keyboard.hpp
    src/modules/keyboard/WrapKeyboard.cpp
    src/modules/keyboard/WrapKeyboard.hpp
)
target_link_libraries(nebula_keyboard PUBLIC
    SDL3::SDL3
    nebula_common
)

add_library(nebula_mouse STATIC
    src/modules/mouse/Mouse.cpp
    src/modules/mouse/Mouse.hpp
    src/modules/mouse/WrapMouse.cpp
    src/modules/mouse/WrapMouse.hpp
)
target_link_libraries(nebula_mouse PUBLIC
    SDL3::SDL3
    nebula_common
    nebula_window
)

add_library(nebula_physics STATIC
    src/modules/physics/Physics.hpp
    src/modules/physics/Physics.cpp
    src/modules/physics/WrapPhysics.hpp
    src/modules/physics/WrapPhysics.cpp
)
target_link_libraries(nebula_physics PUBLIC 
    nebula_ecs
    nebula_common
)

add_library(nebula_event STATIC
    src/modules/event/Event.hpp
    src/modules/event/Event.cpp
    src/modules/event/WrapEvent.hpp
    src/modules/event/WrapEvent.cpp
)
target_link_libraries(nebula_event PUBLIC
    SDL3::SDL3
    nebula_common
    nebula_window
    nebula_graphics
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
    nebula_event
    nebula_keyboard
    nebula_mouse
    nebula_physics
)
target_include_directories(nebula_scripts PUBLIC
    src/modules/scripts/boot.lua
    src/modules/scripts/baseScreen.lua
)

set(NEBULA_MODULES
    nebula_time
    nebula_window
    nebula_graphics
    nebula_data
    nebula_ecs
    nebula_common
    nebula_event
    nebula_scripts
    nebula_keyboard
)

set(NEBULA_LIBRARIES
    SDL3::SDL3
    freetype
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

add_subdirectory(libs/SDL3)
add_subdirectory(libs/lua-5.4.8)
add_subdirectory(libs/freetype-2.14.1)

#add_executable(nebula_console)
#target_sources(nebula_console PRIVATE src/nebula.cpp)
#target_link_libraries(nebula_console ${NEBULA_MODULES} ${NEBULA_LIBRARIES})

#add_executable(nebula WIN32)
add_executable(nebula)
target_sources(nebula PRIVATE src/nebula.cpp)
target_link_libraries(nebula ${NEBULA_MODULES} ${NEBULA_LIBRARIES})
#target_include_directories(nebula PRIVATE libs/glad/include/)