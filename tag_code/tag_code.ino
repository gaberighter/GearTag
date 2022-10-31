//include libraries
#include <SPI.h>
#include "RF24.h"

//instantiate transciever object using pin 9 as CE and 10 as CSN
RF24 radio(7, 8);

//define the id for this tag
byte id = 0;

//state the address
const uint8_t* address = "00001";

//send a ping
void ping(){
  radio.write(id, 8);
}

//debugging funcitons
void checkRadio(){
  if(!radio.begin()){
    Serial.print("radio not working\n");
  }else if(radio.begin()){
    Serial.print("radio working\n");
  }
}

void setup() {
  Serial.begin(9600);

  checkRadio();

  radio.openWritingPipe(address);
  radio.stopListening();
}

void loop() {
  ping();
}
