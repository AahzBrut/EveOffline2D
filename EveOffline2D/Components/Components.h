#pragma once
#include "AssetManager/AssetManager.h"
#include "AudioManager/AudioManager.h"
#include "Impl/Position.h"
#include "Impl/Sprite.h"


// ReSharper disable file CppExpressionWithoutSideEffects
inline void RegisterComponents(const flecs::world &world) {
    world.component<AssetManager>();
    world.component<AudioManager>();
    world.component<Sprite>();
    world.component<Position>();
    world.component<Camera2D>();
}
