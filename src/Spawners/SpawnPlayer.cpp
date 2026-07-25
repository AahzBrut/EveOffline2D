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
#include "Components/Impl/Trail.h"
#include "Components/Impl/VelocityVector.h"
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
                            Capacitor& capacitor,
                            Trail& trail
                        ) {
                                const auto spriteTexture = assetManager->GetTexture(ShipSprite);
                                position = {.x = 300, .y = 500};
                                sprite = {
                                    .offset = {}, .size = {.x = toFloat(spriteTexture->width), .y = toFloat(spriteTexture->height)}, .texture = spriteTexture,
                                    .rotation = PI / 2, .scale = 0.5f
                                };
                                velocity = {{.x = 0, .y = 0}};
                                maxSpeed = {.baseValue = 450.0f, .effectiveValue = 450.0f};
                                rotation = {0.0f};
                                acceleration = {.baseValue = 50.0f, .effectiveValue = 50.0f};
                                maxRotationSpeed = {.baseValue = 30.0f * DEG2RAD, .effectiveValue = 30.0f * DEG2RAD};
                                thrustLevel = {0.0f};
                                targetRotation = {0.0f};
                                speed = {.baseValue = 0.0f, .effectiveValue = 0.0f};
                                mouseCollider = {sprite.GetCenterOrigin().x / 2};
                                capacitor = {.baseRechargeTime = 187.5, .currentRechargeTime = 187.5, .baseMaxValue = 250, .currentMaxValue = 250, .currentValue = 0};
                                trail = {};
                            });
    player.add<MovementState, IdleState>();
    player.set_doc_name("Player");
}
