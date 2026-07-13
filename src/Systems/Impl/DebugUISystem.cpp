#include "DebugUISystem.h"

#include <imgui.h>
#include <raylib.h>

#include "raymath.h"
#include "Components/Impl/Rotation.h"
#include "Components/Impl/TargetRotation.h"
#include "Components/Impl/ThrustLevel.h"
#include "Components/Impl/Velocity.h"


void DebugUISystem(const flecs::world& world) {
    world
        .system(__func__)
        .kind(flecs::OnUpdate)
        .run([](const flecs::iter& it) {
            ImGui::Begin("Debug Info");

            const auto player = it.world().entity("Player");

            if (ImGui::BeginTable("Debug values", 2, ImGuiTableFlags_Resizable | ImGuiTableFlags_Borders)) {
                ImGui::TableSetupColumn("Name");
                ImGui::TableSetupColumn("Value");
                ImGui::TableHeadersRow();

                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("FPS");
                ImGui::TableNextColumn();
                ImGui::Text("%d", GetFPS());

                const auto thrustLevel = player.get<ThrustLevel>().value;
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("Thrust level");
                ImGui::TableNextColumn();
                ImGui::Text("%.0f", 100.0f * thrustLevel);

                const auto velocity = player.get<VelocityVector>().velocity;
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("Player speed");
                ImGui::TableNextColumn();
                ImGui::Text("%.0f", Vector2Length(velocity));

                const auto targetRotation = player.get<TargetRotation>().value;
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("Target rotation");
                ImGui::TableNextColumn();
                ImGui::Text("%.0f", targetRotation * RAD2DEG);

                const auto rotation = player.get<Rotation>().value;
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("Rotation");
                ImGui::TableNextColumn();
                ImGui::Text("%.0f", rotation * RAD2DEG);

                ImGui::EndTable();
            }

            ImGui::End();
        });
}
