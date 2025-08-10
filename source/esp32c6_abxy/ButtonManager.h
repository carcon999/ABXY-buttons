#ifndef BUTTON_MANAGER_H
#define BUTTON_MANAGER_H

#include <Arduino.h>
#include "DebugSerial.h"

// --- Button Map Definitions ---
struct ButtonMap {
    int pin;
    int pinModeType;
    int pressedState;
};


// ボタンの状態変化を通知するコールバック関数の型を定義
// int buttonIndex: main.ino の fullButtonMaps 配列におけるボタンのインデックス
// bool isPressed: trueなら押された、falseなら離された
typedef void (*ButtonStateCallback)(int buttonIndex, bool isPressed); // ★変更点★

// 長押しコールバック関数の型定義
typedef void (*LongPressCallback)(int pin);

class ButtonManager {
public:
    // コンストラクタ: PhysicalButton の配列を受け取る
    ButtonManager(const ButtonMap* physicalButtons, int numButtons); // ★変更点★

    // ボタンの状態変化コールバックを設定するメソッド
    void setButtonCallback(ButtonStateCallback callback);

    // 長押しコールバックの設定
    void setLongPressCallback(int pin, LongPressCallback callback);

    void begin();
    bool handleInput();

    bool isPress(int buttonIndex);

private:
    const ButtonMap* _physicalButtons; // ★変更点★ 内部で PhysicalButton を参照
    int _numButtons;
    
    // ボタンの内部状態管理変数
    unsigned long* _lastDebounceTime;
    int* _lastButtonState;
    int* _currentButtonState;
    bool* _isLongPressHandled;

    ButtonStateCallback _buttonCallback = nullptr;
    LongPressCallback _longPressCallback = nullptr;
    int _longPressPin = -1; // 長押しコールバックが設定されたピン

    // handleButton は ButtonManager.cpp に移動したため、ここでは宣言しない
};

#define DEBOUNCE_DELAY_MS 10
#define LONG_PRESS_DURATION_MS 1000

#endif // BUTTON_MANAGER_H