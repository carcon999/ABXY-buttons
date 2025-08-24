#include "MyBleKeyboard.h"

MyBleKeyboard::MyBleKeyboard(std::string deviceName, std::string deviceManufacturer, uint8_t batteryLevel)
    : BleKeyboard(deviceName, deviceManufacturer, batteryLevel) {
}

// コールバック関数を設定するメソッドの実装
void MyBleKeyboard::setConnectionCallback(ConnectionCallback callback) {
    _connectionCallback = callback;
}

bool MyBleKeyboard::isConnected(void) {
    return _lastConnectedState;
}

void MyBleKeyboard::begin(uint8_t init_batt) {

    BleKeyboard::setBatteryLevel(init_batt);
    BleKeyboard::begin();

    Debug.println("BLE Keyboard Ready! Waiting for connection...");
}

void MyBleKeyboard::end(void) {
    BleKeyboard::end();
}

void MyBleKeyboard::onStarted(NimBLEServer *pServer)
{
    BleKeyboard::onStarted(pServer);
    Debug.println("MyBleKeyboard: onStarted");

    NimBLEAdvertising* pAdvertising = pServer->getAdvertising();
    pAdvertising->setMinInterval(0x0020); // 20ms
    pAdvertising->setMaxInterval(0x0030); // 30ms
}

void MyBleKeyboard::onConnect(NimBLEServer* pServer, NimBLEConnInfo &connInfo)
{
    BleKeyboard::onConnect(pServer, connInfo);
    Debug.println("MyBleKeyboard: Client connected!");

    // 接続相手の OTA アドレス（MAC アドレス）を取得
    NimBLEAddress peerAddr = connInfo.getAddress();
    Debug.print("Connected to: ");
    Debug.println(peerAddr.toString().c_str());

    // 接続ハンドルを取得
    uint16_t connHandle = connInfo.getConnHandle();

    // 接続パラメータを変更
    uint16_t minInterval = 6;   // 7.5ms * 6 = 45ms
    uint16_t maxInterval = 12;  // 7.5ms * 12 = 90ms
    uint16_t latency     = 0;
    uint16_t timeout     = 200; // supervision timeout

    // Arduino版ではこの形で呼ぶ
    pServer->updateConnParams(connHandle, minInterval, maxInterval, latency, timeout);

    // 状態が変化した場合のみコールバックを呼び出す
    if (_lastConnectedState == false) { // ★修正点★
        _lastConnectedState = true;
        if (_connectionCallback) {
            _connectionCallback(true); // 接続状態を通知
        }
    }
}

void MyBleKeyboard::onDisconnect(NimBLEServer* pServer, NimBLEConnInfo &connInfo, int reason)
{
    BleKeyboard::onDisconnect(pServer, connInfo, reason);
    Debug.println("MyBleKeyboard: Client disconnected! Restarting advertising...");

    // 状態が変化した場合のみコールバックを呼び出す
    if (_lastConnectedState == true) { // ★修正点★
        _lastConnectedState = false;
        if (_connectionCallback) {
            _connectionCallback(false); // 切断状態を通知
        }
    }
}