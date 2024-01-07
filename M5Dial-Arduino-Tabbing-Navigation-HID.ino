/*

  Inspired by https://github.com/aadfPT/m5dial-media-controller

  To use BLE instead of USB remove the following comment, install 
  https://github.com/T-vK/ESP32-BLE-Keyboard#installation and
  activate NimBLE.

*/
#define USE_BLE_INSTEAD_OF_USB 1

#include <M5Dial.h>

#ifdef USE_BLE_INSTEAD_OF_USB
  #include <BleKeyboard.h>
  BleKeyboard keyboard("Tabbigator");
#else
  #include <USB.h>
  #include <USBHIDKeyboard.h>
  USBHIDKeyboard keyboard;
#endif


unsigned int SLEEP_AFTER_SECONDS = 10;

int prev_encoder_pos = 0;
unsigned long last_interaction = 0;


void setup() {
  Serial.begin(115200);
  Serial.println("setup");

  auto cfg = M5.config();
  M5Dial.begin(cfg, true, false);

  M5Dial.Display.setBrightness(10);

  auto size = M5Dial.Display.width();
  M5Dial.Display.fillCircle(size / 2, size / 2, size / 3, BLUE);

  keyboard.begin();
  #ifndef USE_BLE_INSTEAD_OF_USB
    USB.begin();
  #endif

  last_interaction = millis();
}


void loop() {
  M5Dial.update();  

  // on touch -> send space
  if (M5Dial.Touch.getDetail().state == m5::touch_state_t::touch_begin) {
    Serial.println("on_touch");
    M5Dial.Speaker.tone(6000, 20);
    keyboard.write(0x20); // ASCII for spacebar
    last_interaction = millis();
    M5Dial.Display.wakeup();
  }

  // on rotate encoder -> send tab, shift+tab
  int encoder_pos = M5Dial.Encoder.read();
  int encoder_pos_diff = encoder_pos - prev_encoder_pos;
  prev_encoder_pos = encoder_pos;

  if (encoder_pos_diff > 0) {
    Serial.println("on_rotated: right");
    M5Dial.Speaker.tone(4000, 20);
    keyboard.write(KEY_TAB);
    last_interaction = millis();
    M5Dial.Display.wakeup();
  } else if (encoder_pos_diff < 0) {
    Serial.println("on_rotated: left");
    M5Dial.Speaker.tone(10000, 20);
    keyboard.press(KEY_LEFT_SHIFT);
    keyboard.press(KEY_TAB);
    keyboard.releaseAll();
    last_interaction = millis();
    M5Dial.Display.wakeup();
  }

  if (SLEEP_AFTER_SECONDS != 0 && millis() - last_interaction >= SLEEP_AFTER_SECONDS * 1000) {
    M5Dial.Display.sleep();
  }
}
