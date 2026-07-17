#include "HudSystem.h"

#include <format>
#include <raylib.h>
#include <string>

#include "defs.h"
#include "raymath.h"
#include "Components/Impl/Velocity.h"
#include "Utils/EntityNames.h"


struct VelocityVector;


void HudSystem(const flecs::world& world) {
    world
        .system(__func__)
        .kind(flecs::OnStore)
        .run([](const flecs::iter& it) {
            const auto screenWidth = GetScreenWidth();
            const auto screenHeight = GetScreenHeight();
            const auto centerX = screenWidth / 2;
            const auto centerY = 8 * screenHeight / 9;
            const auto radius = toFloat(screenHeight) / 9 - 5;
            const auto center = Vector2 {toFloat(centerX), toFloat(centerY)};
            const auto radiusPercent = radius / 100.0f;
            const auto shieldInnerRadius = 88.0f * radiusPercent;
            const auto armorOuterRadius = shieldInnerRadius - 2 * radiusPercent;
            const auto armorInnerRadius = armorOuterRadius - 12 * radiusPercent;
            const auto structureOuterRadius = armorInnerRadius - 2 * radiusPercent;
            const auto structureInnerRadius = structureOuterRadius - 12 * radiusPercent;

            DrawCircle(centerX, centerY, radius, BLACK);
            DrawRing(center, shieldInnerRadius, radius, -180.0f, 0.0f, 32, LIGHTGRAY);
            DrawRing(center, armorInnerRadius, armorOuterRadius, -180.0f, 0.0f, 32, LIGHTGRAY);
            DrawRing(center, structureInnerRadius, structureOuterRadius, -180.0f, 0.0f, 32, LIGHTGRAY);
            DrawCircle(centerX, centerY, 50.0f * radiusPercent, GOLD);
            DrawRing(center, structureInnerRadius, radius, 40.0f, 140.0f, 32, GRAY);

            const auto player = it.world().entity(EntityNames::PlayerEntity);
            const auto speed = Vector2Length(player.get<VelocityVector>().velocity);
            const auto speedStr = std::format("{:L}m/s", roundf(speed));

            const auto textSize = MeasureText(speedStr.c_str(), 22.0f);
            DrawText(speedStr.c_str(), centerX - textSize / 2,
                     toFloat(center.y + structureInnerRadius) + 5 * radiusPercent, 22.0f, BLACK);
        });
}
