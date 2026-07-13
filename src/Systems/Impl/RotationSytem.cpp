#include "RotationSytem.h"

#include <raylib.h>

#include "Logger.h"
#include "Components/Impl/MaxRotationSpeed.h"
#include "Components/Impl/Rotation.h"
#include "Components/Impl/TargetRotation.h"


void RotationSystem(const flecs::world& world) {
    world
        .system<Rotation, const TargetRotation, const MaxRotationSpeed>(__func__)
        .kind(flecs::OnUpdate)
        .each([](const flecs::iter& it, const size_t _,
                 Rotation& rotation, const TargetRotation& targetRotation, const MaxRotationSpeed& maxRotationSpeed) {
            const float dt = it.delta_time();
            float angleDiff = targetRotation.value - rotation.value;
            while (angleDiff > PI) angleDiff -= 2 * PI;
            while (angleDiff < -PI) angleDiff += 2 * PI;

            if (std::abs(angleDiff) < maxRotationSpeed.effectiveValue * dt) {
                rotation.value = targetRotation.value;
            } else {
                rotation.value += maxRotationSpeed.effectiveValue * dt * (angleDiff > 0 ? 1.0f : -1.0f);
            }
        });
}
