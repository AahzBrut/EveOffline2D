#include "SelectObjectSystem.h"

#include "Logger.h"
#include "raylib.h"
#include "Components/Impl/MouseCollider.h"
#include "Components/Impl/Position.h"
#include "Components/Impl/Selected.h"


void SelectObjectSystem(const flecs::world& world) {
    world
        .system<const Position, const MouseCollider>(__func__)
        .kind(flecs::OnUpdate)
        .each([](const flecs::iter& it, const size_t index,
                 const Position& position, const MouseCollider& mouseCollider) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                const Camera2D camera = it.world().get<Camera2D>();
                const auto screenPos = GetWorldToScreen2D(position.Vector2(), camera);
                if (CheckCollisionPointCircle(screenPos, GetMousePosition(), mouseCollider.radius)) {
                    it.world().set<Selected>({it.entity(index)});
                }
            }
        });
}
