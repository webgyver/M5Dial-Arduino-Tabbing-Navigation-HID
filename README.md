# M5Dial Arduino Tabbing Navigation HID

This Arduino project utilizes the [M5Stack Dial](https://shop.m5stack.com/products/m5stack-dial-esp32-s3-smart-rotary-knob-w-1-28-round-touch-screen) as a HID (Human Interface Device) Keyboard. It is designed for the specific use case of [tabbing navigation](https://en.wikipedia.org/wiki/Tabbing_navigation), offering an exclusive hardware solution for this purpose.

## Key Features

- **Right Rotation of Encoder:** Sends a `Tab` keystroke.
- **Left Rotation of Encoder:** Sends `Shift + Tab`.
- **Touching the Display:** Sends a `Space`.

## BLE Support

To use BLE (Bluetooth Low Energy) instead of USB, uncomment the following line in the first line of the code, install [ESP32 BLE Keyboard](https://github.com/T-vK/ESP32-BLE-Keyboard#installation), and activate NimBLE.

```cpp
// #define USE_BLE_INSTEAD_OF_USB 1
```

## Dependencies

This project relies on the following libraries:

- Main Library: [M5Dial](https://docs.m5stack.com/en/quick_start/m5dial/arduino)
- For USB Connection: [USBHID](https://www.arduino.cc/reference/en/libraries/usbhid/)

### For BLE Version

- BLE Keyboard: [ESP32 BLE Keyboard](https://github.com/T-vK/ESP32-BLE-Keyboard#installation)
- (faster) BLE Framework: [NimBLE-Arduino](https://www.arduino.cc/reference/en/libraries/nimble-arduino/)

## Inspirations

- https://github.com/aadfPT/m5dial-media-controller
