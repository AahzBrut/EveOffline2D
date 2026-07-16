#include "OrbitSystem.h"

#include <algorithm>
#include <raylib.h>
#include <raymath.h>

#include "Components/Commands/MovementState.h"
#include "Components/Commands/OrbitState.h"
#include "Components/Impl/MaxRotationSpeed.h"
#include "Components/Impl/MaxSpeed.h"
#include "Components/Impl/Position.h"
#include "Components/Impl/Rotation.h"
#include "Components/Impl/TargetRotation.h"
#include "Components/Impl/ThrustLevel.h"


inline constexpr float OrbitDistanceThreshold = 50.0f;

void OrbitSystem(const flecs::world& world) {
    world
        .system<flecs::pair<MovementState, OrbitState>, TargetRotation, ThrustLevel, const Position,
                const Rotation, const MaxRotationSpeed, const MaxSpeed>(__func__)
        .kind(flecs::OnUpdate)
        .each([](const flecs::iter&, const size_t,
                 const OrbitState& command,
                 TargetRotation& targetRotation,
                 ThrustLevel& thrustLevel,
                 const Position& position,
                 const Rotation& rotation,
                 const MaxRotationSpeed& maxRotationSpeed,
                 const MaxSpeed& maxSpeed) {
            if (command.entity.is_valid()) {
                const auto targetPosition = command.entity.get<Position>();
                const auto vectorToTarget = targetPosition.Vector2() - position.Vector2();
                const float distanceToTarget = Vector2Length(vectorToTarget);
                const auto normVectorToTarget = Vector2Normalize(vectorToTarget);
                const auto shipDirection = rotation.ForwardVector();

                // Two perpendicular points on orbit (left=CCW tangent, right=CW tangent)
                const Vector2 leftOrbitPoint = Vector2 {-normVectorToTarget.y, normVectorToTarget.x} * command.distance;
                const Vector2 rightOrbitPoint = Vector2 {normVectorToTarget.y, -normVectorToTarget.x} * command.
                    distance;

                // Choose orbit point: if target is on left side -> fly left (CCW), else fly right (CW)
                const float crossProduct = shipDirection.x * normVectorToTarget.y -
                    shipDirection.y * normVectorToTarget.x;
                const Vector2 targetOrbitPoint = crossProduct > 0.0f ? rightOrbitPoint : leftOrbitPoint;

                float orbitAngle;
                if (distanceToTarget < command.distance + OrbitDistanceThreshold) {
                    // On orbit: fly tangent
                    orbitAngle = crossProduct > 0.0f
                                     ? atan2f(-vectorToTarget.x, vectorToTarget.y) // CCW tangent
                                     : atan2f(vectorToTarget.x, -vectorToTarget.y); // CW tangent
                    thrustLevel.value = command.distance * maxRotationSpeed.effectiveValue / maxSpeed.effectiveValue;
                } else {
                    // Not on orbit yet: fly to chosen orbit point
                    const auto toTargetPoint = Vector2Normalize(vectorToTarget + targetOrbitPoint);
                    orbitAngle = atan2f(toTargetPoint.y, toTargetPoint.x);
                    thrustLevel.value = std::clamp(distanceToTarget * maxRotationSpeed.effectiveValue / maxSpeed.effectiveValue, 0.0f, 1.0f);
                }

                targetRotation.value = orbitAngle;
            }
        });
}
