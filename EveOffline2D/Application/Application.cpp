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
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Game template");
    InitAudioDevice();

    // SetTargetFPS(60);
    // ecsWorld.import<flecs::units>();
    // ecsWorld.import<flecs::stats>();
    // ecsWorld.set<flecs::Rest>({});

    RegisterComponents(world);
    world.set(AssetManager{});
    world.set(AudioManager{});
    world.set(Camera2D{{toFloat(WINDOW_WIDTH) * 0.5f, toFloat(WINDOW_HEIGHT) * 0.5f}, {300, 300}, 0, 1});
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
