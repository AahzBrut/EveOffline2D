#include "HudSystem.h"

#include <format>
#include <raylib.h>
#include <string>

#include "defs.h"
#include "raymath.h"
#include "Components/Impl/Capacitor.h"
#include "Components/Impl/MaxSpeed.h"
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

            const auto player = it.world().entity(EntityNames::PlayerEntity);
            const auto speed = Vector2Length(player.get<VelocityVector>().velocity);
            const auto maxSpeed = player.get<MaxSpeed>().effectiveValue;
            const auto speedPercent = speed / maxSpeed;
            const auto capacitorChargePercent = player.get<Capacitor>().GetCurrentChargeLevelPercent();

            // BACKGROUND
            DrawCircle(centerX, centerY, radius, BLACK);
            // SHIELD
            DrawRing(center, shieldInnerRadius, radius, -225.0f, -45.0f, 32, LIGHTGRAY);
            // ARMOR
            DrawRing(center, armorInnerRadius, armorOuterRadius, -225.0f, -45.0f, 32, LIGHTGRAY);
            // STRUCTURE
            DrawRing(center, structureInnerRadius, structureOuterRadius, -225.0f, -45.0f, 32, LIGHTGRAY);
            // CENTER
            DrawCircle(centerX, centerY, 50.0f * radiusPercent, GOLD);
            // CAPACITOR LEVEL INDICATOR
            DrawRing(center, structureOuterRadius, radius, 45.0f - 85.0f * capacitorChargePercent / 100.0f, 45.0f, 32, BLUE);
            // SPEED TEXT
            DrawRing(center, structureOuterRadius, radius, 50.0f, 130.0f, 32, GRAY);
            // SPEED INDICATOR
            DrawRing(center, structureInnerRadius, structureOuterRadius - 6 * radiusPercent, 130.0f - 170.0f * speedPercent, 130.0f, 32,
                     DARKBLUE);

            const auto speedStr = std::format("{:L}m/s", roundf(speed));

            const auto textSize = MeasureText(speedStr.c_str(), 22.0f);
            DrawText(speedStr.c_str(), centerX - textSize / 2,
                     toFloat(center.y + structureInnerRadius) + 12 * radiusPercent, 22.0f, BLACK);

            const auto capacitorStr = std::format("{:L}%", roundf(capacitorChargePercent));
            const auto capacitorTextSize = MeasureText(capacitorStr.c_str(), 32.0f);
            DrawText(capacitorStr.c_str(), centerX - capacitorTextSize / 2,
                     toFloat(center.y) - 16.0f, 32.0f, BLACK);
        });
}
