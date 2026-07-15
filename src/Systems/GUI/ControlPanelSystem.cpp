#include "ControlPanelSystem.h"

#include <imgui.h>

#include "Components/Commands/ApproachCommand.h"
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
                if (ImGui::Button("Approach")) {
                    player.set<ApproachCommand>({selectedObject.entity, 200});
                }
                ImGui::SameLine();
                ImGui::Button("Keep distance");
                ImGui::SameLine();
                ImGui::Button("Orbit");
            }

            ImGui::End();
        });
}
