#include "ApproachSystem.h"

#include <algorithm>
#include <cmath>
#include <raymath.h>

#include "Components/Commands/ApproachCommand.h"
#include "Components/Impl/Acceleration.h"
#include "Components/Impl/Position.h"
#include "Components/Impl/Speed.h"
#include "Components/Impl/TargetRotation.h"
#include "Components/Impl/ThrustLevel.h"


void ApproachSystem(const flecs::world& world) {
    world
        .system<const ApproachCommand, TargetRotation, ThrustLevel, const Position, const Speed, const Acceleration>(__func__)
        .kind(flecs::OnUpdate)
        .each([](const flecs::iter& it, const size_t index,
                 const ApproachCommand& command,
                 TargetRotation& targetRotation,
                 ThrustLevel& thrustLevel,
                 const Position& position,
                 const Speed& speed,
                 const Acceleration& acceleration) {
            if (command.entity.is_valid()) {
                const auto targetPosition = command.entity.get<Position>();
                const auto vectorToTarget = targetPosition.Vector2() - position.Vector2();
                const auto distanceToTarget = Vector2Length(vectorToTarget);

                const float holdDistance = command.distance;
                const float currentSpeed = speed.effectiveValue;
                const auto brakeDistance = currentSpeed * currentSpeed / (2.0f * acceleration.effectiveValue);

                if (distanceToTarget < holdDistance) {
                    targetRotation.value = atan2f(-vectorToTarget.y, -vectorToTarget.x);
                    const float maxRetreatDistance = holdDistance - brakeDistance;

                    if (distanceToTarget < maxRetreatDistance) {
                        thrustLevel.value = (distanceToTarget - holdDistance) / brakeDistance;
                        thrustLevel.value = std::clamp(thrustLevel.value, 0.0f, 1.0f);
                    } else {
                        thrustLevel.value = 0.0f;
                    }
                } else {
                    targetRotation.value = atan2f(vectorToTarget.y, vectorToTarget.x);

                    const float minApproachDistance = holdDistance + brakeDistance;

                    if (distanceToTarget > holdDistance + brakeDistance) {
                        thrustLevel.value = 1.0f;
                    } else if (distanceToTarget > minApproachDistance) {
                        thrustLevel.value = (distanceToTarget - minApproachDistance) / brakeDistance;
                        thrustLevel.value = std::clamp(thrustLevel.value, 0.0f, 1.0f);
                    } else {
                        thrustLevel.value = 0.0f;
                    }
                }
            } else {
                thrustLevel.value = 0.0f;
                it.entity(index).remove<ApproachCommand>();
            }
        });
}
