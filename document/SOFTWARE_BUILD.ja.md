## ビルド方法
ESP32やBLEのライブラリは更新が頻繁にあるので、Versionが異なるとエラーが発生することがあります。異なるVersionを利用する際には注意してください。私は以下のものを利用しています。
- [Arduino IDE 2.3.6](https://www.arduino.cc/en/software/)
- ボードマネージャー [esp32 by Espressif Systems 3.2.1](https://github.com/espressif/arduino-esp32)
- BLEライブラリ [ESP32-BLE-Keyboard](https://github.com/carcon999/ESP32-BLE-Keyboard)<br>
 上記は、[XIAO ESP32C6のBLEでログインボタンを作る](https://qiita.com/nori-dev-akg/items/249988fd87bd9a589bde)の修正を利用させていただきました。

### 前提条件
Arduino IDEインストールと、XIAO ESP32C6のボードが利用できている状態とします。
もし、はじめて利用する場合には、[Seeed Studioの公式ブログ](https://wiki.seeedstudio.com/xiao_esp32c6_getting_started/)を参考に構築してください。

### ライブラリのインストール
[本家のライブラリ](https://github.com/T-vK/ESP32-BLE-Keyboard)は、残念ながらビルドエラーが発生してしまうので、[Forkしたこちらの修正版](https://github.com/carcon999/ESP32-BLE-Keyboard)をダウンロードして、Arduinoライブラリに追加します。

### Arduno IDEの設定
「メニュー」の「ツール」で下記の設定に合わせる。
| 項目名 | 設定内容 | 備考 |
|--------|--------|--------|
| ボード | XIAO_ESP32C6 | - |
| ポート | COM X | お使いの環境に合わせて設定 |
| CPU Frequency | 80MHz(WiFi) | 160MHzでも動作可能 |
| Core Debug Level | None | - |
| Erase All Flash Before Sketch Upload | Enabled | ボンド情報はクリアされる |
| Flash Frequency | 80MHz | - |
| Flash Mode | QIO | - |
| Flash Size | 4MB(32Mb) | - |
| JTAG Adapter | Disabled | - |
| Partition Scheme | No OTA (2MB APP/2MB SPIFFS) | 現在OTAは利用しない |
| Upload Speed | 921600 | - |
| Zigbee Mode | Disabled | - |

![分解イメージ画像](../image/SOFTWARE_BUILD/arduino_tool.png)

### ビルド
設計資料にある[ソースコード](./source/esp32c6_abxy/)をダウンロードし、Arduino IDEでesp32c6_abxy.inoを開き、ビルドします。もし、ビルドエラーが発生する場合には、Versionの違いに注意してください。とくにボードマネージャーのVersionの違いに注意してください。<br>
※ESP32は頻繁に更新されるため違いが発生しやすいです。

### 書き込み
USB経由で書き込みます。もし、うまく書き込みができない場合やシリアルポートが見えない場合には、XIAO ESP32C6をBootLoaderモードで起動させます。手順は、Bootボタンを押したまま、ResetボタンをON->OFFします。Bootボタンは、USB端子の左側にあり、Resetボタンは端子の右側です。非常に小さいスイッチなのでうまく操作してください。<br>
もし、ケースに入れたままの状態の場合は、4か所のねじを外して作業する必要があります。

![分解イメージ画像](../image/SOFTWARE_BUILD/Boot_Reset.jpg)

[戻る](../README.ja.md)