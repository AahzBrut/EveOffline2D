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

void MovementSystem(const flecs::world &world) {
    world
            .system<Position, VelocityVector, MaxSpeed, Rotation, TargetPosition>("MovementSystem")
            .kind(flecs::OnUpdate)
            .each([&world](flecs::entity entity, Position &position, VelocityVector &velocity, const MaxSpeed &maxSpeed, const Rotation &rotation, const TargetPosition &target) {
                const Vector2 currentPos = {toFloat(position.x), toFloat(position.y)};
                const Vector2 dir = Vector2Subtract(target.value, currentPos);
                const float distance = Vector2Length(dir);

                if (distance < ARRIVAL_THRESHOLD) {
                    velocity.velocity = {0, 0};
                    position.x = target.value.x;
                    position.y = target.value.y;
                    entity.remove<TargetPosition>();
                    return;
                }

                const float angleRad = rotation.angle * DEG2RAD;
                const Vector2 forward = {cosf(angleRad), sinf(angleRad)};

                velocity.velocity = {forward.x * maxSpeed.value, forward.y * maxSpeed.value};

                position.x += velocity.velocity.x * world.delta_time();
                position.y += velocity.velocity.y * world.delta_time();
            });
}
