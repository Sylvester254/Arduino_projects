#include <WiFi.h>
#include <WiFiClient.h>

#define BATTERY_PIN A0   // ADC input pin connected to the battery voltage

char *ssid = "YOUR_SSID";
char *password = "YOUR_PASSWORD";

const int momentarySwitchPin = 1; // D1 Pin for the momentary switch
const int relayPin = 2; // D2 Pin for the relay
//const int adcPin = A0; // Pin for the ADC input
const int statusLEDPin = 3; // D3 Pin for the status LED
bool lockOut = false; // Flag for the lockout function

WiFiClient client;

void setup() {
  Serial.begin(115200);
  pinMode(momentarySwitchPin, INPUT_PULLUP); // Initialize the momentary switch as a digital input with pull-up resistor
  // Initialize the digital input pin for the momentary switch
//  pinMode(momentarySwitchPin, INPUT);
   // Initialize the digital output pin for the relay
  pinMode(relayPin, OUTPUT);
   // Initialize the digital output pin for the indicator LED
  pinMode(statusLEDPin, OUTPUT);
  //  set default state of relay
  digitalWrite(relayPin, LOW);

  // Initialize the ADC input pin connected to the battery voltage
//  analogReadResolution(10);

  // Connect to the Wi-Fi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to ");
   Serial.println(ssid);
}

void loop() {
  int lockOutState = digitalRead(lockOut);
  if (lockOutState == LOW) {
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
  } else {
    // Keep the relay deactivated when the lockout switch is activated
    digitalWrite(relayPin, LOW);
    digitalWrite(statusLEDPin, LOW);
  }

//  int adcValue = analogRead(adcPin);
//  float voltage = (adcValue * 3.3) / 1024;

 // Read the value of the battery using the ADC
  int batteryValue = analogRead(BATTERY_PIN);
  float batteryVoltage = (batteryValue * 3.3) / 1024.0;

  // Send the battery voltage and the state of the rotary latch to the app(represented by 
//  the state of the momentary switch)
  if (client.connect("your_server_IP", 80)) {
    String postData = "Battery Voltage=" + String(batteryVoltage) + "&Latch State=" + String(momentarySwitchPin);
    client.print("POST /update HTTP/1.1\r\n");
    client.print("Host: your_server_IP\r\n");
    client.print("Content-Type: application/x-www-form-urlencoded\r\n");
    client.print("Content-Length: " + String(postData.length()) + "\r\n");
    client.print("\r\n");
    client.print(postData);
    client.stop();
  }
  
  delay(500);
}
