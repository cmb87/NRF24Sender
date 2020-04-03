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
//RF24 radio(9, 10); // CE, CSN - TEST
RF24 radio(10, 9); // CE, CSN - PAD
const byte address[6] = "00001";
void setup() {
  Serial.println("Setup");
  Serial.begin(115200);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}
void loop() {
  Serial.println("Sent");
  const char text[] = "Hello World";
  radio.write(&text, sizeof(text));
  delay(100);
}
