#include "CameraControlSystem.h"

#include <raylib.h>

#include "defs.h"
#include "Logger.h"
#include "Components/Impl/Position.h"


void CameraControlSystem(const flecs::world &world) {
    auto camera = &world.get_mut<Camera2D>();

    world
            .system(__func__)
            .run([camera](const flecs::iter &it) {
                if (const auto wheelDelta = GetMouseWheelMove(); wheelDelta != 0) {
                    const auto zoomDelta = wheelDelta > 0 ? 2.f : 0.5f;
                    camera->zoom *= zoomDelta;
                }

                if (const auto player = it.world().entity("Player"); player.has<Position>()) {
                    const auto & [x, y] = player.get<Position>();
                    //camera->target.x = toFloat(x);
                    //camera->target.y = toFloat(y);
                }
            });
}
