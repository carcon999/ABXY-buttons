#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include <Arduino.h>

// 色定義
#define COLOR_BLACK   0b00000111
#define COLOR_RED     0b00000110
#define COLOR_GREEN   0b00000101
#define COLOR_BLUE    0b00000011
#define COLOR_YELLOW  0b00000100
#define COLOR_MAGENTA 0b00000010
#define COLOR_CYAN    0b00000001
#define COLOR_WHITE   0b00000000

class LedController {
public:
    LedController(int rPin, int gPin, int bPin, int builtinLedPin);
    void begin();

    void setColor(int color, unsigned long interval = 0);
    void setBuiltinLed(bool state);
    void update();

private:
    int _rPin;
    int _gPin;
    int _bPin;
    int _builtinLedPin;
    
    // 点滅状態管理のための変数
    bool _isBlinking = false;
    unsigned long _blinkInterval = 0;
    unsigned long _lastBlinkTime = 0;
    int _blinkColor = COLOR_BLACK;
    bool _blinkingState = false; // true: 点灯, false: 消灯
    
    void _setRgbColor(int color);
};

#endif // LED_CONTROLLER_H