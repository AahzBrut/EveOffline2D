#pragma once

#include <flecs.h>

#include "AssetManager/AssetManager.h"


constexpr auto BackgroundImage = "background-image";
constexpr auto ShipSprite = "ship-sprite";
constexpr auto NpcShipSprite = "npc-ship-sprite";


inline void LoadAssets(const flecs::world &world) {
    const auto assetManager = &world.get_mut<AssetManager>();

    assetManager->LoadTexture(BackgroundImage, "./assets/gfx/background/Purple_Nebula_01-1024x1024.png");
    assetManager->LoadTexture(ShipSprite, "./assets/gfx/ships/falcon_base.png");
    assetManager->LoadTexture(NpcShipSprite, "./assets/gfx/ships/Ship-1.png");
}
