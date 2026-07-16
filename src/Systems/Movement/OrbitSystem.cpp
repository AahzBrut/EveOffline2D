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

                // Two perpendicular points on orbit (left=CCW tangent, right=CW tangent)
                const Vector2 leftOrbitPoint = targetPosition.Vector2() + Vector2{-normVectorToTarget.y, normVectorToTarget.x} * command.distance;
                const Vector2 rightOrbitPoint = targetPosition.Vector2() + Vector2{normVectorToTarget.y, -normVectorToTarget.x} * command.distance;

                // Choose orbit point by minimal rotation angle
                const float angleToLeft = atan2f(leftOrbitPoint.y - position.Vector2().y, leftOrbitPoint.x - position.Vector2().x);
                const float angleToRight = atan2f(rightOrbitPoint.y - position.Vector2().y, rightOrbitPoint.x - position.Vector2().x);

                const float currentAngle = rotation.value;
                float angleDiffLeft = angleToLeft - currentAngle;
                angleDiffLeft = atan2f(sinf(angleDiffLeft), cosf(angleDiffLeft));
                float angleDiffRight = angleToRight - currentAngle;
                angleDiffRight = atan2f(sinf(angleDiffRight), cosf(angleDiffRight));

                const Vector2 targetOrbitPoint = fabsf(angleDiffLeft) <= fabsf(angleDiffRight) ? leftOrbitPoint : rightOrbitPoint;

                float orbitAngle;
                if (distanceToTarget < command.distance) {
                    // On orbit: fly tangent (CCW = left tangent)
                    orbitAngle = atan2f(-vectorToTarget.x, vectorToTarget.y);
                } else {
                    // Not on orbit yet: fly to orbit point requiring minimal rotation
                    const Vector2 toTargetPoint = targetOrbitPoint - position.Vector2();
                    orbitAngle = atan2f(toTargetPoint.y, toTargetPoint.x);
                }

                targetRotation.value = orbitAngle;
                thrustLevel.value = 1.0f;
            }
        });
}
