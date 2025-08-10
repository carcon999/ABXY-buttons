#include "LedController.h"

LedController::LedController(int rPin, int gPin, int bPin, int builtinLedPin)
    : _rPin(rPin), _gPin(gPin), _bPin(bPin), _builtinLedPin(builtinLedPin) {
}

void LedController::begin() {
    pinMode(_rPin, OUTPUT);
    pinMode(_gPin, OUTPUT);
    pinMode(_bPin, OUTPUT);
    _setRgbColor(COLOR_BLACK);

    pinMode(_builtinLedPin, OUTPUT);
    setBuiltinLed(false);
    
    // 点滅状態の初期化
    _isBlinking = false;
    _blinkInterval = 0;
    _lastBlinkTime = 0;
    _blinkColor = COLOR_BLACK;
    _blinkingState = false;
}

// 点灯と点滅を統合したメソッド
void LedController::setColor(int color, unsigned long interval) { // ★変更点★
    if (interval == 0) {
        // 点滅を停止し、指定した色で点灯
        _isBlinking = false;
        _setRgbColor(color);
    } else {
        // 点滅を開始
        _isBlinking = true;
        _blinkInterval = interval;
        _lastBlinkTime = millis();
        _blinkColor = color;
        _blinkingState = true; // 初回は点灯から開始
        _setRgbColor(_blinkColor);
    }
}

void LedController::setBuiltinLed(bool state) {
    // For XIAO C6, turn on LOW
    digitalWrite(_builtinLedPin, state ? LOW : HIGH);
}

// 点滅を更新するメソッド (loop()から呼び出す)
void LedController::update() {
    if (_isBlinking && (millis() - _lastBlinkTime >= _blinkInterval)) {
        _blinkingState = !_blinkingState; // 状態を反転
        if (_blinkingState) {
            // 点灯
            _setRgbColor(_blinkColor);
        } else {
            // 消灯
            _setRgbColor(COLOR_BLACK);
        }
        _lastBlinkTime = millis();
    }
}

// RGB LEDの直接制御用プライベートメソッド
void LedController::_setRgbColor(int color) { // ★追加点★
    digitalWrite(_rPin, (color >> 0) & 0x01);
    digitalWrite(_gPin, (color >> 1) & 0x01);
    digitalWrite(_bPin, (color >> 2) & 0x01);
}