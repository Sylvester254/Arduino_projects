#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_PRINT Serial
#define BLYNK_AUTH_TOKEN       "••••••••••••••••••••••••"  //replace with authentication token from Blynk

#define BATTERY_PIN A0   // ADC input pin connected to the battery voltage

const int momentarySwitchPin = 1; // D1 Pin for the momentary switch
const int relayPin = 2; // D2 Pin for the relay
const int statusLEDPin = 3; // D3 Pin for the status LED

// Blynk virtual pins for battery voltage, latch state and lock out flag
const int batteryVoltagePin = V0;
const int latchStatePin = V1;
const int lockOutFlagPin = V2;

// Variables to store battery voltage and latch state
float batteryVoltage = 0;
int switchState = 0;

BlynkTimer timer;
void myTimer()
{
  // Update the battery voltage and latch state in the Blynk app
  Blynk.virtualWrite(batteryVoltagePin, batteryVoltage);
  Blynk.virtualWrite(latchStatePin, switchState);

  }
void setup() {
  // Initialize the serial connection
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, "wifi-ssid", "wifi-pass");
  
  // Initialize the digital input pin for the momentary switch
  pinMode(momentarySwitchPin, INPUT);
   // Initialize the digital output pin for the relay and the indicator LED
  pinMode(relayPin, OUTPUT);
  pinMode(statusLEDPin, OUTPUT);
  //  set default state of relay
  digitalWrite(relayPin, LOW);

  // Setting interval to send data to Blynk Cloud every second
  timer.setInterval(1000L, myTimer); 
}

//send 0(low) or 1(high) to control the momentary switch remotely 
BLYNK_WRITE(V3) {
    // Read the lock out flag in the Blynk app
    Blynk.syncVirtual(lockOutFlagPin);

    // Read the state of the button in the Blynk app
    int buttonState = param.asInt();
    if (buttonState == 1 && lockOutFlagPin != 1) {
      // Activate the momentary switch if it's not locked out
      digitalWrite(relayPin, HIGH);
      delay(500);
      digitalWrite(relayPin, LOW);
    }
  }

  
void loop() {
 Blynk.run();
 
 // runs BlynkTimer
  timer.run(); 
  
    // Check the state of the momentary switch
    int switchState = digitalRead(momentarySwitchPin);
    if (switchState == HIGH) {
      // Activate the relay when the momentary switch is pressed
      digitalWrite(relayPin, HIGH);   //rotary latch output will be controlled by the relay shield 
      digitalWrite(statusLEDPin, HIGH);
      delay(500); // Wait for 500 milliseconds
    } else {
      // Deactivate the relay when the momentary switch is released
      digitalWrite(relayPin, LOW);
      digitalWrite(statusLEDPin, LOW);
    }


 // Read the value of the battery using the ADC
  int batteryValue = analogRead(BATTERY_PIN);
  float batteryVoltage = (batteryValue * 3.3) / 1024.0;

  // Check the lock out flag in the Blynk app
    Blynk.syncVirtual(lockOutFlagPin); 
    if (lockOutFlagPin == 1) {
      // Inhibit the momentary switch activation
      digitalWrite(relayPin, LOW);
    }
  
  delay(500);
}
