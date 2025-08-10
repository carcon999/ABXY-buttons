#ifndef DEBUG_SERIAL_H
#define DEBUG_SERIAL_H

#include "Setting.h"
#include <Arduino.h>

class DebugSerial {
public:
    DebugSerial() {
    }

    void begin(unsigned long baud) {
#if DEBUG_ENABLED
        Serial.begin(baud);
        delay(1000);
#endif
    }

    template<typename T>
    size_t print(T arg) {
#if DEBUG_ENABLED
        return Serial.print(arg);
#else
        return 0;
#endif
    }

    template<typename T>
    size_t print(T arg, int format) {
#if DEBUG_ENABLED
        return Serial.print(arg, format);
#else
        return 0;
#endif
    }

    template<typename T>
    size_t println(T arg) {
#if DEBUG_ENABLED
        return Serial.println(arg);
#else
        return 0;
#endif
    }

    template<typename T>
    size_t println(T arg, int format) {
#if DEBUG_ENABLED
        return Serial.println(arg, format);
#else
        return 0;
#endif
    }
    
    size_t println() {
#if DEBUG_ENABLED
        return Serial.println();
#else
        return 0;
#endif
    }

    void printf(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
    
};

extern DebugSerial Debug;

#endif // DEBUG_SERIAL_H