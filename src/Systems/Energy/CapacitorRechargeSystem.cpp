#include "CapacitorRechargeSystem.h"

#include <algorithm>
#include <cmath>

#include "Logger.h"
#include "Components/Impl/Capacitor.h"

constexpr float LinearRechargeThreshold = 0.05f;
constexpr float LinearRechargeMultiplier = 15.0f;

void CapacitorRechargeSystem(const flecs::world& world) {
    world
        .system<Capacitor>(__func__)
        .kind(flecs::OnUpdate)
        .each([](const flecs::iter& it, const size_t, Capacitor& capacitor) {
            const float dt = it.delta_time();
            if (capacitor.currentValue < capacitor.currentMaxValue) {
                const auto currentChargePercent = capacitor.currentValue / capacitor.currentMaxValue;
                float rechargeRate = 0.0f;
                if (currentChargePercent < LinearRechargeThreshold) {
                    rechargeRate = (currentChargePercent * LinearRechargeMultiplier + 0.1f) * (capacitor.currentMaxValue / capacitor.currentRechargeTime);
                } else {
                    rechargeRate = capacitor.currentMaxValue / capacitor.currentRechargeTime * 10.0f *
                        std::sqrtf(currentChargePercent) * (1 - currentChargePercent);
                    }
                capacitor.currentValue = std::min(capacitor.currentValue + rechargeRate * dt,
                                                  capacitor.currentMaxValue);
            }
        });
}
