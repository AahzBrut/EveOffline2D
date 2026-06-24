#include "RenderFPSSystem.h"

#include <format>
#include <raylib.h>

void RenderFPSSystem(const flecs::world &world) {
    world
            .system(__func__)
            .kind(flecs::OnStore)
            .run([](flecs::iter &) {
                const auto fpsString = std::format("{}", GetFPS());
                DrawText(fpsString.c_str(), 5, 5, 32, WHITE);
            });
}
