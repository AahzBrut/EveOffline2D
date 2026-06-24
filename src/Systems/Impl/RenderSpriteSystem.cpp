#include "RenderSpriteSystem.h"

#include <raylib.h>

#include "defs.h"
#include "Components/Impl/Position.h"
#include "Components/Impl/Rotation.h"
#include "Components/Impl/Sprite.h"


void RenderSpriteSystem(const flecs::world &world) {
    const auto camera = &world.get<Camera2D>();

    world
            .system<const Position, const Sprite, const Rotation>(__func__)
            .kind(flecs::OnStore)
            .each([camera](const Position &position, const Sprite &sprite, const Rotation &rotation) {
                BeginMode2D(*camera);
                DrawTexturePro(
                    *sprite.texture,
                    sprite.GetSrcRect(),
                    sprite.GetDstRect({toFloat(position.x), toFloat(position.y)}),
                    sprite.GetCenterOrigin(),
                    rotation.angle + 90.0f,
                    WHITE
                );
                EndMode2D();
            });
}
