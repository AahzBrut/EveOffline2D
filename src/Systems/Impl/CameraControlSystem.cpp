#include "CameraControlSystem.h"

#include <raylib.h>

#include "Components/Impl/Position.h"
#include "defs.h"
#include "Logger.h"


void CameraControlSystem(const flecs::world &world) {
    auto camera = &world.get_mut<Camera2D>();

    world
            .system(__func__)
            .run([camera](flecs::iter &it) {
                const auto wheelDelta = GetMouseWheelMove();
                if (wheelDelta != 0) {
                    const auto zoomDelta = wheelDelta > 0 ? 2.f : 0.5f;
                    camera->zoom *= zoomDelta;
                }

                const auto player = it.world().entity("Player");
                if (player.has<Position>()) {
                    const auto &pos = player.get<Position>();
                    camera->target.x = toFloat(pos.x);
                    camera->target.y = toFloat(pos.y);
                }
            });
}
