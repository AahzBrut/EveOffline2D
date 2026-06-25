#include "MovementSystem.h"

#include <cmath>
#include <raylib.h>
#include <raymath.h>

#include "Components/Impl/MaxSpeed.h"
#include "Components/Impl/Position.h"
#include "Components/Impl/Rotation.h"
#include "Components/Impl/TargetPosition.h"
#include "Components/Impl/Velocity.h"
#include "defs.h"


static constexpr float ARRIVAL_THRESHOLD = 5.0f;
static constexpr float ROTATION_SPEED = 90.0f;

void MovementSystem(const flecs::world &world) {
    world
            .system<Position, VelocityVector, MaxSpeed, Rotation, TargetPosition>("MovementSystem.Move")
            .kind(flecs::OnUpdate)
            .each([](const flecs::iter &it, size_t index,  Position &position, VelocityVector &velocity, const MaxSpeed &maxSpeed, Rotation &rotation, const TargetPosition &target) {
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

                const Vector2 currentPos = {toFloat(position.x), toFloat(position.y)};
                const float distance = Vector2Length(dir);

                if (distance < ARRIVAL_THRESHOLD) {
                    velocity.velocity = {0, 0};
                    position.x = target.value.x;
                    position.y = target.value.y;
                    it.entity(index).remove<TargetPosition>();
                    return;
                }

                const float angleRad = rotation.angle * DEG2RAD;
                const Vector2 forward = {cosf(angleRad), sinf(angleRad)};

                velocity.velocity = {forward.x * maxSpeed.value, forward.y * maxSpeed.value};

                position.x += velocity.velocity.x * dt;
                position.y += velocity.velocity.y * dt;
            });
}
