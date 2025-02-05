#include "RenderSpriteSystem.h"

#include <raylib.h>

#include "defs.h"
#include "Components/Impl/Position.h"
#include "Components/Impl/Sprite.h"


void RenderSpriteSystem(const flecs::world &world) {
    const auto camera = world.get<Camera2D>();

    world
            .system<const Position, const Sprite>(__func__)
            .kind(flecs::OnStore)
            .each([camera](const Position &position, const Sprite &sprite) {
                BeginMode2D(*camera);
                DrawTexturePro(
                    *sprite.texture,
                    sprite.GetSrcRect(),
                    sprite.GetDstRect({toFloat(position.x), toFloat(position.y)}),
                    sprite.GetCenterOrigin(),
                    0,
                    WHITE
                );
                EndMode2D();
            });
}
