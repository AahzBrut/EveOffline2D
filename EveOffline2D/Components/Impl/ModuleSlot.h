#pragma once


enum class ModuleSlotType : int {
    High,
    Mid,
    Low
};

struct ModuleSlot {
    ModuleSlotType type;
};