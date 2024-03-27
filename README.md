# P00016-WeidosESP32-Gateway


## Dependencies
Inside "dependencies" folder you can find all libraries required to compile this code. Those are listed below:

- Crypto chip library version changed to the newer one (v 1.3.7) inside package's libraries folder.
- SD library used is the one from the Weidos MKR1010
- In package's platform.txt ARDUINO extra flag included: build.extra_flags.esp32=-DARDUINO_USB_CDC_ON_BOOT=0 -DARDUINO

**Libraries**
- Crypto chip:          https://github.com/arduino-libraries/ArduinoECCX08  v1.3.7
- Arduino MQTT Client:  https://github.com/256dpi/arduino-mqtt   v2.5.1
- Arduino Bear SSL:     https://github.com/arduino-libraries/ArduinoBearSSL v1.7.3
- ESP Async Web Server: https://github.com/me-no-dev/ESPAsyncWebServer v1.2.3
- Async TCP:            https://github.com/me-no-dev/AsyncTCP   master (ca8ac5f)
- Ring Buffer:          https://github.com/Locoduino/RingBuffer     v1.0.3
- Weidmuller Code Base: https://github.com/WeidmullerSA/WeidmullerCodeBase master (5fd7fb4)
- NTPClient: url=https://github.com/arduino-libraries/NTPClient v3.2.1
- Azure SDK for C library for Arduino: https://github.com/Azure/azure-sdk-for-c-arduino (v1.1.3)
- Arduino SD: Weidos MKR1010 SD library. Do not download directly from Arduino because Wiedos one has a change in pin size (uint8_t -> uint32_t)