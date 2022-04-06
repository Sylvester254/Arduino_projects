#define Q0 13  
#define Q1 12  
#define Q2 11
#define Q3 10  
#define Q4 9
#define Q5 8
#define Q6 7   
#define Q7 6

int pin1 = 2;
int pin2 = 3;
int pin3 = 4;
int pin4 = 5;

void setup() {  // This code runs once
 pinMode(pin1, INPUT);
 pinMode(pin2, INPUT);
 pinMode(pin3, INPUT);
 pinMode(pin4, INPUT);
 
  pinMode (Q0,OUTPUT);
  pinMode (Q1,OUTPUT);
  pinMode (Q2,OUTPUT);
  pinMode (Q3,OUTPUT);
  pinMode (Q4,OUTPUT);
  pinMode (Q5,OUTPUT);
  pinMode (Q6,OUTPUT);
  pinMode (Q7,OUTPUT);
 

}
   //turn ON exactly one output pin at a time
void loop() {

   int digitalValue = digitalRead(pin1);
   if (digitalValue = HIGH) {
   digitalWrite(Q0,HIGH);
    delay(5000);
     }
   else {  
    delay(1500);
   }
  digitalWrite(Q0,LOW);
     delay(10);
  digitalWrite(Q1,HIGH);
     delay(1500);
  digitalWrite(Q1,LOW);
     delay(10);

  int digitalValue2 = digitalRead(pin2);
   if (digitalValue2 = HIGH) {
   digitalWrite(Q2,HIGH);
     delay(5000);
     }
   else {  
     digitalWrite(Q2,HIGH);
     delay(1500);
   }
  digitalWrite(Q2,LOW);
     delay(10);            
  digitalWrite(Q3,HIGH);
     delay(1500);
  digitalWrite(Q3,LOW);
     delay(10);  
               
  int digitalValue3 = digitalRead(pin3);
   if (digitalValue3 = HIGH) {
   digitalWrite(Q4,HIGH);
     delay(5000);
     }
   else {  
   digitalWrite(Q4,HIGH);
     delay(1500);
   }
  digitalWrite(Q4,LOW);
     delay(10);            
  digitalWrite(Q5,HIGH);
     delay(1500);
  digitalWrite(Q5,LOW);
     delay(10);            
  
   int digitalValue4 = digitalRead(pin4);
   if (digitalValue4 = HIGH) {
   digitalWrite(Q6,HIGH);
     delay(5000);
     }
   else {  
    digitalWrite(Q6,HIGH);
     delay(1500);
   }
  digitalWrite(Q6,LOW);
     delay(10);            
  digitalWrite(Q7,HIGH);
     delay(1500);
  digitalWrite(Q7,LOW);
     delay(10);            
}
