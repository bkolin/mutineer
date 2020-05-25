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
 * The Mutineer leverages the HID capabilities of the modern Arduino 32U4 (ATmega32U4) 
 * and SAM boards, including the Leonardo, Pro Micro, Zero, Due, various Teensy boards, etc.,
 * to present a USB keyboard to the host device. Little to no configuration should be 
 * needed on the host side.
 * 
 * Wiring/Customization: 
 *   - Connect a momentary switch to pin 9 and to ground. This is the keyboard "key".
 *   - Use the built-in LED or connect your own. Special handling for the Pro Micro is in place.
 *   - Change the key sent when the button is pressed by adjusting the body of the sendKey method.
 *   - Control whether keys should be sent automatically (for testing) by setting testMode to true.
 *   - Change the keys sent in test mode by adjsuting the body of the sendTestKeys method.
 *   
 * Usage:
 *   - Connect the Arduino to a host device (Windows, Mac, Linux, Android, etc).
 *   - Answer or dismiss any prompts.
 *   - Configure any needed software on the host (https://mutify.app/ works great on Mac).
 *   - Press the button!
*/

#include <Keyboard.h>

// Control whether a string of test keys are sent every 5 seconds with no user interaction
// or if the real key is sent when the button is pressed.
boolean testMode = false;

// Adjust this section to reflect a connected LED.
#define PRO_MICRO 1
#ifdef PRO_MICRO
  // The only built-in leds on the pro micro are the RX and TX leds, which require a little custom handling:
  //   https://learn.sparkfun.com/tutorials/pro-micro--fio-v3-hookup-guide/example-1-blinkies
  #define LED 17
  #define ON  LOW
  #define OFF HIGH
#else
  #define LED LED_BUILTIN
  #define ON  HIGH
  #define OFF LOW
#endif

#define SWITCH_PIN 9

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(SWITCH_PIN, INPUT_PULLUP);

  digitalWrite(LED, OFF);

  Keyboard.begin();
}

void loop() {
  if (testMode) {
    sendTestKeys();
    delay(5000);
  } else if (digitalRead(SWITCH_PIN) == LOW) { // The switch is pressed
    sendKey();
    digitalWrite(LED, ON);
    delay(1000); // Also serves as a cheap debounce since there is no need to send the key in quick succession.
    digitalWrite(LED, OFF);
  }
}

void sendKey() { // Shift-Command-0 is the default, for compatibility with the Mutify app.
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('0');
  delay(100);
  Keyboard.releaseAll();
}

void sendTestKeys() {
  Keyboard.press('a');
  delay(100);
  Keyboard.releaseAll();      

  Keyboard.press('b');
  delay(100);
  Keyboard.releaseAll();      

  Keyboard.press('c');
  delay(100);
  Keyboard.releaseAll();      

  Keyboard.press('d');
  delay(100);
  Keyboard.releaseAll();      
}
