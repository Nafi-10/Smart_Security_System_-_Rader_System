#include <Servo.h>

Servo servoX;
Servo servoY;
Servo servoA;  // Missile base servo (horizontal rotation)
Servo servoB;  // Missile vertical servo (up/down)

#define trigPin 7
#define echoPin 6
#define servoXPin 9
#define servoYPin 10
#define servoAPin 11
#define servoBPin 3
#define buzzerPin 4
#define redLedPin 5
#define greenLedPin 8  

long duration;
float distance;

void setup() {
  Serial.begin(9600);

  servoX.attach(servoXPin);
  servoY.attach(servoYPin);
  servoA.attach(servoAPin);
  servoB.attach(servoBPin);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);

  // Initialize missile servos to rest position
  servoA.write(90);  // Center base
  servoB.write(0);   // Missile down

  digitalWrite(greenLedPin, HIGH); // Green LED ON by default

  Serial.println("🚀 Missile Tracking & Locking System Activated");
}

// Basic ultrasonic reading
float getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0) return -1;

  float dist = (duration * 0.0343) / 2;

  if (dist < 2 || dist > 400) return -1;

  return dist;
}

// Smooth readings
float getSmoothedDistance(int samples = 5) {
  float sum = 0;
  int validCount = 0;
  for (int i = 0; i < samples; i++) {
    float d = getDistance();
    if (d != -1) {
      sum += d;
      validCount++;
    }
    delay(10);
  }
  if (validCount == 0) return -1;
  return sum / validCount;
}

// Beep only
void beepOnly() {
  tone(buzzerPin, 1000);
  delay(100);
  noTone(buzzerPin);
  delay(80);
}

// Blink red LED for lock
void blinkRed() {
  digitalWrite(redLedPin, HIGH);
  tone(buzzerPin, 1200);
  delay(150);
  digitalWrite(redLedPin, LOW);
  noTone(buzzerPin);
  delay(150);
}

// Blink red & green alternately
void blinkRedGreen() {
  digitalWrite(redLedPin, HIGH);
  digitalWrite(greenLedPin, LOW);
  delay(150);
  digitalWrite(redLedPin, LOW);
  digitalWrite(greenLedPin, HIGH);
  delay(150);
}

// Aim missile at object
void aimMissile(int scanX, int scanY) {
  int missileBaseAngle = map(scanX, 0, 180, 0, 180);
  int missileElevAngle = map(scanY, 0, 180, 0, 90);

  servoA.write(missileBaseAngle);
  servoB.write(missileElevAngle);
  delay(300);
}

// Launch effect
void missileLaunchEffect() {
  servoB.write(90);  // Launch
  tone(buzzerPin, 1500);
  digitalWrite(redLedPin, HIGH);
  delay(800);
  servoB.write(0);   // Reset
  digitalWrite(redLedPin, LOW);
  noTone(buzzerPin);
}

// Explosion effect
void explosionEffect() {
  digitalWrite(redLedPin, HIGH);
  tone(buzzerPin, 500);
  delay(300);
  digitalWrite(redLedPin, LOW);
  noTone(buzzerPin);
  delay(200);
}

void loop() {
  for (int x = 0; x <= 180; x += 10) {
    servoX.write(x);
    delay(150);

    for (int y = 0; y <= 180; y += 20) {
      servoY.write(y);
      delay(50);

      distance = getSmoothedDistance();
      if (distance == -1) continue;

      Serial.print("X: "); Serial.print(x);
      Serial.print("°, Y: "); Serial.print(y);
      Serial.print("° => Distance: ");
      Serial.print(distance); Serial.println(" cm");

      if (distance <= 20) {  // Locking distance
        Serial.println("🎯 Target lock!");
        digitalWrite(greenLedPin, LOW); // Turn off green
        for (int i = 0; i < 6; i++) { // Blink red before destroy
          blinkRed();
        }
        aimMissile(x, y);
        delay(500);
        Serial.println("🚀 Missile Launch!");
        missileLaunchEffect();
        delay(2000);
        Serial.println("💥 Target Destroyed!");
        explosionEffect();
        digitalWrite(greenLedPin, HIGH); // Reset green LED
      }
      else if (distance <= 50) {  // Object detected
        Serial.println("⚠ Object Detected");
        for (int i = 0; i < 3; i++) { // Blink red & green alternately
          blinkRedGreen();
        }
      }
      else {
        digitalWrite(redLedPin, LOW);
        digitalWrite(greenLedPin, HIGH); // Default green ON
        noTone(buzzerPin);
      }
    }
  }
}
