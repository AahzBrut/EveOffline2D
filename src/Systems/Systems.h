#pragma once
#include <flecs.h>

#include "Impl/CameraControlSystem.h"
#include "Impl/DebugUISystem.h"
#include "Impl/InputSystem.h"
#include "Impl/MovementSystem.h"
#include "Impl/RenderBackgroundSystem.h"
#include "Impl/RenderSpriteSystem.h"
#include "Impl/RotationSytem.h"
#include "Impl/ThrustSystem.h"


inline void RegisterSystems(const flecs::world &world) {
    CameraControlSystem(world);
    InputSystem(world);
    MovementSystem(world);
    RenderBackgroundSystem(world);
    RenderSpriteSystem(world);
    DebugUISystem(world);
    RotationSystem(world);
    ThrustSystem(world);
}
