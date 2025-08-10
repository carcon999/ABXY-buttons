## Build Instructions

ESP32 and BLE libraries are frequently updated, so using a different version may cause build errors.  
Please be careful when using versions other than the ones listed below, which I have confirmed to work:

- [Arduino IDE 2.3.6](https://www.arduino.cc/en/software/)
- Board Manager: [esp32 by Espressif Systems 3.2.1](https://github.com/espressif/arduino-esp32)
- BLE Library: [ESP32-BLE-Keyboard](https://github.com/carcon999/ESP32-BLE-Keyboard)  
  This is a modified version based on “[Creating a login button with XIAO ESP32C6 BLE](https://qiita.com/nori-dev-akg/items/249988fd87bd9a589bde)”.

### Prerequisites
Arduino IDE must be installed, and the XIAO ESP32C6 board must already be set up.  
If you are using it for the first time, please follow the [official Seeed Studio guide](https://wiki.seeedstudio.com/xiao_esp32c6_getting_started/).

### Installing the Library
The [original library](https://github.com/T-vK/ESP32-BLE-Keyboard) unfortunately causes build errors, so please download and add [this forked and fixed version](https://github.com/carcon999/ESP32-BLE-Keyboard) to your Arduino libraries.

### Arduino IDE Settings
In the **Tools** menu, set the following:

| Setting Name | Value | Notes |
|--------------|-------|-------|
| Board | XIAO_ESP32C6 | - |
| Port | COM X | Adjust according to your environment |
| CPU Frequency | 80MHz (WiFi) | Works at 160MHz as well |
| Core Debug Level | None | - |
| Erase All Flash Before Sketch Upload | Enabled | Clears bonding information |
| Flash Frequency | 80MHz | - |
| Flash Mode | QIO | - |
| Flash Size | 4MB (32Mb) | - |
| JTAG Adapter | Disabled | - |
| Partition Scheme | No OTA (2MB APP / 2MB SPIFFS) | OTA not used currently |
| Upload Speed | 921600 | - |
| Zigbee Mode | Disabled | - |

![Arduino Tools Settings](../image/SOFTWARE_BUILD/arduino_tool.png)

### Build
Download the [source code](./source/esp32c6_abxy/) from the design documents,  
open `esp32c6_abxy.ino` in Arduino IDE, and build.  
If a build error occurs, check for version mismatches — especially in the Board Manager version.  
*Note: ESP32 is updated frequently, so version mismatches are common.*

### Upload
Upload via USB.  
If uploading fails or the serial port is not visible, start the XIAO ESP32C6 in Bootloader mode:  
Hold down the **Boot** button and press **Reset** (ON → OFF).  
The Boot button is to the left of the USB port, and the Reset button is to the right.  
These are very small switches, so handle them carefully.  

If the device is still in its case, you will need to remove the four screws before performing this procedure.

![Boot and Reset Buttons](../image/SOFTWARE_BUILD/Boot_Reset.jpg)

[Back](../README.en.md)
