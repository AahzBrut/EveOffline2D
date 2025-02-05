#include "CameraControlSystem.h"

#include <raylib.h>

#include "Logger.h"


void CameraControlSystem(const flecs::world &world) {
    auto camera = world.get_mut<Camera2D>();

    world
            .system(__func__)
            .run([camera](flecs::iter &) {
                const auto wheelDelta = GetMouseWheelMove();
                if (wheelDelta == 0) return;
                const auto zoomDelta = wheelDelta > 0 ? 2.f : 0.5f;
                camera->zoom *= zoomDelta;
            });
}
