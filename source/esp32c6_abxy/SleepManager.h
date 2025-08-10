#ifndef SLEEP_MANAGER_H
#define SLEEP_MANAGER_H

#include "Setting.h"
#include <Arduino.h>
#include "esp_sleep.h"

class SleepManager {
public:
    SleepManager(const int* wakeupPins, int numWakeupPins);
    
    void setupWakeup();
    
    void enterDeepSleep();

    esp_sleep_wakeup_cause_t getWakeupCause();

private:
    const int* _wakeupPins;
    int _numWakeupPins;
};

#endif // SLEEP_MANAGER_H
