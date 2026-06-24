#include "InputSystem.h"

#include <raylib.h>

#include "Components/Impl/TargetPosition.h"
#include "defs.h"


void InputSystem(const flecs::world &world) {
    world
            .system("InputSystem")
            .kind(flecs::OnUpdate)
            .run([](flecs::iter &it) {
                if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && IsKeyDown(KEY_LEFT_SHIFT)) {
                    const Camera2D camera = it.world().get<Camera2D>();
                    const Vector2 mousePos = GetScreenToWorld2D(GetMousePosition(), camera);
                    it.world()
                            .entity("Player")
                            .set<TargetPosition>({mousePos});
                }
            });
}
