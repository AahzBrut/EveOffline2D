#include "InputSystem.h"

#include <raylib.h>

#include "Components/Impl/TargetPosition.h"


void InputSystem(const flecs::world& world) {
    constexpr double doubleClickThreshold = 0.3;
    static double lastClick = 0.0;

    world
        .system(__func__)
        .kind(flecs::OnUpdate)
        .run([](const flecs::iter& it) {
            const auto currentTime = GetTime();
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (currentTime - lastClick <= doubleClickThreshold) {
                    const Camera2D camera = it.world().get<Camera2D>();
                    const Vector2 mousePos = GetScreenToWorld2D(GetMousePosition(), camera);
                    it.world()
                      .entity("Player")
                      .set<TargetPosition>({mousePos});
                }
                lastClick = currentTime;
            }
        });
}
