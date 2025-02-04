#pragma once
#include <flecs.h>

#include "Impl/RenderFPSSystem.h"


inline void RegisterSystems(const flecs::world &world) {
    RenderFPSSystem(world);
}
