#ifndef MY_BLE_KEYBOARD_H
#define MY_BLE_KEYBOARD_H

#include <NimBleKeyboard.h> // Base BleKeyboard class

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
  virtual void onStarted(NimBLEServer *pServer) override;
  virtual void onConnect(NimBLEServer* pServer, NimBLEConnInfo &connInfo) override;
  virtual void onDisconnect(NimBLEServer* pServer, NimBLEConnInfo &connInfo, int reason) override;

private:

    ConnectionCallback _connectionCallback = nullptr; // コールバック関数ポインタ
    bool _lastConnectedState = false; // 前回の接続状態を保持する変数 ★追加点★
};

#endif // MY_BLE_KEYBOARD_H