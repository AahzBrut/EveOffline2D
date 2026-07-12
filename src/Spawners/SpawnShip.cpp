#include "SpawnShip.h"

#include "Logger.h"
#include "Components/Impl/ModuleSlot.h"


void SpawnShip(const flecs::world &world) {
    const auto rifterPrefab = world.prefab("RifterPrefab");

    const auto firstSlot = world.entity().add(ModuleSlotType::High).child_of(rifterPrefab).set_name("Slot 1");
    const auto secondSlot = world.entity().add(ModuleSlotType::Mid).child_of(rifterPrefab).set_name("Slot 2");


    const auto firstShip = world.entity().is_a(rifterPrefab).set_name("Ship 1");
    const auto secondShip = world.entity().is_a(rifterPrefab).set_name("Ship 2");

    // const auto firstSlot = world.entity().add<ModuleSlot>().child_of(firstShip).set_doc_name("Slot 1").set_name("Slot 1");
    // const auto secondSlot = world.entity().add<ModuleSlot>().child_of(firstShip).set_doc_name("Slot 2").set_name("Slot 2");
    //
    // const auto firstSlot2 = world.entity().add<ModuleSlot>().child_of(secondShip).set_doc_name("Slot 1").set_name("Slot 1");
    // const auto secondSlot2 = world.entity().add<ModuleSlot>().child_of(secondShip).set_doc_name("Slot 2").set_name("Slot 2");

    world.query_builder()
            .with<ModuleSlotType>(flecs::Wildcard)
            .with(flecs::Prefab)
            .build()
            .each([](const flecs::entity slot) {
                LOG("Prefab Query slot: {}", slot.name().c_str());
            });

    world.query_builder()
            .with<ModuleSlotType>(flecs::Wildcard)
            .build()
            .each([](const flecs::entity slot) {
                LOG("Module slot: {} - {}", slot.parent().name().c_str(), slot.name().c_str());
            });
}
