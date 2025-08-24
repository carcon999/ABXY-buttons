#ifndef SETTING_H
#define SETTING_H

// XIAO ESP32C6 use
#define ARDUINO_XIAO_ESP32C6

// Enables debug output to the serial port.
#define DEBUG_ENABLED                   (0)

#define DEBUG_BATT                      (0)

#define IDLE_TIMEOUT_ENABLED            (0)

#define DEVICE_NAME         "SF/SNES A,B,X,Y Button"
#define DEVICE_MANUFACTURER "@carcon999" 

// --- port define. ---
#define KEY_A_PIN       GPIO_NUM_0      // F D0/A0/GPIO0/LP_GPIO0
#define KEY_B_PIN       GPIO_NUM_1      // F D1/A1/GPIO1/LP_GPIO1
#define KEY_X_PIN       GPIO_NUM_2      // F D2/A2/GPIO2/LP_GPIO2
#define KEY_Y_PIN       GPIO_NUM_5      // B MTDI/A5/GPIO5/LP_GPIO5/LP_UART_TXD
#define BATT_PIN        GPIO_NUM_6      // B MTCK/A6/GPIO6/LP_GPIO6/LP_I2C_SDA
#define LED_R_PIN       GPIO_NUM_21     // F D3/GPIO21/SDIO_DATA1
#define LED_G_PIN       GPIO_NUM_18     // F D10/MOSI/GPIO18/SDIO_CMD
#define LED_B_PIN       GPIO_NUM_20     // F D9/MISO/GPIO20/SDIO_DATA0
#define KEY_UP_PIN      GPIO_NUM_19     // F D8/SCK/GPIO19/SDIO_CLK
#define KEY_DOWN_PIN    GPIO_NUM_4      // B MTMS/A4/GPIO4/LP_GPIO4/LP_UART_RXD      
#define KEY_CENTER_PIN  GPIO_NUM_7      // B MTDO/GPIO7/LP_GPIO7/LP_I2C_SCL    
#define SSDA            GPIO_NUM_44     // F D4/SDA/GPIO22/SDIO_DATA2
#define SSCL            GPIO_NUM_43     // F D5/SCL/GPIO23/SDIO_DATA3

// Battery Update Interval
#define BATTERY_REPORT_INTERVAL_MS    (60000)
#define LOW_BATTERY_PERCENT           25
#define LOW_BATTERY_SHUTDOWN_PERCENT  0

#define BATT_MAX      4.1               // Fully charged.(100%)
#define BATT_MIN      3.3               // No battery power remaining.(0%)

// Enter deep sleep mode if there is a long period of inactivity.
#define IDLE_TIMEOUT_NO_USE_MS        (180 * 1000L) 

// Timeout period for advertisements when not connected.
#define ADVERTISING_TIMEOUT_MS        (60 * 1000L)

#endif // SETTING_H
