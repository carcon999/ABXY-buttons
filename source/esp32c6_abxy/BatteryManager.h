#ifndef BATTERY_MANAGER_H
#define BATTERY_MANAGER_H

#include "Setting.h"
#include <Arduino.h>
#include "DebugSerial.h"

// Define the type for the battery level change callback function.
// It takes the new battery percentage as a parameter.
typedef void (*BatteryLevelCallback)(uint8_t newLevel);

class BatteryManager {
public:
    BatteryManager(int battPin, float battMax, float battMin);
    void begin();
    float getVoltage();
    int getPercent();
    void handleBatteryUpdate();

    // Method to set the callback function.
    void setBatteryLevelCallback(BatteryLevelCallback callback);

private:
    int _battPin;
    float _battMax;
    float _battMin;
    unsigned long _lastBatteryUpdateTime;
    uint8_t _battery_percent = 0;
    
    // Member variable to store the last reported battery level.
    uint8_t _lastReportedLevel = 0;

    // Member variable to store the callback function pointer.
    BatteryLevelCallback _levelCallback = nullptr;
};

#endif // BATTERY_MANAGER_H