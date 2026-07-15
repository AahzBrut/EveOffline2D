#include "ApproachSystem.h"

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
                const auto directionToTarget = Vector2Normalize(vectorToTarget);
                const auto distanceToTargetSqr = Vector2LengthSqr(vectorToTarget);
                const auto distanceToGo = distanceToTargetSqr - command.distance * command.distance;


                targetRotation.value = atan2f(vectorToTarget.y, vectorToTarget.x);
            } else {
                it.entity(index).remove<ApproachCommand>();
            }
        });
}
