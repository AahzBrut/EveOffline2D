#include "RenderSpriteSystem.h"

#include <raylib.h>

#include "defs.h"
#include "Logger.h"
#include "Components/Impl/Position.h"
#include "Components/Impl/Rotation.h"
#include "Components/Impl/Sprite.h"


void RenderSpriteSystem(const flecs::world &world) {
    world
            .system<const Position, const Sprite, const Rotation>(__func__)
            .kind(flecs::OnStore)
            .each([](const Position &position, const Sprite &sprite, const Rotation &rotation) {
                const auto dstRect = sprite.GetDstRect({toFloat(position.x), toFloat(position.y)});
                DrawTexturePro(
                    *sprite.texture,
                    sprite.GetSrcRect(),
                    sprite.GetDstRect({toFloat(position.x), toFloat(position.y)}),
                    sprite.GetCenterOrigin(),
                    rotation.value * RAD2DEG + sprite.rotation * RAD2DEG,
                    WHITE
                );

                DrawCircle(toInt(dstRect.x), toInt(dstRect.y), 10.0f, WHITE);
            });
}
