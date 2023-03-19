#include <OneWire.h>
#include <DallasTemperature.h>
 
// Input data wire for temperature is plugged into pin 13 on the Arduino
#define ONE_WIRE_BUS 13
 
// Setup a oneWire instance to communicate with any OneWire devices 
OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

//LEDs for temp. indicate if temperature is normal or its very high
int pinLedG = 4;     //output for Green LED
int pinLedR = 10;    //output for Red LED

//LEDs for moisture indicate if moisture level in compost is normal(wet) or low(dry)
int WET = 2; //represented by Green LED
int DRY = 3; //represented by Red LED 

//LEDs for methane gas indicate if methane level is high or low
int pinGreenLed = 6;   //output for Green LED
int pinRedLed = 7;    //output for Red LED

int pinSensor = A5;  //input pin for gas sensor 
int THRESHOLD = 100; //ideal level of methane gas

//initializing values for evaluating moisture level
 const int soilValue = 520;   
const int WaterValue = 260;  
int intervals = (soilValue - WaterValue)/3;
int soilMoistureValue = 0;

//This section runs once on compilation 
void setup(void)
{
  // start serial port
  Serial.begin(9600);
  pinMode(pinLedR, OUTPUT);
  pinMode(pinLedG, OUTPUT);
  
  pinMode(WET, OUTPUT);
  pinMode(DRY, OUTPUT);

  pinMode(pinRedLed, OUTPUT);
 pinMode(pinGreenLed, OUTPUT);
 pinMode(pinSensor, INPUT);
  
  // Start up the library
  sensors.begin();
 
}
 
 // This section runs repeatedly (in a loop) on compilation
void loop(void)
{   //TEMPERATURE SENSOR
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  sensors.requestTemperatures(); // Send the command to get temperatures

  Serial.print("Temperature is: "); //displays on serial monitor
  Serial.print(sensors.getTempCByIndex(0)); 
    // 0 refers to the first IC on the wire
     if (sensors.getTempCByIndex(0) > 65) { //if temperature is above 65 degrees, Red LED turns on
    digitalWrite(pinLedG, LOW);
    digitalWrite(pinLedR, HIGH);
  }
  else {                              // if below 65, turn Green LED on instead
     digitalWrite(pinLedG, HIGH);
    digitalWrite(pinLedR, LOW);
  }
  delay(1000);      //wait for 1 second then test again 

 //SOIL MOISTURE SENSOR
  soilMoistureValue = analogRead(A0);  //moisture sensor output connects to pin A0
  //check if water level is high,if true turn Green LED on
  if(soilMoistureValue > (WaterValue + intervals) && soilMoistureValue < (soilValue - intervals))
{
  Serial.println("Moisture level: Wet");  //display on serial monitor 
  digitalWrite(WET, HIGH);               
  digitalWrite(DRY, LOW);
}
 //check if water level is low, if true turn Red LED on
else if(soilMoistureValue < soilValue && soilMoistureValue > (soilValue - intervals))
{
  Serial.println("Moisture level:Dry");   //display on serial monitor 
  digitalWrite(DRY, HIGH);
  digitalWrite(WET, LOW);
}
delay(1000);    //wait for 1 second then test again 

  //METHANE GAS SENSOR
int analogValue = analogRead(pinSensor);
Serial.println(analogValue);
if (analogValue >= THRESHOLD) {           //check if gas level is above the threshold,
  Serial.println("Methane level:HIGH");    //display High on serial monitor 
  digitalWrite(pinGreenLed, LOW);
  digitalWrite(pinRedLed, HIGH);              //turn Red LED on and Green LED off
}
else {                                    //else if gas level is below the threshold,
  Serial.println("Methane level:NORMAL");   //display normal on serial monitor 
  digitalWrite(pinRedLed, LOW);              //turn Red LED off and Green LED on
  digitalWrite(pinGreenLed, HIGH);
}
delay(1000);    //wait for 1 second then test again 
}
