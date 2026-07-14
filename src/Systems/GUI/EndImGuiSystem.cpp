#include "EndImGuiSystem.h"

#include <rlImGui.h>


void EndImGuiSystem(const flecs::world& world) {
    world
        .system(__func__)
        .kind(flecs::OnStore)
        .run([](const flecs::iter& _) {
            rlImGuiEnd();
        });
}
