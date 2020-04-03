/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define MAX_MILLIS_TO_WAIT 500  //or whatever
  
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";

// The sizeof this struct should not exceed 32 bytes
// This gives us up to 32 8 bits channals
struct MyData {
  byte throttle;
  byte yaw;
  byte pitch;
  byte roll;
  byte AUX1;
  byte AUX2;
};
MyData data;

int c;
byte RFin_bytes[6] {0};
unsigned long starttime;

void resetData() 
{
  //This are the start values of each channal
  // Throttle is 0 in order to stop the motors
  //127 is the middle value of the 10ADC.
    
  data.throttle = 0;
  data.yaw = 127;
  data.pitch = 127;
  data.roll = 127;
  data.AUX1 = 0;
  data.AUX2 = 0;
}

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  resetData();
  Serial.begin(115200);
}

void loop() {

  radio.write(&data, sizeof(MyData));
  
  
  starttime = millis();
  while ( (Serial.available()<6) && ((millis() - starttime) < MAX_MILLIS_TO_WAIT) )
  {      
       // hang in this loop until we either get 9 bytes of data or 1 second
       // has gone by
  }
  if(Serial.available() < 6)
  {
             // the data didn't come in - handle that problem here
       //Serial.println("ERROR - Didn't get 6 bytes of data!");
 
  }
  else
  {
      // for(int n=0; n<6; n++)
      //    RFin_bytes[n] = Serial.read(); // Then: Get them.

        Serial.readBytes(RFin_bytes, 6);
  }


  data.throttle = RFin_bytes[0];
  data.yaw = RFin_bytes[1];
  data.pitch = RFin_bytes[2];
  data.roll = RFin_bytes[3];
  data.AUX1 = RFin_bytes[4];
  data.AUX2 = RFin_bytes[5];

  Serial.println("");
  Serial.print(data.throttle);
  Serial.print(" ");
  Serial.print(data.yaw);
  Serial.print(" ");
  Serial.print(data.pitch);
  Serial.print(" ");
  Serial.print(data.roll);
  Serial.print(" ");
  Serial.print(data.AUX1);
  Serial.print(" ");
  Serial.print(data.AUX2);
  Serial.println("");
  Serial.flush();
  // ==================================
  // For calibration
  //if (Serial.available() > 0) {
    /* This code will work IF you set the Serial Monitor to "No Line Ending"
      (OSX 10.6.8. IDE Version 1.0.6.2). parseInt() doesn't like the NL + CR chars.
  //  */
  // c = Serial.parseInt();    // Parse an Integer from Serial
  //  data.throttle = c;
  //}

  // ==================================
  delay(50);
}
