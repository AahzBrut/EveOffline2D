#pragma once
#include <flecs.h>

class Application {
    flecs::world world;

public:
    void Run();

private:
    void Initialize() const;
    void DeInitialize();
};
