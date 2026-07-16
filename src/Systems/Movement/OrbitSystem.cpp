#include "OrbitSystem.h"

#include <raymath.h>

#include "Logger.h"
#include "Components/Commands/ApproachState.h"
#include "Components/Commands/MovementState.h"
#include "Components/Commands/OrbitState.h"
#include "Components/Impl/Acceleration.h"
#include "Components/Impl/MaxRotationSpeed.h"
#include "Components/Impl/MaxSpeed.h"
#include "Components/Impl/Position.h"
#include "Components/Impl/Rotation.h"
#include "Components/Impl/Speed.h"
#include "Components/Impl/TargetRotation.h"
#include "Components/Impl/ThrustLevel.h"


void OrbitSystem(const flecs::world& world) {
    world
        .system<flecs::pair<MovementState, OrbitState>, TargetRotation, ThrustLevel, const MaxSpeed, const
                MaxRotationSpeed, const Position, const Speed,
                const Acceleration, const Rotation>(__func__)
        .kind(flecs::OnUpdate)
        .each([](const flecs::iter& it, const size_t index,
                 const OrbitState& command,
                 TargetRotation& targetRotation,
                 ThrustLevel& thrustLevel,
                 const MaxSpeed& maxSpeed,
                 const MaxRotationSpeed& maxRotationSpeed,
                 const Position& position,
                 const Speed& speed,
                 const Acceleration& acceleration,
                 const Rotation& rotation) {
            if (command.entity.is_valid()) {
                const auto targetPosition = command.entity.get<Position>();
                const auto vectorToTarget = targetPosition.Vector2() - position.Vector2();
                const auto normVectorToTarget = Vector2Normalize(vectorToTarget);
                const auto rightVector = Vector2 {normVectorToTarget.y, -normVectorToTarget.x} * command.distance;
                const auto leftVector = Vector2 {-normVectorToTarget.y, normVectorToTarget.x} * command.distance;
                const auto shipDirection = rotation.ForwardVector();

                // Positive - target on the left, negative - on the right
                const auto targetOrientation = shipDirection.x * targetPosition.y - shipDirection.y * targetPosition.x;
                const auto targetPointPosition = targetOrientation < 0.0
                                                     ? targetPosition.Vector2() + rightVector
                                                     : targetPosition.Vector2() + leftVector;
                const auto targetPointVector = Vector2Normalize(targetPointPosition - position.Vector2());
                targetRotation.value = atan2f(targetPointVector.y, targetPointVector.x);
                thrustLevel.value = 1.0f;
            }
        });
}
