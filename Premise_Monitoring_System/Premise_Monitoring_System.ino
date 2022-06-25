/* KY-001 Temperature sensor, MQ-4 Gas Sensor,buzzer,KY-026 flame sensor,Photoresistor,PIR motion sensor and LCD display Circuit with Arduino */

#include <LiquidCrystal.h>

const int RS = 12, EN = 11, D4 = 5, D5 = 4, D6 = 3, D7 = 2;
LiquidCrystal lcd(RS,EN,D4,D5,D6,D7);             //set Uno pins that are connected to LCD, 4-bit mode

#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 6 // Data wire is plugged into pin 6 on the Arduino
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

const int AOUTpin = 0; //the AOUT pin of the methane sensor goes into analog pin A0 of the arduino
int analogPin = A1; // KY-026 analog interface
int analogVal; //analog readings
int buzzer = 8; // set the buzzer control digital IO pin

int value;

int sensor = 7;              // the pin that the PIR motion sensor is atteched to
int state = LOW;             // by default, no motion detected
int val = 0;                 // variable to store the sensor status (value)

void setup() {
  Serial.begin(115200);//sets the baud rate

  pinMode(sensor, INPUT);
  pinMode(analogPin, INPUT);
  pinMode(AOUTpin, INPUT);//sets the pin as an input to the arduino
  pinMode(buzzer, OUTPUT); // set pin 8 as output
  pinMode(LED_BUILTIN, OUTPUT);
  lcd.begin(16,2);    //set 16 columns and 2 rows of 16x2 LCD
  
  sensors.begin();

  lcd.setCursor(15,0);
  lcd.print("PREMISE MONITOR SYSTEM");             //print project name once on first row
  for (int i = 0; i < 23; i++) {                    //moves "PREMISE MONITOR SYSTEM" to the left by 8 character
  lcd.scrollDisplayLeft();             
  delay(800);
  }
//  lcd.clear();
  lcd.setCursor(0,0);
}
void loop()
{
  /*Photoresistor*/
  // read the input on analog pin A5:
  int sensorValue = analogRead(A5);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  // print out the value you read:
  Serial.print("Voltage:");
  Serial.println(voltage);
  delay(100);
  if(voltage <= 1.6){
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100); // wait for a second
/*motion sensor activates*/
  val = digitalRead(sensor);   // read sensor value
  if (val == HIGH) {           // check if the sensor is HIGH
//    digitalWrite(led, HIGH);   // turn LED ON
//    delay(500);                // delay 100 milliseconds 
    
    if (state == LOW) {
      lcd.clear();
      lcd.print("Motion detected!");
      Serial.println("Motion detected!"); 
      state = HIGH;       // update variable state to HIGH
    }
  } 
  else {
//      digitalWrite(led, LOW); // turn LED OFF
//      delay(500);             // delay 200 milliseconds 
      
      if (state == HIGH){
        lcd.clear();
        lcd.print("Motion stopped!");
        Serial.println("Motion stopped!");
        state = LOW;       // update variable state to LOW
    }
  } 
  }
  else{
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
//  delay(100); 
  }
  
  /*Temperature sensor*/
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  sensors.requestTemperatures(); // Send the command to get temperatures
  lcd.clear();
  lcd.print("Temperature:");
  lcd.setCursor(0,1);
  lcd.print(sensors.getTempCByIndex(0)); //You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  lcd.write(B11011111); // degree symbol
  lcd.print("C ");
  Serial.println(sensors.getTempCByIndex(0));
  delay(2000);
  lcd.clear();
  /*Gas sensor*/
  value = analogRead(AOUTpin); //reads the analaog value from MQ4 sensor's AOUT pin
//  lcd.setCursor(0,0);
  lcd.print("Gas level:");
  lcd.setCursor(0,1);
  lcd.print(value);//prints the gas value
  Serial.println(value);
  delay(2000);
  lcd.clear();
  if (value >= 15 && analogVal > 300) {
    for (int i = 0; i < 20; i++) {  // make a sound
    digitalWrite(buzzer, HIGH);
    delay(1); // delay 1ms
    digitalWrite(buzzer, LOW);
    delay(1);
  }
  }
  
  /*flame sensor*/
  analogVal = analogRead(analogPin);
//  lcd.setCursor(0,0); 
  lcd.print("flame reading: ");
  lcd.setCursor(0,1);
  lcd.print(analogVal); // print analog value to LCD
  Serial.println(analogVal);
  delay(2000);
  lcd.clear();
  if (analogVal < 450 && value < 15){
    for (int i = 0; i < 50; i++) {  // make a sound
    digitalWrite(buzzer, HIGH);
    delay(2); // delay 2ms
    digitalWrite(buzzer, LOW);
    delay(2);
  }
  }
  if (value >= 15 && analogVal < 400 ){
    for (int i = 0; i < 150; i++) {  // make a sound
    digitalWrite(buzzer, HIGH);
    delay(3); // delay 3ms
    digitalWrite(buzzer, LOW);
    delay(2);
  }
  }
}
