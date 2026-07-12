#include "Application.h"
#include <raylib.h>

#include "defs.h"
#include "AssetManager/Assets.h"
#include "Components/Components.h"
#include "Spawners/SpawnPlayer.h"
#include "Spawners/SpawnShip.h"
#include "Systems/Systems.h"


// ReSharper disable once CppMemberFunctionMayBeStatic
void Application::Initialize() const { // NOLINT(*-convert-member-functions-to-static)
    //SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Eve offline 2D");
    InitAudioDevice();

    // SetTargetFPS(60);
    // ecsWorld.import<flecs::units>();
    // ecsWorld.import<flecs::stats>();
    // ecsWorld.set<flecs::Rest>({});

    RegisterComponents(world);
    world.emplace<AssetManager>();
    world.emplace<AudioManager>();
    world.emplace<Camera2D>(Vector2{toFloat(WINDOW_WIDTH) * 0.5f, toFloat(WINDOW_HEIGHT) * 0.5f}, Vector2{300, 300}, 0.f, 1.f);
    RegisterSystems(world);

    LoadAssets(world);

    SpawnPlayer(world);
    SpawnShip(world);
}

void Application::Run() {
    Initialize();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        world.progress(GetFrameTime());

        EndDrawing();
    }
    DeInitialize();
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void Application::DeInitialize() { // NOLINT(*-convert-member-functions-to-static)
    CloseAudioDevice();
    CloseWindow();
}
