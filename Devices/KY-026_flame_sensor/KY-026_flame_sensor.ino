int led = 13; // define the LED pin
int digitalPin = 2; // KY-026 digital interface
int analogPin = A1; // KY-026 analog interface
int digitalVal; // digital readings
int analogVal; //analog readings
void setup()
{
  pinMode(led, OUTPUT);
  pinMode(digitalPin, INPUT);
  pinMode(analogPin, INPUT);
  Serial.begin(9600);
}
void loop()
{
  // Read the digital interface
  digitalVal = digitalRead(digitalPin); 
  if(digitalVal == HIGH) // if flame is detected
  {
    digitalWrite(led, HIGH); // turn ON Arduino's LED
  }
  else
  {
    digitalWrite(led, LOW); // turn OFF Arduino's LED
  }
  // Read the analog interface
  analogVal = analogRead(analogPin); 
  Serial.println(analogVal); // print analog value to serial
  delay(1000);
}
