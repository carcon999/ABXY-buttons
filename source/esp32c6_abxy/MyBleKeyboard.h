#ifndef MY_BLE_KEYBOARD_H
#define MY_BLE_KEYBOARD_H

#include <BleKeyboard.h> // Base BleKeyboard class
#include "BLEDevice.h"
#include "esp_bt_main.h"
#include "esp_gap_ble_api.h"
#include "esp_bt_defs.h"
#include "DebugSerial.h"  // For debug logging

// コールバック関数の型を定義
// bool isConnected: trueなら接続、falseなら切断
typedef void (*ConnectionCallback)(bool isConnected);

class MyBleKeyboard : public BleKeyboard {
public:
    MyBleKeyboard(std::string deviceName = "ESP32 Keyboard", std::string deviceManufacturer = "Espressif", uint8_t batteryLevel = 100);

    // コールバック関数を設定するメソッド
    void setConnectionCallback(ConnectionCallback callback);

    void begin(uint8_t init_batt);

    void end(void);

    bool isConnected(void);

protected:
    virtual void onConnect(BLEServer* pServer) override;
    virtual void onDisconnect(BLEServer* pServer) override;

private:
    void startAdvertising(BLEServer* pServer);

    ConnectionCallback _connectionCallback = nullptr; // コールバック関数ポインタ
    bool _lastConnectedState = false; // 前回の接続状態を保持する変数 ★追加点★
};

#endif // MY_BLE_KEYBOARD_H