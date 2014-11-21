/* Simple Serial ECHO script : Written by ScottC 03/07/2012 */

/* Use a variable called byteRead to temporarily store
   the data coming from the computer */

// include the library code:
#include <SoftwareSerial.h> //this is a must


// RainSensor serial
const int rxpin = 2;                    // pin used to receive from RainSensor
const int txpin = 3;                    // pin used to send to RainSensor
SoftwareSerial serial_rain(rxpin, txpin); // new serial port on pins 2 and 3

//char strValue[18]; // must be big enough to hold all the digits
int ctr;

void setup() {                
  // Turn the Serial Protocol ON
  Serial.begin(9600);
  serial_rain.begin(1200); // initialize the port, Rain 1200 baud 
 }

void loop() {
   /*  check if data has been sent from the computer: */
   if (serial_rain.available()) {
    char byteRead = serial_rain.read();
    if (byteRead == 115 || byteRead =='s')
    {
      ctr = 0;    
    }
    else if ((ctr % 2) == 0)
        {
      // decode the hex value and print out first character in two-byte ascii hex
      switch (ctr)
      {
        case 0: Serial.println();Serial.print("PeakRS = \t\t"); break;
        case 2: Serial.print("SPeakRS = \t\t"); break;
        case 4: Serial.print("RainAD8 = \t\t"); break;
        case 6: Serial.print("LRA = \t\t\t"); break;
        case 8: Serial.print("TransRat = \t\t"); break;
        case 10: Serial.print("AmbLNoise = \t\t"); break;
        case 12: Serial.print("RGBits = \t\t"); break;
        case 14: Serial.print("Slow Reg Index = \t"); break;
        case 16: Serial.print("Slow Reg Value = \t"); break;
        default: break;
      }
      Serial.print(byteRead);    
      ctr++;   
    }
    else
    {
      // print out the 2nd ascii hex byte and then add a newline
      Serial.println(byteRead); 
      ctr++; 
    }
    }
 
}
