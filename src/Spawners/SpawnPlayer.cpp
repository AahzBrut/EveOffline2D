#include "SpawnPlayer.h"

#include "defs.h"
#include "AssetManager/AssetManager.h"
#include "AssetManager/Assets.h"
#include "Components/Commands/IdleState.h"
#include "Components/Commands/MovementState.h"
#include "Components/Impl/Acceleration.h"
#include "Components/Impl/Capacitor.h"
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
#include "Utils/EntityNames.h"


void SpawnPlayer(const flecs::world& world) {
    const auto assetManager = &world.get_mut<AssetManager>();

    const auto player = world
                        .entity(EntityNames::PlayerEntity)
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
                            MouseCollider& mouseCollider,
                            Capacitor& capacitor
                        ) {
                                const auto spriteTexture = assetManager->GetTexture(ShipSprite);
                                position = {300, 500};
                                sprite = {
                                    {}, {toFloat(spriteTexture->width), toFloat(spriteTexture->height)}, spriteTexture,
                                    PI / 2, 0.5f
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
                                capacitor = {187.5, 187.5, 250, 250, 0};
                            });
    player.add<MovementState, IdleState>();
    player.set_doc_name("Player");
}
