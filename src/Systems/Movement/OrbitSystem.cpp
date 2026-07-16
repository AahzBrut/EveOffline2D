#include "OrbitSystem.h"

#include <raylib.h>
#include <raymath.h>

#include "Components/Commands/MovementState.h"
#include "Components/Commands/OrbitState.h"
#include "Components/Impl/Position.h"
#include "Components/Impl/Rotation.h"
#include "Components/Impl/TargetRotation.h"
#include "Components/Impl/ThrustLevel.h"


void OrbitSystem(const flecs::world& world) {
    world
        .system<flecs::pair<MovementState, OrbitState>, TargetRotation, ThrustLevel, const Position, const Rotation>(__func__)
        .kind(flecs::OnUpdate)
        .each([](const flecs::iter& it, const size_t index,
                 const OrbitState& command,
                 TargetRotation& targetRotation,
                 ThrustLevel& thrustLevel,
                 const Position& position,
                 const Rotation& rotation) {
            if (command.entity.is_valid()) {
                const auto targetPosition = command.entity.get<Position>();
                const auto vectorToTarget = targetPosition.Vector2() - position.Vector2();
                const float distanceToTarget = Vector2Length(vectorToTarget);
                const auto normVectorToTarget = Vector2Normalize(vectorToTarget);
                const auto shipDirection = rotation.ForwardVector();

                // Two perpendicular points on orbit (left=CCW tangent, right=CW tangent)
                const Vector2 leftOrbitPoint = targetPosition.Vector2() + Vector2{-normVectorToTarget.y, normVectorToTarget.x} * command.distance;
                const Vector2 rightOrbitPoint = targetPosition.Vector2() + Vector2{normVectorToTarget.y, -normVectorToTarget.x} * command.distance;

                // Choose orbit point: if target is on left side -> fly left (CCW), else fly right (CW)
                const float crossProduct = shipDirection.x * vectorToTarget.y - shipDirection.y * vectorToTarget.x;
                const Vector2 targetOrbitPoint = crossProduct > 0.0f ? leftOrbitPoint : rightOrbitPoint;

                float orbitAngle;
                if (distanceToTarget < command.distance) {
                    // On orbit: fly tangent
                    orbitAngle = crossProduct > 0.0f
                                     ? atan2f(-vectorToTarget.x, vectorToTarget.y)  // CCW tangent
                                     : atan2f(vectorToTarget.x, -vectorToTarget.y); // CW tangent
                } else {
                    // Not on orbit yet: fly to chosen orbit point
                    const Vector2 toTargetPoint = targetOrbitPoint - position.Vector2();
                    orbitAngle = atan2f(toTargetPoint.y, toTargetPoint.x);
                }

                targetRotation.value = orbitAngle;
                thrustLevel.value = 1.0f;
            }
        });
}
