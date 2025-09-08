#include "MyBle.h"
#if IS_GAME_CONTROLLER
#include "NimBLEDevice.h"
#endif
#if IS_GAME_CONTROLLER
BleGamepadConfiguration gamepadConfig;
#endif

MyBle::MyBle(std::string deviceName, std::string deviceManufacturer, uint8_t batteryLevel)
#if IS_GAME_CONTROLLER
    : BleGamepad(deviceName, deviceManufacturer, batteryLevel) {
#else 
    : BleKeyboard(deviceName, deviceManufacturer, batteryLevel) {
#endif
}

#if !IS_GAME_CONTROLLER
// コールバック関数を設定するメソッドの実装
void MyBle::setConnectionCallback(ConnectionCallback callback) {
    _connectionCallback = callback;
}

bool MyBle::isConnected(void) {
    return _lastConnectedState;
}
#endif

void MyBle::begin(uint8_t init_batt) {
#if IS_GAME_CONTROLLER
    // Configuration を設定
    gamepadConfig.setButtonCount(7);       // ボタン数
    gamepadConfig.setHatSwitchCount(0);     // ハットスイッチ
    // 軸 (X, Y, RX, RY) 全無効
    gamepadConfig.setWhichAxes(false, false, false, false, false, false, false, false);

    // 特殊ボタン 全無効
    gamepadConfig.setWhichSpecialButtons(false, false, false, false, false, false, false, false);

    //gamepadConfig.setVid(0x054C);  // Sony
    //gamepadConfig.setPid(0x05C4);  // DualShock 4

    gamepadConfig.setAutoReport(true);
    gamepadConfig.setControllerType(CONTROLLER_TYPE_GAMEPAD); // CONTROLLER_TYPE_JOYSTICK, CONTROLLER_TYPE_GAMEPAD (DEFAULT), CONTROLLER_TYPE_MULTI_AXIS

    BleGamepad::setBatteryLevel(init_batt);
    BleGamepad::begin();
#else
    BleKeyboard::setBatteryLevel(init_batt);
    BleKeyboard::begin();
#endif
    Debug.println("BLE Ready! Waiting for connection...");
}

void MyBle::end(void) {
#if IS_GAME_CONTROLLER
    BleGamepad::end();
#else
    BleKeyboard::end();
#endif
}

void MyBle::stop(void){
    // Bluetooth スタック停止
    NimBLEDevice::deinit();
}

void MyBle::onStarted(NimBLEServer *pServer)
{
#if IS_GAME_CONTROLLER
    BleGamepad::onStarted(pServer);
#else
    BleKeyboard::onStarted(pServer);
#endif
    Debug.println("MyBle: onStarted");
    NimBLEAdvertising* pAdvertising = pServer->getAdvertising();
    pAdvertising->setMinInterval(0x0020); // 20ms
    pAdvertising->setMaxInterval(0x0030); // 30ms
}

#if !IS_GAME_CONTROLLER
void MyBle::onConnect(NimBLEServer* pServer, NimBLEConnInfo &connInfo)
{
    BleKeyboard::onConnect(pServer, connInfo);
    Debug.println("MyBle: Client connected!");

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

void MyBle::onDisconnect(NimBLEServer* pServer, NimBLEConnInfo &connInfo, int reason)
{
    BleKeyboard::onDisconnect(pServer, connInfo, reason);
    Debug.println("MyBle: Client disconnected! Restarting advertising...");

    // 状態が変化した場合のみコールバックを呼び出す
    if (_lastConnectedState == true) { // ★修正点★
        _lastConnectedState = false;
        if (_connectionCallback) {
            _connectionCallback(false); // 切断状態を通知
        }
    }
}
#endif