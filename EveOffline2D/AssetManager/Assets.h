#pragma once

#include <flecs.h>

#include "AssetManager/AssetManager.h"


const auto BackgroundImage = std::string("background-image");
const auto ShipSprite = std::string("ship-sprite");


inline void LoadAssets(const flecs::world &world) {
    const auto assetManager = world.get_mut<AssetManager>();

    assetManager->LoadTexture(BackgroundImage, "./assets/gfx/background/Purple_Nebula_01-1024x1024.png");
    assetManager->LoadTexture(ShipSprite, "./assets/gfx/ships/falcon_base.png");
}
