#include "BatteryManager.h"

BatteryManager::BatteryManager(int battPin, float battMax, float battMin)
    : _battPin(battPin), _battMax(battMax), _battMin(battMin), _lastBatteryUpdateTime(0) {
}

void BatteryManager::begin() {
    pinMode(_battPin, INPUT);
    // Get the initial battery level and store it.
    _lastReportedLevel = getPercent();
}

float BatteryManager::getVoltage() {
    uint32_t Vbatt = 0;
    // Averaging over 16 samples
    for(int i = 0; i < 16; i++) {
        Vbatt += analogReadMilliVolts(_battPin);
    }
    // The XIAO ESP32C6 uses a voltage divider circuit to halve the voltage,
    // so multiply it by 2 to convert mV to V.
    return 2.0 * Vbatt / 16.0 / 1000.0;
}

int BatteryManager::getPercent() {
    float voltage = getVoltage();
    _battery_percent = 0;

#if DEBUG_BATT
    _battery_percent = (voltage - 3.0) * 100.0;
#else
    if (voltage >= _battMax) {
        _battery_percent = 100;
    } else if (voltage <= _battMin) {
        _battery_percent = 0;
    } else {
        _battery_percent = static_cast<uint8_t>(
            (voltage - _battMin) / (_battMax - _battMin) * 100.0
        );
    }
#endif
    return _battery_percent;
}

// Sets the callback function.
void BatteryManager::setBatteryLevelCallback(BatteryLevelCallback callback) {
    _levelCallback = callback;
}

void BatteryManager::handleBatteryUpdate() {
    unsigned long now = millis();
    
    if (now - _lastBatteryUpdateTime >= BATTERY_REPORT_INTERVAL_MS) {
        int newLevel = getPercent();
        
        // Only call the callback if the battery level has changed.
        if (newLevel != _lastReportedLevel) {
            Debug.printf("Battery level changed: %d%% -> %d%%\n", _lastReportedLevel, newLevel);
            
            // Call the callback function if it's set.
            if (_levelCallback) {
                _levelCallback(newLevel);
            }

            _lastReportedLevel = newLevel; // Update the last reported level.
        }
        
        _lastBatteryUpdateTime = now;
    }
}

