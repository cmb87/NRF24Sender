/*
    DIY Arduino based RC Transmitter Project
              == Receiver Code ==
  by Dejan Nedelkovski, www.HowToMechatronics.com
  Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
  https://howtomechatronics.com/projects/diy-arduino-rc-transmitter/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 910);   // nRF24L01 (CE, CSN)

const byte address[6] = "00001";
unsigned long lastReceiveTime = 0;
unsigned long currentTime = 0;
// Max size of this struct is 32 bytes - NRF24L01 buffer limit
struct Data_Package {
    byte j1PotX;
    byte j1PotY;
    byte j1Button;
    byte j2PotX;
    byte j2PotY;
    byte j2Button;
};
Data_Package data; //Create a variable with the above structure
void setup() {
  Serial.begin(115200);
  Serial.print("Setup Receiver");
  radio.begin();
  radio.openReadingPipe(0, address);
  //radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening(); //  Set the module as receiver
  resetData();
}
void loop() {
  // Check whether there is data to be received
  if (radio.available()) {
    radio.read(&data, sizeof(Data_Package)); // Read the whole data and store it into the 'data' structure
    lastReceiveTime = millis(); // At this moment we have received the data
    
    // Print the data in the Serial Monitor
    Serial.print("j1PotX: ");
    Serial.print(data.j1PotX);
    Serial.print("; j1PotY: ");
    Serial.print(data.j1PotY);
    Serial.print("j2PotX: ");
    Serial.print(data.j2PotX);
    Serial.print("; j2PotY: ");
    Serial.print(data.j2PotY);
    Serial.print("\n");
    
  }

  //Serial.print(radio.isChipConnected());
  // Check whether we keep receving data, or we have a connection between the two modules
  currentTime = millis();
  if ( currentTime - lastReceiveTime > 1000 ) { // If current time is more then 1 second since we have recived the last data, that means we have lost connection
    resetData(); // If connection is lost, reset the data. It prevents unwanted behavior, for example if a drone has a throttle up and we lose connection, it can keep flying unless we reset the values
  }
  delay(1);

}
void resetData() {
  // Reset the values when there is no radio connection - Set initial default values
  data.j1PotX = 127;
  data.j1PotY = 127;
  data.j2PotX = 127;
  data.j2PotY = 127;
  data.j1Button = 1;
  data.j2Button = 1;
}
