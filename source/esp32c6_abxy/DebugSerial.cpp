#include "DebugSerial.h"

DebugSerial Debug;

void DebugSerial::printf(const char *fmt, ...) {
#if DEBUG_ENABLED
    char loc_buf[64];
    char * temp = loc_buf;
    va_list arg;
    va_start(arg, fmt);
    int len = vsnprintf(temp, sizeof(loc_buf), fmt, arg);
    va_end(arg);
    if(len < 0) {
        return;
    } else if(len >= sizeof(loc_buf)) {
        // 例: temp = (char*) malloc(len + 1);
        //     if(temp) {
        //         va_start(arg, fmt);
        //         vsnprintf(temp, len + 1, fmt, arg);
        //         va_end(arg);
        //     }
    }
    Serial.print(temp);
    // if(temp != loc_buf) {
    //     free(temp);
    // }
#endif
}