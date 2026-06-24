#include "SpawnPlayer.h"

#include "defs.h"
#include "AssetManager/AssetManager.h"
#include "AssetManager/Assets.h"
#include "Components/Impl/MaxSpeed.h"
#include "Components/Impl/Position.h"
#include "Components/Impl/Rotation.h"
#include "Components/Impl/Sprite.h"
#include "Components/Impl/Velocity.h"


void SpawnPlayer(const flecs::world &world) {
    const auto assetManager = &world.get_mut<AssetManager>();

    world
            .entity("Player")
            .insert([assetManager](Position &position, Sprite &sprite, VelocityVector &velocity, MaxSpeed &maxSpeed, Rotation &rotation) {
                const auto spriteTexture = assetManager->GetTexture(ShipSprite);
                position = {300, 300};
                sprite = {{}, {toFloat(spriteTexture->width), toFloat(spriteTexture->height)}, spriteTexture};
                velocity = {{0, 0}};
                maxSpeed = {200.0f};
                rotation = {0.0f};
            });
}
