#pragma once
#include <flecs.h>

#include "BackgroundRender/RenderBackgroundSystem.h"
#include "GUI/BeginImGuiSystem.h"
#include "GUI/ControlPanelSystem.h"
#include "GUI/DebugUISystem.h"
#include "GUI/EndImGuiSystem.h"
#include "Input/CameraControlSystem.h"
#include "Input/InputSystem.h"
#include "Input/SelectObjectSystem.h"
#include "LocalRender/BeginCameraSystem.h"
#include "LocalRender/EndCameraSystem.h"
#include "LocalRender/RenderSpriteSystem.h"
#include "Movement/ApproachSystem.h"
#include "Movement/MovementSystem.h"
#include "Movement/OrbitSystem.h"
#include "Movement/RotationSytem.h"
#include "Movement/ThrustSystem.h"


inline void RegisterSystems(const flecs::world &world) {
    CameraControlSystem(world);
    InputSystem(world);
    ApproachSystem(world);
    OrbitSystem(world);
    SelectObjectSystem(world);
    RotationSystem(world);
    ThrustSystem(world);
    MovementSystem(world);
    RenderBackgroundSystem(world);
    BeginCameraSystem(world);
    RenderSpriteSystem(world);
    EndCameraSystem(world);
    BeginImGuiSystem(world);
    ControlPanelSystem(world);
    DebugUISystem(world);
    EndImGuiSystem(world);
}
