#include "InputSystem.h"

#include <raylib.h>
#include <raymath.h>

#include "imgui.h"
#include "Components/Commands/ApproachCommand.h"
#include "Components/Impl/Position.h"
#include "Components/Impl/Selected.h"
#include "Components/Impl/TargetPosition.h"
#include "Components/Impl/TargetRotation.h"
#include "Components/Impl/ThrustLevel.h"
#include "Utils/EntityNames.h"


void InputSystem(const flecs::world& world) {
    constexpr double doubleClickThreshold = 0.3;
    static double lastClick = 0.0;

    world
        .system(__func__)
        .kind(flecs::OnUpdate)
        .run([](const flecs::iter& it) {
            const auto currentTime = GetTime();

            const auto player = it.world().entity(EntityNames::PlayerEntity);
            auto thrustLevel = player.get<ThrustLevel>().value;

            if (IsKeyPressed(KEY_ONE)) thrustLevel = 0.1f;
            if (IsKeyPressed(KEY_TWO)) thrustLevel = 0.2f;
            if (IsKeyPressed(KEY_THREE)) thrustLevel = 0.3f;
            if (IsKeyPressed(KEY_FOUR)) thrustLevel = 0.4f;
            if (IsKeyPressed(KEY_FIVE)) thrustLevel = 0.5f;
            if (IsKeyPressed(KEY_SIX)) thrustLevel = 0.6f;
            if (IsKeyPressed(KEY_SEVEN)) thrustLevel = 0.7f;
            if (IsKeyPressed(KEY_EIGHT)) thrustLevel = 0.8f;
            if (IsKeyPressed(KEY_NINE)) thrustLevel = 0.9f;
            if (IsKeyPressed(KEY_ZERO)) thrustLevel = 0.0f;
            player.set<ThrustLevel>({thrustLevel});

            const ImGuiIO& io = ImGui::GetIO();
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !io.WantCaptureMouse) {
                it.world().set<Selected>({});
                player.remove<ApproachCommand>();
                if (currentTime - lastClick <= doubleClickThreshold) {
                    const Camera2D camera = it.world().get<Camera2D>();
                    const Vector2 mousePos = GetScreenToWorld2D(GetMousePosition(), camera);
                    const auto playerPos = player.get<Position>();
                    const auto [dirX, dirY] = mousePos - playerPos.Vector2();
                    player
                        .set<ThrustLevel>({1.0f})
                        .set<TargetPosition>({mousePos})
                        .set<TargetRotation>({atan2f(dirY, dirX)});
                }
                lastClick = currentTime;
            }
        });
}
