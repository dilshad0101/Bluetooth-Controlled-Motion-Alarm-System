# Bluetooth-Controlled-Motion-Alarm-System
An Arduino-based motion detection alarm system integrated with Bluetooth for remote control.

# Project Overview
This project implements a Motion Detector Alarm System using an Arduino Uno, PIR sensor, LED, Buzzer, and HC-05 Bluetooth module. It provides both visual and audible alerts when motion is detected and can be controlled remotely via Bluetooth. The system includes a cooldown mechanism to avoid repeated triggering.

# Objectives
-Detect motion using a PIR sensor.
-Provide real-time alerts with a buzzer and LED.
-Enable remote control via Bluetooth (HC-05).
-Implement a cooldown mechanism to reduce false alarms.
-Allow status monitoring through Serial communication.

# Components

| Component                | Function                               |
|--------------------------|----------------------------------------|
| Arduino Uno              | Microcontroller                        |
| PIR Sensor               | Detects motion                         |
| HC-05 Bluetooth Module   | Wireless communication                 |
| Buzzer                   | Audible alarm                          |
| LED                      | Visual alarm                           |
| Power Supply             | Powers the system                      |
| Breadboard, Resistors    | Circuit connections                    |

# Working
 Activation: When the alarm system is activated, the PIR sensor constantly scans for motion. If motion is
detected within its 110-degree detection range, the system triggers the buzzer and turns on the LED,
signaling that motion has been detected and the alarm is active.

 User Control: The system is equipped with a Bluetooth interface that allows the user to turn off the alarm
remotely. Using the mobile phone, the user sends a signal to the Bluetooth module (via the HC-05), which is
received by the Arduino. If the signal is to turn off the alarm, the system stops the buzzer and LED, but
enters a cooldown period to prevent immediate reactivation.

 Cooldown Period: Once the alarm is deactivated, it enters a cooldown state. During this period, the alarm
will not re-trigger, even if motion is detected. If the PIR sensor detects motion during cooldown, the
cooldown timer is reset, and the alarm will only re-activate once the cooldown period (set to 7 seconds) has
elapsed without any further motion.

 Deactivation: If the user decides to turn off the alarm manually via Bluetooth (signal 2), the system stops the
alarm without entering the cooldown stage, immediately deactivating both the buzzer and LED. 

[Read more...](https://github.com/user-attachments/files/19814241/AlarmSystem.pdf)
