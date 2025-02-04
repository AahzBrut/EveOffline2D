#include "RenderBackgroundSystem.h"

#include "defs.h"
#include "AssetManager/AssetManager.h"
#include "AssetManager/Assets.h"


void RenderBackgroundSystem(const flecs::world &world) {
    const auto assetManager = world.get_mut<AssetManager>();

    world
            .system(__func__)
            .kind(flecs::OnStore)
            .run([assetManager](flecs::iter &) {
                const auto backgroundImage = assetManager->GetTexture(BackgroundImage);
                const auto srcRect = Rectangle{0, 0, toFloat(backgroundImage->width), toFloat(backgroundImage->height)};
                constexpr auto dstRect = Rectangle{0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
                DrawTexturePro(*backgroundImage, srcRect, dstRect, {}, 0, WHITE);
            });
}
