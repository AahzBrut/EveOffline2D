#pragma once
#include "AssetManager/AssetManager.h"
#include "AudioManager/AudioManager.h"
#include "Impl/Position.h"
#include "Impl/Sprite.h"


// ReSharper disable file CppExpressionWithoutSideEffects
inline void RegisterComponents(const flecs::world &ecsWorld) {
    ecsWorld.component<AssetManager>();
    ecsWorld.component<AudioManager>();
    ecsWorld.component<Sprite>();
    ecsWorld.component<Position>();
}
