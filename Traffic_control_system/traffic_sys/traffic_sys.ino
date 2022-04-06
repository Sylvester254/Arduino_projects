//pin numbers are initialized here
#define Q0 13  
#define Q1 12  
#define Q2 11
#define Q3 10  
#define Q4 9
#define Q5 8
#define Q6 7   
#define Q7 6

int sensor1 = 2;
int sensor2 = 3;
int sensor3 = 4;
int sensor4 = 5;

//setup code indicating input pins for sensors and output pins for the traffic system
void setup() {  
 pinMode(sensor1, INPUT);
 pinMode(sensor2, INPUT);
 pinMode(sensor3, INPUT);
 pinMode(sensor4, INPUT);
 
  pinMode (Q0,OUTPUT);
  pinMode (Q1,OUTPUT);
  pinMode (Q2,OUTPUT);
  pinMode (Q3,OUTPUT);
  pinMode (Q4,OUTPUT);
  pinMode (Q5,OUTPUT);
  pinMode (Q6,OUTPUT);
  pinMode (Q7,OUTPUT);
 

}
   // this section runs repeatedly checking which sensors are ON and activating the respective Traffic Lights
void loop() {

   int digitalValue = digitalRead(sensor1);
   int digitalValue2 = digitalRead(sensor2);
   int digitalValue3 = digitalRead(sensor3);
   int digitalValue4 = digitalRead(sensor4);

   // this part runs only if all 4 sensors are on indicating all roads are busy
   if (digitalValue = HIGH && digitalValue2 = HIGH && digitalValue3 = HIGH && digitalValue4 = HIGH) {
    digitalWrite(Q0,HIGH);
    delay(1500);
  digitalWrite(Q0,LOW);
     delay(10);
  digitalWrite(Q1,HIGH);
     delay(1500);
  digitalWrite(Q1,LOW);
     delay(10);
   digitalWrite(Q2,HIGH);
     digitalWrite(Q2,HIGH);
     delay(1500);
  digitalWrite(Q2,LOW);
     delay(10);            
  digitalWrite(Q3,HIGH);
     delay(1500);
  digitalWrite(Q3,LOW);
     delay(10);  
   digitalWrite(Q4,HIGH);
   digitalWrite(Q4,HIGH);
     delay(1500);
  digitalWrite(Q4,LOW);
     delay(10);            
  digitalWrite(Q5,HIGH);
     delay(1500);
  digitalWrite(Q5,LOW);
     delay(10);            
   digitalWrite(Q6,HIGH);
    digitalWrite(Q6,HIGH);
     delay(1500);
  digitalWrite(Q6,LOW);
     delay(10);            
  digitalWrite(Q7,HIGH);
     delay(1500);
  digitalWrite(Q7,LOW);
     delay(10);            
   }
   //This runs if only sensor on Road A is ON
 else if (digitalValue = HIGH && digitalValue2 = LOW && digitalValue3 = LOW && digitalValue4 = LOW) {
    digitalWrite(Q0,HIGH);
    delay(1500);
  digitalWrite(Q0,LOW);
     delay(10);
  digitalWrite(Q1,HIGH);
     delay(1500);
  digitalWrite(Q1,LOW);
     delay(10);
  digitalWrite(Q3,HIGH);
     delay(1500);
  digitalWrite(Q3,LOW);
     delay(10);    
  digitalWrite(Q5,HIGH);
     delay(1500);
  digitalWrite(Q5,LOW);
     delay(10);            
  digitalWrite(Q7,HIGH);
     delay(1500);
  digitalWrite(Q7,LOW);
     delay(10);            
   }           
   //This runs only if sensor on road B is ON
  else if (digitalValue = LOW && digitalValue2 = HIGH && digitalValue3 = LOW && digitalValue4 = LOW) {
    
  digitalWrite(Q1,HIGH);
     delay(1500);
  digitalWrite(Q1,LOW);
     delay(10);
     digitalWrite(Q2,HIGH);
     delay(1500);
  digitalWrite(Q2,LOW);
     delay(10);            
  digitalWrite(Q3,HIGH);
     delay(1500);
  digitalWrite(Q3,LOW);
     delay(10);  
  digitalWrite(Q5,HIGH);
     delay(1500);
  digitalWrite(Q5,LOW);
     delay(10);             
  digitalWrite(Q7,HIGH);
     delay(1500);
  digitalWrite(Q7,LOW);
     delay(10);            
   }
   //This runs only if sensor on road C is ON
  else if (digitalValue = LOW && digitalValue2 = LOW && digitalValue3 = HIGH && digitalValue4 = LOW) {
   
  digitalWrite(Q1,HIGH);
     delay(1500);
  digitalWrite(Q1,LOW);
     delay(10);
  digitalWrite(Q3,HIGH);
     delay(1500);
  digitalWrite(Q3,LOW);
     delay(10);  
   digitalWrite(Q4,HIGH);
   digitalWrite(Q4,HIGH);
     delay(1500);
  digitalWrite(Q4,LOW);
     delay(10);            
  digitalWrite(Q5,HIGH);
     delay(1500);
  digitalWrite(Q5,LOW);
     delay(10);            
  digitalWrite(Q7,HIGH);
     delay(1500);
  digitalWrite(Q7,LOW);
     delay(10); 
   }           
      //This runs only if sensor on road D is ON

  else if (digitalValue = LOW && digitalValue2 = LOW && digitalValue3 = LOW && digitalValue4 = HIGH) {
     
  digitalWrite(Q1,HIGH);
     delay(1500);
  digitalWrite(Q1,LOW);
     delay(10);
  digitalWrite(Q3,HIGH);
     delay(1500);
  digitalWrite(Q3,LOW);
     delay(10);  
   digitalWrite(Q5,HIGH);
     delay(1500);
  digitalWrite(Q5,LOW);
     delay(10);            
   digitalWrite(Q6,HIGH);
    digitalWrite(Q6,HIGH);
     delay(1500);
  digitalWrite(Q6,LOW);
     delay(10);            
  digitalWrite(Q7,HIGH);
     delay(1500);
  digitalWrite(Q7,LOW);
     delay(10);            
     }
}
