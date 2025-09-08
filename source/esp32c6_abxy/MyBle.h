#ifndef MY_BLE_H
#define MY_BLE_H

#include "Setting.h"

#if IS_GAME_CONTROLLER
#include <BleGamepad.h> // https://github.com/lemmingDev/ESP32-BLE-Gamepad
#else
#include <NimBleKeyboard.h> // Base BleKeyboard class
#endif

#include "DebugSerial.h"  // For debug logging

#if IS_GAME_CONTROLLER
// コールバック関数の型を定義
class MyBle : public BleGamepad {
public:
    MyBle(std::string deviceName = "ESP32 Keyboard", std::string deviceManufacturer = "Espressif", uint8_t batteryLevel = 100);
    
    void begin(uint8_t init_batt);

    void end(void);

    void stop(void);

 protected:
  virtual void onStarted(NimBLEServer *pServer) override;
};
#else
// コールバック関数の型を定義
// bool isConnected: trueなら接続、falseなら切断
typedef void (*ConnectionCallback)(bool isConnected);

class MyBle : public BleKeyboard {
public:
    MyBle(std::string deviceName = "ESP32 Keyboard", std::string deviceManufacturer = "Espressif", uint8_t batteryLevel = 100);

    // コールバック関数を設定するメソッド
    void setConnectionCallback(ConnectionCallback callback);
    
    void begin(uint8_t init_batt);

    void end(void);

    void stop(void);

    bool isConnected(void);

 protected:
  virtual void onStarted(NimBLEServer *pServer) override;
  virtual void onConnect(NimBLEServer* pServer, NimBLEConnInfo &connInfo) override;
  virtual void onDisconnect(NimBLEServer* pServer, NimBLEConnInfo &connInfo, int reason) override;

private:

    ConnectionCallback _connectionCallback = nullptr; // コールバック関数ポインタ
    bool _lastConnectedState = false; // 前回の接続状態を保持する変数 ★追加点★
};
#endif

#endif // MY_BLE_H