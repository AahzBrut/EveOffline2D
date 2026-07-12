#include "RenderFPSSystem.h"

#include <format>
#include <raylib.h>

void RenderFPSSystem(const flecs::world &world) {
    world
            .system(__func__)
            .kind(flecs::OnStore)
            .run([](flecs::iter &) {
                DrawFPS(5,5);
            });
}
