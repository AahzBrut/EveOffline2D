#include "ThrustSystem.h"

#include "Components/Impl/Acceleration.h"
#include "Components/Impl/MaxSpeed.h"
#include "Components/Impl/Speed.h"
#include "Components/Impl/ThrustLevel.h"


void ThrustSystem(const flecs::world& world) {
    world
        .system<Speed, const MaxSpeed, const ThrustLevel, const Acceleration>(__func__)
        .kind(flecs::OnUpdate)
        .each([](const flecs::iter& it, const size_t _,
                 Speed& speed, const MaxSpeed& maxSpeed, const ThrustLevel& thrustLevel,
                 const Acceleration& acceleration) {
            const auto dt = it.delta_time();

            if (const auto targetSpeed = maxSpeed.effectiveValue * thrustLevel.value; speed.effectiveValue !=
                targetSpeed) {
                const auto deltaSpeed = acceleration.effectiveValue * dt;
                if (const auto speedDiff = targetSpeed - speed.effectiveValue; abs(deltaSpeed) >= abs(speedDiff)) {
                    speed.effectiveValue = targetSpeed;
                } else {
                    speed.effectiveValue += (speedDiff > 0 ? 1.0f : -1.0f) * deltaSpeed;
                }
            }
        });
}
