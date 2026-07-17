#include "DebugUISystem.h"

#include <imgui.h>
#include <raylib.h>

#include "Logger.h"
#include "raymath.h"
#include "Components/Impl/Capacitor.h"
#include "Components/Impl/Position.h"
#include "Components/Impl/Rotation.h"
#include "Components/Impl/Selected.h"
#include "Components/Impl/TargetRotation.h"
#include "Components/Impl/ThrustLevel.h"
#include "Components/Impl/Velocity.h"
#include "Utils/EntityNames.h"


void DebugUISystem(const flecs::world& world) {
    world
        .system(__func__)
        .kind(flecs::OnStore)
        .run([](const flecs::iter& it) {
            ImGui::Begin("Debug Info");

            const auto player = it.world().entity(EntityNames::PlayerEntity);

            if (ImGui::BeginTable("Debug values", 2, ImGuiTableFlags_Resizable | ImGuiTableFlags_Borders)) {
                ImGui::TableSetupColumn("Name");
                ImGui::TableSetupColumn("Value");
                ImGui::TableHeadersRow();

                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("FPS");
                ImGui::TableNextColumn();
                ImGui::Text("%d", GetFPS());

                const auto capacitorCapacity = player.get<Capacitor>().currentValue;
                const auto capacitorPercent = 100.0f * capacitorCapacity / player.get<Capacitor>().currentMaxValue;
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("Capacitor capacity");
                ImGui::TableNextColumn();
                ImGui::Text("%.0f (%.0f%)", capacitorCapacity, capacitorPercent);

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

                const auto selectedObject = it.world().get<Selected>();
                const auto selectedObjectName = selectedObject.entity.is_valid()
                                                    ? selectedObject.entity.doc_name()
                                                    : "NONE";
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("Selected object");
                ImGui::TableNextColumn();
                ImGui::Text("%s", selectedObjectName);

                static float lastAngle = 0.0f;
                const float currentAngle = selectedObject.entity.is_valid()
                                               ? Vector2Angle(player.get<Rotation>().ForwardVector(),
                                                              Vector2Normalize(
                                                                  selectedObject.entity.get<Position>().Vector2() -
                                                                  player.get<Position>().Vector2()))
                                               : 0.0f;
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("Selected object angular velocity");
                ImGui::TableNextColumn();
                ImGui::Text("%f", abs(currentAngle - lastAngle) * RAD2DEG / it.delta_time());
                lastAngle = currentAngle;

                ImGui::EndTable();
            }

            ImGui::End();
        });
}
