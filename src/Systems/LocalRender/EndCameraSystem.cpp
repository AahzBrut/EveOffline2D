#include "../Impl/EndCameraSystem.h"

#include "Logger.h"
#include "raylib.h"


void EndCameraSystem(const flecs::world& world) {
    world
        .system(__func__)
        .kind(flecs::OnStore)
        .run([](const flecs::iter& _) {
            EndMode2D();
        });
}
