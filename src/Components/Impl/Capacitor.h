#pragma once


struct Capacitor {
    float baseRechargeTime;
    float currentRechargeTime;
    float baseMaxValue;
    float currentMaxValue;
    float currentValue;

    float GetCurrentChargeLevelPercent() const { return  100.0f * currentValue / currentMaxValue; }
};
