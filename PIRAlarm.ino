#include <SoftwareSerial.h>

SoftwareSerial BTSerial(2, 3); // Bluetooth TX to Arduino 2 and RX to Arduino 3

int pirPin = 7; // PIR sensor connected to pin 7
int ledPin = 13; // LED connected to pin 13 (optional for visual feedback)
int buzzerPin = 8; // Buzzer connected to pin 8
int motionCount = 0; // Counter for detected motion
unsigned long cooldownStart; // Timer for cooldown period
bool isOnCooldown = false; // Flag indicating cooldown status
int cooldown = 7000; // Cooldown period duration (in milliseconds)
int enabled = true; // Flag to enable or disable the system

void setup() {
  pinMode(pirPin, INPUT); // Set PIR sensor pin as input
  pinMode(ledPin, OUTPUT); // Set LED pin as output
  pinMode(buzzerPin, OUTPUT); // Set Buzzer pin as output
  BTSerial.begin(9600); // Initialize Bluetooth serial communication
  Serial.begin(9600); // Initialize Arduino serial communication for debugging
}

void loop() {
  if (BTSerial.available()) {
    char command = BTSerial.read(); // Read the incoming Bluetooth command

    if (command == '1') { // Command to turn off the alarm and start cooldown
      digitalWrite(buzzerPin, HIGH); // Turn off the buzzer
      digitalWrite(ledPin, LOW); // Turn off the LED
      motionCount = 0; // Reset the motion count
      Serial.println("Turned OFF By User");
      Serial.println("Alarm Is In Cooldown");
      isOnCooldown = true; // Enable cooldown state
      cooldownStart = millis(); // Start the cooldown timer
    }
    else if (command == '2') { // Command to stop alarm without cooldown
      stopAlarmWithoutCooldown();
    }
  }

  // Cooldown state management
  while (isOnCooldown) {
    int motionOnCooldown = digitalRead(pirPin); // Check if motion is detected during cooldown

    if ((millis() - cooldownStart) >= cooldown && motionOnCooldown == false) {
      isOnCooldown = false; // Exit cooldown after the specified time if no motion
      Serial.println("Alarm Is Active Now");
      break;
    }
    else if (motionOnCooldown == true) {
      Serial.println("Motion Detected During Cooldown");
      cooldownStart = millis(); // Reset cooldown timer if motion is detected
      motionOnCooldown = false;
    }
    delay(100); // Small delay to avoid excessive polling
  }

  // Motion detection and alarm triggering
  int motionDetected = digitalRead(pirPin); // Read the PIR sensor

  if (motionDetected) {
    triggerAlarm(); // Trigger the alarm if motion is detected
  }
  else {
    Serial.println("No motion detected."); // Print message if no motion is detected
  }
  delay(750); // Delay to avoid excessive polling
}

// Trigger alarm: Increment motion count, turn on LED and buzzer
void triggerAlarm() {
  motionCount++; // Increment motion count
  digitalWrite(buzzerPin, LOW); // Turn on the buzzer
  digitalWrite(ledPin, HIGH); // Turn on the LED
  Serial.print("Motion detected! Total Motion: ");
  Serial.println(motionCount); // Print the motion count for debugging
}

// Stop alarm without cooldown
void stopAlarmWithoutCooldown() {
  digitalWrite(buzzerPin, HIGH); // Turn off the buzzer
  digitalWrite(ledPin, LOW); // Turn off the LED
  Serial.println("ALARM DISABLED"); // Print message indicating the alarm is off
}