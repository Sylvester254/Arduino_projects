int relay = 10;  //Pin 10
void setup() 
{   
  pinMode(relay,OUTPUT);    // Define the port attribute as output 
} 
void loop() 
{   
  digitalWrite(relay,HIGH);   // turn the relay ON
                // [NO] is connected to feed
                // [NC] is not connected to feed
  delay(2000);          
  digitalWrite(relay,LOW);    // turn the relay OFF
                // [NO] is not connected to feed
                // [NC] is connected to feed
  delay(2000); 
} 
