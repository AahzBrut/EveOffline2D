#pragma once


struct Selected {
    flecs::entity entity;

    bool IsValid() const { return entity.is_valid(); }
};
