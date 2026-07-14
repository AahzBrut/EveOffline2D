#include "BeginCameraSystem.h"

#include <raylib.h>

#include "Logger.h"


void BeginCameraSystem(const flecs::world& world) {
    auto camera = &world.get_mut<Camera2D>();

    world
        .system(__func__)
        .kind(flecs::OnStore)
        .run([camera](const flecs::iter& _) {
            BeginMode2D(*camera);
        });
}
