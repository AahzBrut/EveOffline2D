#include "RotationSystem.h"

#include <cmath>
#include <raylib.h>
#include <raymath.h>

#include "Components/Impl/MaxSpeed.h"
#include "Components/Impl/Position.h"
#include "Components/Impl/Rotation.h"
#include "Components/Impl/TargetPosition.h"
#include "Components/Impl/Velocity.h"
#include "defs.h"


static constexpr float ROTATION_SPEED = 90.0f;

void RotationSystem(const flecs::world &world) {
    world
            .system<Position, Rotation, TargetPosition>("RotationSystem")
            .kind(flecs::OnUpdate)
            .each([](flecs::iter &it, size_t index, const Position &position, Rotation &rotation, const TargetPosition &target) {
                const float dt = it.delta_time();

                const Vector2 dir = Vector2Subtract(target.value, {toFloat(position.x), toFloat(position.y)});
                const float targetAngle = RAD2DEG * atan2f(dir.y, dir.x);

                float angleDiff = targetAngle - rotation.angle;
                while (angleDiff > 180) angleDiff -= 360;
                while (angleDiff < -180) angleDiff += 360;

                if (std::abs(angleDiff) < ROTATION_SPEED * dt) {
                    rotation.angle = targetAngle;
                } else {
                    rotation.angle += ROTATION_SPEED * dt * (angleDiff > 0 ? 1.0f : -1.0f);
                }
            });
}
