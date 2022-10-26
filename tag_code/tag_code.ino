//include libraries
#include <SPI.h>
#include "RF24.h"

//instantiate transciever object using pin 9 as CE and 10 as CSN
RF24 radio(9, 10);

//state the address
const uint8_t address = "00001";

//send a ping
void ping(){
}

//debugging funcitons
void checkRadio(){
  if(!radio.begin()){
    Serial.print("radio not working");
  }
}

void setup() {
  Serial.begin(96000);

  checkRadio();

  radio.openWritingPipe(address);
  radio.stopListening();
}

void loop() {
  ping();
}
