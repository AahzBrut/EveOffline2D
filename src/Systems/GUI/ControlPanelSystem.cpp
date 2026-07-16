#include "ControlPanelSystem.h"

#include <imgui.h>

#include "Logger.h"
#include "raymath.h"
#include "Components/Commands/ApproachState.h"
#include "Components/Commands/MovementState.h"
#include "Components/Commands/OrbitState.h"
#include "Components/Impl/Position.h"
#include "Components/Impl/Selected.h"
#include "Utils/EntityNames.h"


void ControlPanelSystem(const flecs::world& world) {
    world
        .system(__func__)
        .kind(flecs::OnStore)
        .run([](const flecs::iter& it) {
            ImGui::Begin("Control panel", nullptr, ImGuiWindowFlags_NoCollapse);

            const auto player = it.world().entity(EntityNames::PlayerEntity);
            const auto selectedObject = it.world().get<Selected>();
            const auto selectedObjectName = selectedObject.IsValid() ? selectedObject.entity.doc_name() : "NONE";
            ImGui::Text("%s", selectedObjectName);

            if (selectedObject.IsValid()) {
                const auto distanceToTarget = Vector2Distance(
                    selectedObject.entity.get<Position>().Vector2(),
                    player.get<Position>().Vector2()
                );
                ImGui::Text("%.0f m", distanceToTarget);

                if (ImGui::Button("Approach")) {
                    player.set<MovementState, ApproachState>({selectedObject.entity, 200});
                }
                ImGui::SameLine();
                if (ImGui::Button("Keep distance")) {
//                    player.set<MovementState, KeepDistanceState>({selectedObject.entity, 500});
                }
                ImGui::SameLine();
                if (ImGui::Button("Orbit")) {
                    player.set<MovementState, OrbitState>({selectedObject.entity, 500});
                }
            }

            ImGui::End();
        });
}
