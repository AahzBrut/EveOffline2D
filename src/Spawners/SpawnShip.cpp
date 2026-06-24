#include "SpawnShip.h"

#include "Logger.h"
#include "Components/Impl/ModuleSlot.h"


void SpawnShip(const flecs::world &world) {
    const auto firstShip = world.entity().set_doc_name("Ship 1");
    const auto secondShip = world.entity();

    const auto rifterPrefab = world
    .prefab("RifterPrefab");

    const auto firstSlot = world.entity().set<ModuleSlot>({ ModuleSlotType::Mid }).child_of(rifterPrefab).set_doc_name("Slot 1").set_name("Slot 1");

    // const auto firstSlot = world.entity().add<ModuleSlot>().child_of(firstShip).set_doc_name("Slot 1").set_name("Slot 1");
    // const auto secondSlot = world.entity().add<ModuleSlot>().child_of(firstShip).set_doc_name("Slot 2").set_name("Slot 2");
    //
    // const auto firstSlot2 = world.entity().add<ModuleSlot>().child_of(secondShip).set_doc_name("Slot 1").set_name("Slot 1");
    // const auto secondSlot2 = world.entity().add<ModuleSlot>().child_of(secondShip).set_doc_name("Slot 2").set_name("Slot 2");

    world.query_builder()
            .with<ModuleSlot>()
            .with(flecs::Prefab)
            .build()
            .each([](const flecs::entity slot) {
                LOG("Query slot: {}, {}", slot.doc_name(), slot.name().c_str());
            });

    firstShip.destruct();

    firstShip.children([](const flecs::entity child) {
        LOG("Child slot: {}", child.doc_name());
    });
}
