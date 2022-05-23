/* KY-001 Temperature sensor, MQ-4 Gas Sensor,buzzer,KY-026 flame sensor Circuit with Arduino */

#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2 // Data wire is plugged into pin 2 on the Arduino
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

const int AOUTpin = 0; //the AOUT pin of the methane sensor goes into analog pin A0 of the arduino
int analogPin = A1; // KY-026 analog interface
int analogVal; //analog readings
int buzzer = 8; // set the buzzer control digital IO pin

int value;

void setup() {
  Serial.begin(115200);//sets the baud rate

  pinMode(analogPin, INPUT);
  pinMode(AOUTpin, INPUT);//sets the pin as an input to the arduino
  pinMode(buzzer, OUTPUT); // set pin 8 as output

  sensors.begin();
}
void loop()
{
  /*Temperature sensor*/
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.print("Temperature: ");
  Serial.print(sensors.getTempCByIndex(0)); // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  
  /*Gas sensor*/
  value = analogRead(AOUTpin); //reads the analaog value from MQ4 sensor's AOUT pin
  Serial.print("Gas level: ");
  Serial.println(value);//prints the gas value
  if (value >= 12 && analogVal > 300) {
    for (int i = 0; i < 20; i++) {  // make a sound
    digitalWrite(buzzer, HIGH);
    delay(1); // delay 1ms
    digitalWrite(buzzer, LOW);
    delay(1);
  }
  }
  
  /*flame sensor*/
  analogVal = analogRead(analogPin); 
  Serial.println("flame reading: ");
  Serial.println(analogVal); // print analog value to serial
  if (analogVal < 500 && value < 12){
    for (int i = 0; i < 50; i++) {  // make a sound
    digitalWrite(buzzer, HIGH);
    delay(2); // delay 2ms
    digitalWrite(buzzer, LOW);
    delay(2);
  }
  }
  if (value >= 12 && analogVal < 500 ){
    for (int i = 0; i < 150; i++) {  // make a sound
    digitalWrite(buzzer, HIGH);
    delay(3); // delay 3ms
    digitalWrite(buzzer, LOW);
    delay(2);
  }
  }
  delay(1000);
}
