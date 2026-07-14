#include "BeginImGuiSystem.h"

#include <rlImGui.h>


void BeginImGuiSystem(const flecs::world& world) {
    world
        .system(__func__)
        .kind(flecs::OnStore)
        .run([](const flecs::iter& _) {
            rlImGuiBegin();
        });
}
