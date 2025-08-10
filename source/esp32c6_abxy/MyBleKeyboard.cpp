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
    // Initialize the BLE device with the specified device name.
    BLEDevice::init(DEVICE_NAME);

    // Create a new BLE server instance.
    BLEServer* pServer = BLEDevice::createServer();

    // Set BLE authentication requirements for bonding.
    // ESP_LE_AUTH_REQ_SC_MITM_BOND requests Secure Connections, MITM protection, and bonding.
    esp_ble_auth_req_t auth_req = ESP_LE_AUTH_REQ_SC_MITM_BOND;
    esp_ble_gap_set_security_param(ESP_BLE_SM_AUTHEN_REQ_MODE, &auth_req, sizeof(uint8_t));

    // Set IO capabilities. ESP_IO_CAP_NONE means the device has no display or input capabilities,
    // so pairing will typically proceed without user interaction (e.g., no PIN code entry).
    uint8_t io_cap = ESP_IO_CAP_NONE; 
    esp_ble_gap_set_security_param(ESP_BLE_SM_IOCAP_MODE, &io_cap, sizeof(uint8_t)); 

    // Set the initial battery level for the BleKeyboard service.
    // This value will be reported to connected hosts.
    BleKeyboard::setBatteryLevel(init_batt);
    
    Debug.printf("init_batt: %d%%\n", init_batt);

    // Initialize and start the BleKeyboard service on the created BLE server.
    // This adds the HID and Battery services to the server.
    BleKeyboard::begin();

    //Debug.printf("Bonded device num = %d\n", esp_ble_get_bond_device_num());

    // Start BLE advertising to make the device discoverable.
    startAdvertising(pServer);

    Debug.println("BLE Keyboard Ready! Waiting for connection...");
}

void MyBleKeyboard::end(void) {
    BleKeyboard::end();
}

void MyBleKeyboard::startAdvertising(BLEServer* pServer) {
    BLEAdvertising* advertising = pServer->getAdvertising(); 
    if (advertising == nullptr) {
        Debug.println("Advertising object is null, cannot start.");
        return;
    }

    advertising->addServiceUUID(BLEUUID((uint16_t)0x1812)); // HID Service UUID
    advertising->addServiceUUID(BLEUUID((uint16_t)0x180F)); // Battery Service UUID
    advertising->setScanResponse(true); 

    advertising->setAdvertisementType(ADV_TYPE_IND); 
    advertising->setMinPreferred(0x800); // 1280ms
    advertising->setMaxPreferred(0x800); // 1280ms
    
    advertising->start(); 
}

// onConnect callback
void MyBleKeyboard::onConnect(BLEServer* pServer) {
    BleKeyboard::onConnect(pServer); 
    Debug.println("MyBleKeyboard: Client connected!");

    // 状態が変化した場合のみコールバックを呼び出す
    if (_lastConnectedState == false) { // ★修正点★
        _lastConnectedState = true;
        if (_connectionCallback) {
            _connectionCallback(true); // 接続状態を通知
        }
    }
}

// onDisconnect callback
void MyBleKeyboard::onDisconnect(BLEServer* pServer) {
    BleKeyboard::onDisconnect(pServer);
    Debug.println("MyBleKeyboard: Client disconnected! Restarting advertising...");

    // 状態が変化した場合のみコールバックを呼び出す
    if (_lastConnectedState == true) { // ★修正点★
        _lastConnectedState = false;
        if (_connectionCallback) {
            _connectionCallback(false); // 切断状態を通知
        }
    }
}