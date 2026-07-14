#include "SpawnNPC.h"

#include "AssetManager/AssetManager.h"
#include "AssetManager/Assets.h"
#include "Components/Impl/Acceleration.h"
#include "Components/Impl/MaxRotationSpeed.h"
#include "Components/Impl/MaxSpeed.h"
#include "Components/Impl/MouseCollider.h"
#include "Components/Impl/Position.h"
#include "Components/Impl/Rotation.h"
#include "Components/Impl/Speed.h"
#include "Components/Impl/Sprite.h"
#include "Components/Impl/TargetRotation.h"
#include "Components/Impl/ThrustLevel.h"
#include "Components/Impl/Velocity.h"


void SpawnNPC(const flecs::world& world) {
    const auto assetManager = &world.get_mut<AssetManager>();

    const auto npc = world
        .entity()
        .insert([assetManager](
            Position& position,
            Sprite& sprite,
            VelocityVector& velocity,
            MaxSpeed& maxSpeed,
            Rotation& rotation,
            Acceleration& acceleration,
            MaxRotationSpeed& maxRotationSpeed,
            TargetRotation& targetRotation,
            ThrustLevel& thrustLevel,
            Speed& speed,
            MouseCollider& mouseCollider
        ) {
                const auto spriteTexture = assetManager->GetTexture(NpcShipSprite);
                position = {300, 100};
                sprite = {
                    {}, {toFloat(spriteTexture->width), toFloat(spriteTexture->height)}, spriteTexture, PI / 2, 0.5f
                };
                velocity = {{0, 0}};
                maxSpeed = {450.0f, 450.0f};
                rotation = {0.0f};
                acceleration = {50.0f, 50.0f};
                maxRotationSpeed = {30.0f * DEG2RAD, 30.0f * DEG2RAD};
                thrustLevel = {0.0f};
                targetRotation = {0.0f};
                speed = {0.0f, 0.0f};
                mouseCollider = {sprite.GetCenterOrigin().x / 2};
            });
    npc.set_doc_name("NPC");
}
