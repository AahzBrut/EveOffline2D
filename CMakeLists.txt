cmake_minimum_required(VERSION 3.30)
project(EveOffline2D)

set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS OFF)
add_compile_definitions(FLECS_CPP_NO_AUTO_REGISTRATION)

include(FetchContent)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
)

FetchContent_Declare(
        flecs
        GIT_REPOSITORY https://github.com/SanderMertens/flecs.git
        GIT_TAG v4.0.4
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(raylib flecs)

add_executable(${CMAKE_PROJECT_NAME}
        EveOffline2D/main.cpp
        EveOffline2D/Application/Application.cpp
        EveOffline2D/Application/Application.h
        EveOffline2D/defs.h
        EveOffline2D/Logger.h
        EveOffline2D/AssetManager/AssetManager.cpp
        EveOffline2D/AssetManager/AssetManager.h
        EveOffline2D/TypeDefs.h
        EveOffline2D/Utils/Random.h
        EveOffline2D/Systems/Systems.h
        EveOffline2D/Components/Components.h
        EveOffline2D/AudioManager/AudioManager.cpp
        EveOffline2D/AudioManager/AudioManager.h
        EveOffline2D/Systems/Impl/RenderFPSSystem.cpp
        EveOffline2D/Systems/Impl/RenderFPSSystem.h
        EveOffline2D/Systems/Impl/RenderBackgroundSystem.cpp
        EveOffline2D/Systems/Impl/RenderBackgroundSystem.h
        EveOffline2D/AssetManager/Assets.h
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE raylib flecs_static)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_PROJECT_NAME})

add_custom_target(COPY_ASSETS
        COMMAND
        ${CMAKE_COMMAND} -E copy_directory_if_different
        "${CMAKE_CURRENT_LIST_DIR}/assets" "${CMAKE_CURRENT_BINARY_DIR}/assets"
)
add_dependencies(${CMAKE_PROJECT_NAME} COPY_ASSETS)
