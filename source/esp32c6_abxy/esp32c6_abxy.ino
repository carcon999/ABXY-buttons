#include "Setting.h" // User-defined pin definitions and other constants
#include "MyBleKeyboard.h"
#include "nvs_flash.h"

// Include custom classes
#include "LedController.h" 
#include "BatteryManager.h" 
#include "ButtonManager.h" 
#include "SleepManager.h" 
#include "DebugSerial.h" 

// キーのタイプを定義するenum
enum KeyType {
    KEYBOARD_KEY,
    MEDIA_KEY,
    STRING_TYPE,
    NO_KEY
};

struct KeyMap {
    KeyType keyType;
    union {
        uint8_t key;
        const MediaKeyReport* media;
        const char* string;
    } keyData;
};

struct ButtonMap buttonMaps[] = {
    // pin,           pinModeType,    pressedState
    {KEY_A_PIN,        INPUT,          HIGH}, 
    {KEY_B_PIN,        INPUT,          HIGH}, 
    {KEY_X_PIN,        INPUT,          HIGH}, 
    {KEY_Y_PIN,        INPUT,          HIGH}, 
    {KEY_UP_PIN,       INPUT_PULLUP,   LOW},
    {KEY_DOWN_PIN,     INPUT_PULLUP,   LOW},
    {KEY_CENTER_PIN,   INPUT,          HIGH},
};

const int NUM_ALL_BUTTONS = sizeof(buttonMaps) / sizeof(buttonMaps[0]);

struct KeyMap keyMaps[] = {
    //keyType,         keyData (union)
    {KEYBOARD_KEY,    {.key = KEY_RIGHT_ARROW}},
    {KEYBOARD_KEY,    {.key = KEY_DOWN_ARROW}},
    {KEYBOARD_KEY,    {.key = KEY_UP_ARROW}},
    {KEYBOARD_KEY,    {.key = KEY_LEFT_ARROW}},
    {MEDIA_KEY,       {.media = &KEY_MEDIA_VOLUME_UP}},
    {MEDIA_KEY,       {.media = &KEY_MEDIA_VOLUME_DOWN}},
    {NO_KEY,          {.key = 0}}
    // Example of a STRING_TYPE button (uncomment and add a pin if needed)
    // {NEW_GREETING_PIN,STRING_TYPE,   {.string = "Hello World!"},       INPUT_PULLUP, LOW}
};

#define KEY_A_INDEX             (0)
#define KEY_CENTER_INDEX        (6)

// --- Sleep Wakeup Pins ---
// Define pins that can wake the ESP32 from Deep Sleep.
const int wakeupPins[] = {
    KEY_A_PIN,
    KEY_B_PIN,
    KEY_X_PIN,
    KEY_Y_PIN
    // KEY_CENTER_PIN could be added here if it's also a wakeup source
};
const int NUM_WAKEUP_PINS = sizeof(wakeupPins) / sizeof(wakeupPins[0]);

// --- Global Class Pointers (initialized in setup() based on dependencies) ---
MyBleKeyboard bleKeyboard(DEVICE_NAME, DEVICE_MANUFACTURER, 80); 
ButtonManager buttonManager(buttonMaps, NUM_ALL_BUTTONS);
SleepManager sleepManager(wakeupPins, NUM_WAKEUP_PINS);
LedController led(LED_R_PIN, LED_G_PIN, LED_B_PIN, LED_BUILTIN);
BatteryManager batteryManager(BATT_PIN, BATT_MAX, BATT_MIN);

static unsigned long mDisconnectedTime; 

// --- Function Prototypes ---
void checkAdvertisingTimeout(void);
void handleConnectionStatusChange(bool isConnected);
void enterDeepSleep(void); // Centralized function to enter deep sleep
void onBatteryLevelChange(uint8_t newLevel);
void onButtonStateChange(int index, bool isPressed);
void onButtonCenterLongPress(int pin);
void factory_reset(void);

void updateLedStatus(void){
    bool isConnect = bleKeyboard.isConnected();
    bool isLowBatt = batteryManager.getPercent() <= LOW_BATTERY_PERCENT;

    // 接続中
    if(bleKeyboard.isConnected()){
        if(isLowBatt){
            led.setColor(COLOR_GREEN, 1000);
        }else{
            led.setColor(COLOR_GREEN);
        }
    }
    // 非接続
    else{
        if(isLowBatt){
            led.setColor(COLOR_RED, 1000);
        }else{
            led.setColor(COLOR_RED);
        }
    }
}

// ==============================================================================
// === Arduino Setup Function ===================================================
// ==============================================================================
void setup() {
    // 1. Initialize LED controller and set initial state (e.g., red for not connected)
    led.begin(); 
    led.setColor(COLOR_RED);

    // 2. Initialize Debug Serial (only active if DEBUG_ENABLED is defined)
    Debug.begin(115200);
    Debug.println("Starting BLE Keyboard");

    sleepManager.setupWakeup(); 

    // ボタン開始
    buttonManager.begin(); 

    // 工場出荷初期化モード
    if(buttonManager.isPress(KEY_CENTER_INDEX)){
        Debug.println("Press StartUp Center. ");
        factory_reset();
        while(1){};
    }

    // コールバック関数を登録
    bleKeyboard.setConnectionCallback(handleConnectionStatusChange);


    batteryManager.setBatteryLevelCallback(onBatteryLevelChange);
    batteryManager.begin();
    int initialBatteryLevel = batteryManager.getPercent();
    
    // Debug.printf("initialBatteryLevel: %d%%\n", initialBatteryLevel);
    // delay(1000); // Short delay to prevent watchdog timer issues and yield to other tasks

    // initialBatteryLevel = batteryManager.getPercent();
    Debug.printf("initialBatteryLevel: %d%%\n", initialBatteryLevel);

    bleKeyboard.begin(initialBatteryLevel);
    mDisconnectedTime = millis();

    buttonManager.setButtonCallback(onButtonStateChange);
    buttonManager.setLongPressCallback(KEY_CENTER_PIN, onButtonCenterLongPress);

}

// ==============================================================================
// === Arduino Loop Function ====================================================
// ==============================================================================
void loop() {
    led.update();

    // Handle button inputs (debouncing, key/media/string sending, long press detection)
    bool is_input = buttonManager.handleInput(); 

#if IDLE_TIMEOUT_ENABLED
    // Manage idle timeout for deep sleep transition
    static unsigned long lastActivityTime = 0; 
    unsigned long now = millis();

    // Reset activity timer if there's any input or if it's the first loop
    if (lastActivityTime == 0 || is_input) { 
        lastActivityTime = now;
    }

    // If device has been idle for too long, enter deep sleep
    if (now - lastActivityTime > IDLE_TIMEOUT_NO_USE_MS) {
        Debug.println("It hasn't been used for a while, entering Deep Sleep...");
        enterDeepSleep(); // Centralized deep sleep function
    }
#endif

    // Avoid prolonged periods of disconnection. Reduce battery consumption.
    checkAdvertisingTimeout();

    // Update and report battery level via BatteryManager
    batteryManager.handleBatteryUpdate();

    delay(1); // Short delay to prevent watchdog timer issues and yield to other tasks
}

// ==============================================================================
// === Helper Functions =========================================================
// ==============================================================================
void checkAdvertisingTimeout(void){
    if(mDisconnectedTime != 0){
        if(millis() - mDisconnectedTime > ADVERTISING_TIMEOUT_MS){
            Debug.println("Unable to connect, entering Deep Sleep...");
            enterDeepSleep();
        }
    }
}

// 接続状態が変化したときに呼び出されるコールバック関数
void handleConnectionStatusChange(bool isConnected) {
    if (isConnected) {
        mDisconnectedTime = 0;  // clear
        Debug.println("Callback: BLE connected! Setting LED to green.");
    } else {
        mDisconnectedTime = millis();
        Debug.println("Callback: BLE disconnected! Starting red blinking.");
    }

    updateLedStatus();
}

void onBatteryLevelChange(uint8_t newLevel) {

    bleKeyboard.setBatteryLevel(newLevel);

    if (newLevel == 0) {
        Debug.println("Battery voltage is low, entering Deep Sleep...");
        enterDeepSleep(); // Centralized deep sleep function
    }
    else if (newLevel <= LOW_BATTERY_PERCENT) {
        Debug.println("Battery voltage is low.");
        updateLedStatus();
    }
}

// ボタンの状態変化を処理するコールバック関数
void onButtonStateChange(int index, bool isPressed) { // ★追加点★
    if (!bleKeyboard.isConnected()) {
        return;
    }

    KeyMap& map = keyMaps[index];

    if (isPressed) {
        switch (map.keyType) {
            case KEYBOARD_KEY:
                bleKeyboard.press(map.keyData.key);
                break;
            case MEDIA_KEY:
                bleKeyboard.press(*(map.keyData.media));
                break;
            case STRING_TYPE:
                bleKeyboard.print(map.keyData.string);
                break;
            default:
                break;
        }
    } else { // Released
        switch (map.keyType) {
            case KEYBOARD_KEY:
                bleKeyboard.release(map.keyData.key);
                break;
            case MEDIA_KEY:
                bleKeyboard.release(*(map.keyData.media));
                break;
            case STRING_TYPE:
                // String type doesn't have a release action
                break;
            default:
                break;
        }
    }
}

/**
 * @brief Callback function for center button long press.
 * This function is called by ButtonManager when the center button is long-pressed.
 * @param pin The pin number of the button that triggered the event (KEY_CENTER_PIN).
 */
void onButtonCenterLongPress(int pin) {
    Debug.println("KEY_CENTER long-pressed! Entering Deep Sleep...");
    enterDeepSleep(); // Centralized deep sleep function
}

/**
 * @brief Centralized function to prepare for and enter Deep Sleep mode.
 * This ensures consistent behavior (e.g., LED state) before sleeping,
 * regardless of the trigger source (idle, low battery, button press).
 */
void enterDeepSleep(void){
    // Set all LEDs to OFF state before entering sleep
    led.setColor(COLOR_BLACK); // Turn off RGB LED
    led.setBuiltinLed(true);   // Turn off built-in LED (assuming HIGH is OFF)
    bleKeyboard.end();
    
    // Enter deep sleep via SleepManager
    sleepManager.enterDeepSleep(); 
}

void factory_reset(void) {
    esp_err_t ret;

    led.setColor(COLOR_RED, 100);

    while(buttonManager.isPress(KEY_CENTER_INDEX)){
        led.update();
    }

    buttonManager.setLongPressCallback(KEY_CENTER_PIN, onButtonCenterLongPress);
    Debug.println("Wait Press A");
    while(!buttonManager.isPress(KEY_A_INDEX) || buttonManager.isPress(KEY_CENTER_INDEX)){
        led.update();
        buttonManager.handleInput();
    }

    led.setColor(COLOR_YELLOW);

    // Bluetooth スタック停止
    NimBLEDevice::deinit();

    // NVS全体を消去
    ret = nvs_flash_erase();
    if (ret != ESP_OK) {
        Debug.printf("NVS erase failed: %s", esp_err_to_name(ret));
        return;
    }

    // NVSを再初期化
    ret = nvs_flash_init();
    if (ret != ESP_OK) {
        Debug.printf("NVS init failed: %s", esp_err_to_name(ret));
        return;
    }

    Debug.println("NVS erased and re-initialized. Restarting device...");

    delay(1000);

    // ESP再起動
    esp_restart();
}