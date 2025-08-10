#include "SleepManager.h"

SleepManager::SleepManager(const int* wakeupPins, int numWakeupPins)
    : _wakeupPins(wakeupPins), _numWakeupPins(numWakeupPins) {
}

void SleepManager::setupWakeup() {
    uint64_t wakeup_pin_mask = 0;
    for (int i = 0; i < _numWakeupPins; i++) {
        wakeup_pin_mask |= (1ULL << _wakeupPins[i]);
    }
    esp_sleep_enable_ext1_wakeup(wakeup_pin_mask, ESP_EXT1_WAKEUP_ANY_HIGH);
}

void SleepManager::enterDeepSleep() {
    
    esp_deep_sleep_start();

    // ここに到達することはない
    while(1){}
}

esp_sleep_wakeup_cause_t SleepManager::getWakeupCause() {
    return esp_sleep_get_wakeup_cause();
}
