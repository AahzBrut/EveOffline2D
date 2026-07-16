#include "MovementSystem.h"

#include <cmath>
#include <raylib.h>
#include <raymath.h>

#include "Components/Impl/Position.h"
#include "Components/Impl/Rotation.h"
#include "Components/Impl/Speed.h"
#include "Components/Impl/Velocity.h"


void MovementSystem(const flecs::world& world) {
    world
        .system<Position, VelocityVector, const Speed, const Rotation>(__func__)
        .kind(flecs::OnUpdate)
        .each([](const flecs::iter& it, const size_t,
                 Position& position, VelocityVector& velocity, const Speed& speed, const Rotation& rotation) {
            const float dt = it.delta_time();

            velocity.velocity = rotation.ForwardVector() * speed.effectiveValue;

            position.x += velocity.velocity.x * dt;
            position.y += velocity.velocity.y * dt;
        });
}
