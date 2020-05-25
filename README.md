# mutineer
A real-world button to mute and unmute all your video conference apps, implemented as a one-key keyboard.

USB and Bluetooth implementations are both provided. 

The USB implementation will run on any Arduino with HID capabilities, including any of the 32U4 (ATmega32U4) and SAM boards. This includes the Leonardo, Pro Micro, Zero, Due, various Teensy boards, etc.

The Bluetooth implementation was built for the ESP32.

These sketches are easy to customize. It is trivial to change which keys are sent, which pins are used for switches and LEDs, add additional switches to make it a multi-key keyboard, and more.
