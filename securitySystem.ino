#include <Keypad.h>

// ---------------- Keypad Config ----------------
const byte rows[4] = {2, 3, 4, 5};  
const byte cols[4] = {6, 7, 8, 9};  

char keys[4][4] = {
  {'D', 'C', 'B', 'A'},
  {'#', '9', '6', '3'},
  {'0', '8', '5', '2'},
  {'*', '7', '4', '1'},
};

Keypad mykeypad = Keypad(makeKeymap(keys), rows, cols, 4, 4);

// ---------------- IR Sensor Config ----------------
#define IR1_PIN 10
#define IR2_PIN 11

// ---------------- LED & Buzzer Config ----------------
#define LED_PIN 12
#define BUZZER_PIN 13

// ---------------- Password System ----------------
String password = "1234";  // Set your password here
String inputPassword = "";
int wrongAttempts = 0;
bool irEnabled = true; // Controls IR activity

void setup() {
  Serial.begin(9600);

  pinMode(IR1_PIN, INPUT);
  pinMode(IR2_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  // --------- Keypad Reading ---------
  char key = mykeypad.getKey();
  if (key) {
    if (key == '#') { // '#' is Enter key
      if (inputPassword == password) {
        Serial.println("Access Granted");
        wrongAttempts = 0; 
        disableIRfor10Sec(); // Disable IR for 10 sec with beeps & blinks
      } else {
        wrongAttempts++;
        Serial.println("Wrong Password!");
        if (wrongAttempts >= 2) {
          triggerAlarm();  // Two long sirens & blinks
          wrongAttempts = 0; 
        }
      }
      inputPassword = ""; 
    } 
    else if (key == '*') { // Clear input
      inputPassword = "";
      Serial.println("Input Cleared");
    }
    else {
      inputPassword += key; 
      Serial.print("*"); 
    }
  }

  // --------- IR Sensor Reaction ---------
  if (irEnabled) {
    int ir1State = digitalRead(IR1_PIN);
    int ir2State = digitalRead(IR2_PIN);

    if (ir1State == LOW || ir2State == LOW) { 
      Serial.println("Unauthorized object on ground");
      digitalWrite(LED_PIN, HIGH);
      tone(BUZZER_PIN, 1000);
      delay(200); // Short beep
      digitalWrite(LED_PIN, LOW);
      noTone(BUZZER_PIN);
      delay(200);
    }
  }

  delay(50);
}

// --------- Alarm Function ---------
void triggerAlarm() {
  Serial.println("!! ALARM TRIGGERED !!");
  for (int i = 0; i < 2; i++) { 
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, 1000);
    delay(1000);
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
    delay(500);
  }
}

// --------- Disable IR for 10 sec with Beeps & Blinks ---------
void disableIRfor10Sec() {
  irEnabled = false; 
  Serial.println("IR Sensor Disabled for 10 Seconds .. Gate Opening");

  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, 1000);
    delay(500); 
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
    delay(1500); 
  }

  Serial.println("IR Sensor Activating ... Gate is closing");
  irEnabled = true; 
}
