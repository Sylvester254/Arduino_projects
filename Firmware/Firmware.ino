
// Include Libraries
#include "Arduino.h"
#include "Buzzer.h"
#include "DS18B20.h"
#include "ESP8266.h"
#include "LiquidCrystal.h"
#include "LDR.h"
#include "PIR.h"
#include "Relay.h"


// Pin Definitions
#define BUZZER_PIN_SIG	2
#define DS18B20_PIN_DQ	3
#define WIFI_PIN_TX	11
#define WIFI_PIN_RX	10
#define IRFLAME_5V_PIN_AOUT	A3
#define LCD_PIN_RS	9
#define LCD_PIN_E	8
#define LCD_PIN_DB4	4
#define LCD_PIN_DB5	5
#define LCD_PIN_DB6	6
#define LCD_PIN_DB7	7
#define LDR_PIN_SIG	A1
#define MQ2_5V_PIN_AOUT	A5
#define PIR_PIN_SIG	12
#define RELAYMODULE_PIN_SIGNAL	13



// Global variables and defines
// ====================================================================
// vvvvvvvvvvvvvvvvvvvv ENTER YOUR WI-FI SETTINGS  vvvvvvvvvvvvvvvvvvvv
//
const char *SSID     = "WIFI-SSID"; // Enter your Wi-Fi name 
const char *PASSWORD = "PASSWORD" ; // Enter your Wi-Fi password
//
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// ====================================================================
char* const host = "www.google.com";
int hostPort = 80;
#define THRESHOLD_ldr   100
int ldrAverageLight;
// object initialization
Buzzer buzzer(BUZZER_PIN_SIG);
DS18B20 ds18b20(DS18B20_PIN_DQ);
ESP8266 wifi(WIFI_PIN_RX,WIFI_PIN_TX);
LiquidCrystal lcd(LCD_PIN_RS,LCD_PIN_E,LCD_PIN_DB4,LCD_PIN_DB5,LCD_PIN_DB6,LCD_PIN_DB7);
LDR ldr(LDR_PIN_SIG);
PIR pir(PIR_PIN_SIG);
Relay relayModule(RELAYMODULE_PIN_SIGNAL);


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    wifi.init(SSID, PASSWORD);
    // set up the LCD's number of columns and rows
    lcd.begin(16, 2);
    ldrAverageLight = ldr.readAverage();
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    if(menuOption == '1') {
    // Buzzer - Test Code
    // The buzzer will turn on and off for 500ms (0.5 sec)
    buzzer.on();       // 1. turns on
    delay(500);             // 2. waits 500 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    buzzer.off();      // 3. turns off.
    delay(500);             // 4. waits 500 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    }
    else if(menuOption == '2') {
    // DS18B20 1-Wire Temperature Sensor - Test Code
    // Read DS18B20 temp sensor value in degrees celsius. for degrees fahrenheit use ds18b20.ReadTempF()
    float ds18b20TempC = ds18b20.readTempC();
    Serial.print(F("Temp: ")); Serial.print(ds18b20TempC); Serial.println(F(" [C]"));

    }
    else if(menuOption == '3') {
    // ESP8266-01 - Wifi Module - Test Code
    //Send request for www.google.com at port 80
    wifi.httpGet(host, hostPort);
    // get response buffer. Note that it is set to 250 bytes due to the Arduino low memory
    char* wifiBuf = wifi.getBuffer();
    //Comment out to print the buffer to Serial Monitor
    //for(int i=0; i< MAX_BUFFER_SIZE ; i++)
    //  Serial.print(wifiBuf[i]);
    //search buffer for the date and time and print it to the serial monitor. This is GMT time!
    char *wifiDateIdx = strstr (wifiBuf, "Date");
    for (int i = 0; wifiDateIdx[i] != '\n' ; i++)
    Serial.print(wifiDateIdx[i]);

    }
    else if(menuOption == '4')
    {
    // Disclaimer: The Infrared Flame Detection Sensor is in testing and/or doesn't have code, therefore it may be buggy. Please be kind and report any bugs you may find.
    }
    else if(menuOption == '5') {
    // LCD 16x2 - Test Code
    // Print a message to the LCD.
    lcd.setCursor(0, 0);
    lcd.print("Circuito Rocks !");
    // Turn off the display:
    lcd.noDisplay();
    delay(500);
    // Turn on the display:
    lcd.display();
    delay(500);
    }
    else if(menuOption == '6') {
    // LDR (Mini Photocell) - Test Code
    // Get current light reading, substract the ambient value to detect light changes
    int ldrSample = ldr.read();
    int ldrDiff = abs(ldrAverageLight - ldrSample);
    Serial.print(F("Light Diff: ")); Serial.println(ldrDiff);

    }
    else if(menuOption == '7')
    {
    // Disclaimer: The Methane, Butane, LPG and Smoke Gas Sensor - MQ-2 is in testing and/or doesn't have code, therefore it may be buggy. Please be kind and report any bugs you may find.
    }
    else if(menuOption == '8') {
    // Infrared PIR Motion Sensor Module - Test Code
    bool pirVal = pir.read();
    Serial.print(F("Val: ")); Serial.println(pirVal);

    }
    else if(menuOption == '9') {
    // Relay Module - Test Code
    // The relay will turn on and off for 500ms (0.5 sec)
    relayModule.on();       // 1. turns on
    delay(500);             // 2. waits 500 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    relayModule.off();      // 3. turns off.
    delay(500);             // 4. waits 500 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    }
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) Buzzer"));
    Serial.println(F("(2) DS18B20 1-Wire Temperature Sensor"));
    Serial.println(F("(3) ESP8266-01 - Wifi Module"));
    Serial.println(F("(4) Infrared Flame Detection Sensor"));
    Serial.println(F("(5) LCD 16x2"));
    Serial.println(F("(6) LDR (Mini Photocell)"));
    Serial.println(F("(7) Methane, Butane, LPG and Smoke Gas Sensor - MQ-2"));
    Serial.println(F("(8) Infrared PIR Motion Sensor Module"));
    Serial.println(F("(9) Relay Module"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
    			Serial.println(F("Now Testing Buzzer"));
    		else if(c == '2') 
    			Serial.println(F("Now Testing DS18B20 1-Wire Temperature Sensor"));
    		else if(c == '3') 
    			Serial.println(F("Now Testing ESP8266-01 - Wifi Module"));
    		else if(c == '4') 
    			Serial.println(F("Now Testing Infrared Flame Detection Sensor - note that this component doesn't have a test code"));
    		else if(c == '5') 
    			Serial.println(F("Now Testing LCD 16x2"));
    		else if(c == '6') 
    			Serial.println(F("Now Testing LDR (Mini Photocell)"));
    		else if(c == '7') 
    			Serial.println(F("Now Testing Methane, Butane, LPG and Smoke Gas Sensor - MQ-2 - note that this component doesn't have a test code"));
    		else if(c == '8') 
    			Serial.println(F("Now Testing Infrared PIR Motion Sensor Module"));
    		else if(c == '9') 
    			Serial.println(F("Now Testing Relay Module"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}

/*******************************************************

*    Circuito.io is an automatic generator of schematics and code for off
*    the shelf hardware combinations.

*    Copyright (C) 2016 Roboplan Technologies Ltd.

*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.

*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.

*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*    In addition, and without limitation, to the disclaimers of warranties 
*    stated above and in the GNU General Public License version 3 (or any 
*    later version), Roboplan Technologies Ltd. ("Roboplan") offers this 
*    program subject to the following warranty disclaimers and by using 
*    this program you acknowledge and agree to the following:
*    THIS PROGRAM IS PROVIDED ON AN "AS IS" AND "AS AVAILABLE" BASIS, AND 
*    WITHOUT WARRANTIES OF ANY KIND EITHER EXPRESS OR IMPLIED.  ROBOPLAN 
*    HEREBY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT 
*    NOT LIMITED TO IMPLIED WARRANTIES OF MERCHANTABILITY, TITLE, FITNESS 
*    FOR A PARTICULAR PURPOSE, NON-INFRINGEMENT, AND THOSE ARISING BY 
*    STATUTE OR FROM A COURSE OF DEALING OR USAGE OF TRADE. 
*    YOUR RELIANCE ON, OR USE OF THIS PROGRAM IS AT YOUR SOLE RISK.
*    ROBOPLAN DOES NOT GUARANTEE THAT THE PROGRAM WILL BE FREE OF, OR NOT 
*    SUSCEPTIBLE TO, BUGS, SECURITY BREACHES, OR VIRUSES. ROBOPLAN DOES 
*    NOT WARRANT THAT YOUR USE OF THE PROGRAM, INCLUDING PURSUANT TO 
*    SCHEMATICS, INSTRUCTIONS OR RECOMMENDATIONS OF ROBOPLAN, WILL BE SAFE 
*    FOR PERSONAL USE OR FOR PRODUCTION OR COMMERCIAL USE, WILL NOT 
*    VIOLATE ANY THIRD PARTY RIGHTS, WILL PROVIDE THE INTENDED OR DESIRED
*    RESULTS, OR OPERATE AS YOU INTENDED OR AS MAY BE INDICATED BY ROBOPLAN. 
*    YOU HEREBY WAIVE, AGREE NOT TO ASSERT AGAINST, AND RELEASE ROBOPLAN, 
*    ITS LICENSORS AND AFFILIATES FROM, ANY CLAIMS IN CONNECTION WITH ANY OF 
*    THE ABOVE. 
********************************************************/