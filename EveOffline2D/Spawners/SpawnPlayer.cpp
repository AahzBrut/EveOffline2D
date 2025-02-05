#include "SpawnPlayer.h"

#include "defs.h"
#include "AssetManager/AssetManager.h"
#include "AssetManager/Assets.h"
#include "Components/Impl/Position.h"
#include "Components/Impl/Sprite.h"


void SpawnPlayer(const flecs::world &world) {
    const auto assetManager = world.get_mut<AssetManager>();

    // ReSharper disable once CppExpressionWithoutSideEffects
    world
            .entity("Player")
            .insert([assetManager](Position &position, Sprite &sprite) {
                const auto spriteTexture = assetManager->GetTexture(ShipSprite);
                position = {300, 300};
                sprite = {{}, {toFloat(spriteTexture->width), toFloat(spriteTexture->height)}, spriteTexture};
            });
}
