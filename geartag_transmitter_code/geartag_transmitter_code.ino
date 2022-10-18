//code for the tag component of GearTag

//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(9, 8);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";

//text that will make up the ping
const String ping = "here";

void setup() {
  //initialize the radio module
  radio.begin();

  //set the address
  radio.openWritingPipe(address);

  //set the module as transmitter
  radio.stopListening();
}

void loop() {
  //ping the receiver
  radio.write(&text, sizeof(text));

  //delay for 5 seconds
  delay(5000);
}
