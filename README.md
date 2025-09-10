_**Missile Tracking & Security System**_

This project integrates ultrasonic scanning, servo-based missile launcher simulation, IR intrusion detection, keypad-based password security, and alarm triggers.
It is designed to mimic a defense turret with access control and object detection.

📂 Project Structure

The project has two main Arduino code parts:

**Part 1 – Missile Tracking & Locking System**

Uses ultrasonic sensor for object detection.

Scans area with servo motors.

Simulates target lock, missile launch, and explosion.

Includes LED and buzzer indicators.

**Part 2 – Security Access with Keypad & IR Sensors**

Keypad-based password authentication.

IR sensors for intrusion detection.

Alarm triggers on wrong attempts.

Automatic disabling of IR sensors for 10 seconds on correct password.

_⚡** Features**_

**Part 1 – Missile Tracking**

Ultrasonic sensor scanning (2–400 cm range).

Servo-mounted radar (X & Y axis movement).

Missile servos simulate targeting and launching.

LED & Buzzer feedback:

Green LED = System active.

Red LED = Target lock.

Red-Green blinking = Object detected.

Siren tones during launch & explosion.

**Part 2 – Keypad & IR Security**

4x4 Keypad password input.

Configurable password system ("1234" by default).

IR sensors for ground object detection.

Access control:

✅ Correct password → IR disabled for 10s (Gate opens).

❌ Wrong password → Warning, alarm after 2 attempts.

LED & Buzzer effects for alerts and gate simulation.

🛠️** _Hardware Requirements_**
Common

Arduino Uno / Mega / Nano

Breadboard & jumper wires

**Part 1 – Missile Tracking**

2 × Servo motors (Radar scan – servoX, servoY)

2 × Servo motors (Missile base – servoA, servoB)

Ultrasonic sensor (HC-SR04)

1 × Red LED

1 × Green LED

1 × Buzzer

Part 2 – Security Access

4x4 Matrix Keypad

2 × IR sensors

1 × LED

1 × Buzzer

⚙️**_ Pin Configuration_**
Part 1 – Missile Tracking
Component	Arduino Pin
Ultrasonic TRIG	7
Ultrasonic ECHO	6
Servo X	9
Servo Y	10
Servo A (Base)	11
Servo B (Vertical)	3
Buzzer	4
Red LED	5
Green LED	8
_**Part 2 – Keypad & IR Security**_
Component	Arduino Pin
Keypad Rows	2, 3, 4, 5
Keypad Cols	6, 7, 8, 9
IR Sensor 1	10
IR Sensor 2	11
LED	12
Buzzer	13
🔑 Password System (Part 2)

Default password: 1234

# = Enter key

* = Clear input

✅ Correct password:

Prints Access Granted

Disables IR for 10s (gate simulation)

❌ Wrong password:

After 2 failed attempts, alarm triggers

🎮 System Behavior
Missile Tracking

Radar scans area with X-Y servo movement.

If object detected:

≤ 20 cm → Target lock → Missile launch + Explosion simulation.

≤ 50 cm → Warning mode → Red/Green blinking with beeps.

> 50 cm → Idle (green LED ON).

Security System

User enters password via keypad.

If correct → Gate opens (IR disabled for 10s).

If wrong twice → Alarm (long sirens & LED blinks).

IR sensors detect ground intrusions when enabled.

📜 Example Serial Monitor Output
🚀 Missile Tracking & Locking System Activated
X: 30°, Y: 60° => Distance: 18 cm
🎯 Target lock!
🚀 Missile Launch!
💥 Target Destroyed!

Access Granted
IR Sensor Disabled for 10 Seconds .. Gate Opening
IR Sensor Activating ... Gate is closing

Wrong Password!
Wrong Password!
!! ALARM TRIGGERED !!

**_🚧 Future Improvements_**

Add Bluetooth/WiFi control for remote access.

Implement LCD display for status updates.

Use motion tracking camera (OpenCV + Arduino) for advanced targeting.

Add EEPROM support to save password permanently.

_**📖 How to Use**_

Upload Part 1 code to Arduino for missile tracking demo.

Upload Part 2 code for keypad-based access & security.

Connect components as per pin mapping.

Monitor outputs via Serial Monitor (9600 baud).

✨ Enjoy building your Arduino Missile Defense + Security System!
