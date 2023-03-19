#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h> // includes the LiquidCrystal Library 

const int RS = 2, EN = 3, D4 = 4, D5 = 5, D6 = A1, D7 = A2;
LiquidCrystal lcd(RS,EN,D4,D5,D6,D7);             //set Uno pins that are connected to LCD, 4-bit mode

// Input data wire for temperature is plugged into pin 13 on the Arduino
#define ONE_WIRE_BUS 13
 
// Setup a oneWire instance to communicate with any OneWire devices 
OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

//LEDs for temp. indicate if temperature is normal or its very high
int pinLedG = 12;    //output for Green LED
int pinLedR = 11;    //output for Red LED

//LEDs for moisture indicate if moisture level in compost is normal(wet) or low(dry)
int WET = 8; //represented by Green LED
int DRY = 7; //represented by Red LED 

//LEDs for methane gas indicate if methane level is high or low
int pinGreenLed = 10;  //output for Green LED
int pinRedLed = 9;    //output for Red LED

int pinSensor = A5;  //input pin for gas sensor 
int THRESHOLD = 100; //ideal level of methane gas

//initializing values for evaluating moisture level
 const int soilValue = 520;   
const int WaterValue = 260;  
int intervals = (soilValue - WaterValue)/3;
int soilMoistureValue = 0;

int lowMoistureThreshold = 300;
int highMoistureThreshold = 700;

//This section runs once on compilation 
void setup(void)
{
  lcd.begin(16,2); // Initializes the interface to the LCD screen
  analogWrite(6,90); // Generate PWM signal at pin D6, value of 100 (out of 255)
  lcd.setCursor(0, 0);
  lcd.print("SMART COMPOST");
  
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
 
 delay(2000);
}
 
 // This section runs repeatedly (in a loop) on compilation
void loop(void)
{ 
  
  //TEMPERATURE SENSOR
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  sensors.requestTemperatures(); // Send the command to get temperatures
  lcd.setCursor(0, 0);
  lcd.print("SMART COMPOST");
  lcd.setCursor(0, 1);
  lcd.print("Temp:");
  lcd.print(sensors.getTempCByIndex(0)); //print the temperature value
  
  Serial.print("Temperature is: "); //displays on serial monitor
  Serial.print(sensors.getTempCByIndex(0)); 
    // 0 refers to the first IC on the wire
   if (sensors.getTempCByIndex(0) > 65) { //if temperature is above 65 degrees, turn on Red LED
    digitalWrite(pinLedG, LOW);
    digitalWrite(pinLedR, HIGH);
    lcd.print(" High"); //print the temperature status
  }
  else if (sensors.getTempCByIndex(0) < 20) { //if temperature is below 20 degrees, turn on Red LED
    digitalWrite(pinLedG, LOW);
    digitalWrite(pinLedR, HIGH);
    lcd.print(" Low"); //print the temperature status
  }
  else { // if between 57 and 71, turn on Green LED and print "optimal" on serial monitor
     digitalWrite(pinLedG, HIGH);
     digitalWrite(pinLedR, LOW);
     lcd.print(" Norm"); //print the temperature status
     Serial.println("Norm/optimal");
  }

  delay(5000);      //wait for 5 sec then test again 
  lcd.clear(); 
  
 //SOIL MOISTURE SENSOR
  soilMoistureValue = analogRead(A0);  //moisture sensor output connects to pin A0

   lcd.setCursor(0, 0);
  lcd.print("SMART COMPOST");
  lcd.setCursor(0, 2);
  lcd.print("Moisture:");
//  lcd.print(soilMoistureValue); //print the soil moisture value

  //check if water level is high,if true turn Green LED on
  if(soilMoistureValue > (WaterValue + intervals) && soilMoistureValue < (soilValue - intervals))
{
  lcd.print("Nml Wet"); //print the moisture status
  Serial.println("Moisture level: Wet");  //display on serial monitor 
  digitalWrite(WET, HIGH);               
  digitalWrite(DRY, LOW);
}
 //check if water level is low, if true turn Red LED on
else if(soilMoistureValue < soilValue && soilMoistureValue > (soilValue - intervals))
{
  lcd.print(" Dry"); //print the moisture status
 
  Serial.println("Moisture level:Dry");   //display on serial monitor 
  digitalWrite(DRY, HIGH);
  digitalWrite(WET, LOW);
}
delay(5000);    //wait for 5 sec then test again
lcd.clear(); 
 
  //METHANE GAS SENSOR
int analogValue = analogRead(pinSensor);

lcd.setCursor(0, 0);
lcd.print("SMART COMPOST");
lcd.setCursor(0, 3);
lcd.print("Gas: ");
lcd.print(analogValue); //print the gas sensor value

Serial.println(analogValue);
if (analogValue >= THRESHOLD) { //check if gas level is above the threshold,
  lcd.print(" High"); //print the gas status
  Serial.println("Methane level:HIGH");    //display High on serial monitor 
  digitalWrite(pinGreenLed, LOW);
  digitalWrite(pinRedLed, HIGH);              //turn Red LED on and Green LED off
}
else {                                    //else if gas level is below the threshold,
  lcd.print(" Normal"); 
  Serial.println("Methane level:NORMAL");   //display normal on serial monitor 
  digitalWrite(pinRedLed, LOW);              //turn Red LED off and Green LED on
  digitalWrite(pinGreenLed, HIGH);
}
delay(5000);    //wait for 5 sec then test again
lcd.clear(); 
}
