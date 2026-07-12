#include "DebugUISystem.h"

#include <imgui.h>
#include <raylib.h>

#include "raymath.h"
#include "Components/Impl/Velocity.h"


void DebugUISystem(const flecs::world& world) {
    world
        .system(__func__)
        .kind(flecs::OnUpdate)
        .run([](const flecs::iter& it) {
            ImGui::Begin("Debug Info");

            if (ImGui::BeginTable("Debug values", 2, ImGuiTableFlags_Resizable | ImGuiTableFlags_Borders)) {
                ImGui::TableSetupColumn("Name");
                ImGui::TableSetupColumn("Value");
                ImGui::TableHeadersRow();

                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("FPS");
                ImGui::TableNextColumn();
                ImGui::Text("%d", GetFPS());

                const auto velocity = it.world()
                                        .entity("Player")
                                        .get<VelocityVector>().velocity;

                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("Player speed");
                ImGui::TableNextColumn();
                ImGui::Text("%.0f", Vector2Length(velocity));

                ImGui::EndTable();
            }

            ImGui::End();
        });
}
