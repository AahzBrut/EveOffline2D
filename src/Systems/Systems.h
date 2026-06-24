#pragma once
#include <flecs.h>

#include "Impl/CameraControlSystem.h"
#include "Impl/InputSystem.h"
#include "Impl/MovementSystem.h"
#include "Impl/RenderBackgroundSystem.h"
#include "Impl/RenderFPSSystem.h"
#include "Impl/RenderSpriteSystem.h"
#include "Impl/RotationSystem.h"


inline void RegisterSystems(const flecs::world &world) {
    CameraControlSystem(world);
    InputSystem(world);
    RotationSystem(world);
    MovementSystem(world);
    RenderBackgroundSystem(world);
    RenderSpriteSystem(world);
    RenderFPSSystem(world);
}
