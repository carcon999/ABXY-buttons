#include "ButtonManager.h"

// コンストラクタ: PhysicalButton の配列を受け取る
ButtonManager::ButtonManager(const ButtonMap* physicalButtons, int numButtons)
    : _physicalButtons(physicalButtons), _numButtons(numButtons) {
    _lastDebounceTime = new unsigned long[_numButtons];
    _lastButtonState = new int[_numButtons];
    _currentButtonState = new int[_numButtons];
    _isLongPressHandled = new bool[_numButtons];
}

// コールバック関数を設定するメソッド
void ButtonManager::setButtonCallback(ButtonStateCallback callback) {
    _buttonCallback = callback;
}

void ButtonManager::setLongPressCallback(int pin, LongPressCallback callback) {
    _longPressPin = pin;
    _longPressCallback = callback;
}

void ButtonManager::begin() {
    for (int i = 0; i < _numButtons; i++) {
        pinMode(_physicalButtons[i].pin, _physicalButtons[i].pinModeType);
        _lastDebounceTime[i] = 0;
        _lastButtonState[i] = (_physicalButtons[i].pressedState == HIGH) ? LOW : HIGH;
        _currentButtonState[i] = _lastButtonState[i];
        _isLongPressHandled[i] = false;
    }
}

bool ButtonManager::isPress(int buttonIndex){
    int reading = digitalRead(_physicalButtons[buttonIndex].pin);

    return (reading == _physicalButtons[buttonIndex].pressedState);
}

bool ButtonManager::handleInput() {
    bool inputDetected = false;
    unsigned long currentMillis = millis();

    for (int i = 0; i < _numButtons; i++) {
        int reading = digitalRead(_physicalButtons[i].pin); // ★変更点★ PhysicalButton を参照

        if (reading != _lastButtonState[i]) {
            _lastDebounceTime[i] = currentMillis;
        }

        if ((currentMillis - _lastDebounceTime[i]) > DEBOUNCE_DELAY_MS) {
            if (reading != _currentButtonState[i]) {
                _currentButtonState[i] = reading;

                if (_currentButtonState[i] == _physicalButtons[i].pressedState) { // ★変更点★ PhysicalButton を参照
                    Debug.printf("Button %d pressed\n", _physicalButtons[i].pin); // ★変更点★ keyType は ButtonManager が知らないのでログから削除
                    if (_buttonCallback != nullptr) {
                        _buttonCallback(i, true); // ★変更点★ インデックスを渡す
                    }
                    inputDetected = true;
                } else {
                    Debug.printf("Button %d released\n", _physicalButtons[i].pin); // ★変更点★
                    // ButtonManager は keyType を知らないので、STRING_TYPE の特別な処理はコールバック側で行う
                    if (_buttonCallback != nullptr) {
                        _buttonCallback(i, false); // ★変更点★ インデックスを渡す
                    }
                    inputDetected = true;
                    _isLongPressHandled[i] = false;
                }
            }
        }
        _lastButtonState[i] = reading;
    }

    if (_longPressPin != -1 && _longPressCallback != nullptr) {
        for (int i = 0; i < _numButtons; i++) {
            if (_physicalButtons[i].pin == _longPressPin && _currentButtonState[i] == _physicalButtons[i].pressedState) { // ★変更点★ PhysicalButton を参照
                if (!_isLongPressHandled[i] && (currentMillis - _lastDebounceTime[i]) > LONG_PRESS_DURATION_MS) {
                    _longPressCallback(_longPressPin);
                    _isLongPressHandled[i] = true;
                    inputDetected = true;
                }
            }
        }
    }
    return inputDetected;
}