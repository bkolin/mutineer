/*
MIT License

Copyright (c) 2020 Benjamin Kolin

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


/*
 * The Mutineer
 * 
 * The Mutineer is a one-key keyboard implementation that is intended to be used with software
 * on a host computer or device to quickly mute the microphone using a hardware button. It is
 * also suitable for any other hardware button implementation that can be mapped to a hotkey
 * combination with minimal editing.
 * 
 * The Mutineer leverages the Bluetooth LE stack of the ESP32 microcontroller. Aside from
 * pairing as a Bluetooth keyboard there should be no configuration on the host side.
 * 
 * Wiring/Customization: 
 *   - Install the BLE HID library for ESP32 from https://github.com/T-vK/ESP32-BLE-Keyboard
 *   - Connect a momentary switch to pin 15 and to ground. This is the keyboard "key".
 *   - Use the built-in LED on GPIO2 or connect your own.
 *   - Change the key sent when the button is pressed by adjusting the body of the sendKey method.
 *   - Control whether keys should be sent automatically (for testing) by setting testMode to true.
 *   - Change the keys sent in test mode by adjusting the body of the sendTestKeys method.
 *   
 * Usage:
 *   - Power up the ESP32 and pair with a host device (Windows, Mac, Linux, Android, etc).
 *   - Answer or dismiss any prompts.
 *   - Configure any needed software on the host (https://mutify.app/ works great on Mac).
 *   - Press the button!
*/


// BLE HID for ESP32 from https://github.com/T-vK/ESP32-BLE-Keyboard
#include <BleKeyboard.h>

// Control whether a string of test keys are sent every 5 seconds with no user interaction
// or if the real key is sent when the button is pressed.
boolean testMode = false;

#define LED 18

#define SWITCH_PIN 15

// name, manufacturer, battery_percent
BleKeyboard bleKeyboard("The Mutineer", "TigerMonsterIndustries", 100);

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(SWITCH_PIN, INPUT_PULLUP);

  bleKeyboard.begin();
}

void loop() {
  if (bleKeyboard.isConnected()) {
    if (testMode) {
      sendTestKeys();
      delay(5000);
    } else if (digitalRead(SWITCH_PIN) == LOW) { // The switch is pressed
      sendKey();
      digitalWrite(LED, HIGH);
      delay(1000); // Also serves as a cheap debounce since there is no need to send the key in quick succession.
      digitalWrite(LED, LOW);
    }
  }
}

void sendKey() { // Shift-Command-0 is the default, for compatibility with the Mutify app.
  bleKeyboard.press(KEY_LEFT_SHIFT);
  bleKeyboard.press(KEY_LEFT_GUI);
  bleKeyboard.press('0');
  delay(100);
  bleKeyboard.releaseAll();
}

void sendTestKeys() {
  bleKeyboard.press('a');
  delay(100);
  bleKeyboard.releaseAll();      

  bleKeyboard.press('b');
  delay(100);
  bleKeyboard.releaseAll();      

  bleKeyboard.press('c');
  delay(100);
  bleKeyboard.releaseAll();      

  bleKeyboard.press('d');
  delay(100);
  bleKeyboard.releaseAll();      
}
