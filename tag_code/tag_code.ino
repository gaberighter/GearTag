//include libraries
#include <SPI.h>
#include "RF24.h"

//instantiate transciever object using pin 9 as CE and 10 as CSN
RF24 radio(6, 7);

//define the id for this tag
float id = 0;

//state the address
uint8_t address[][6] = { "hub01", "tag01", "tag02" };

//send a ping
void ping(){
  bool written = radio.write(&id, sizeof(float));
  //Serial.println("pinging");
  if(written){
    //Serial.println("recieved");
  }
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
  
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  
  checkRadio();

  radio.openWritingPipe(address[0]);
  radio.stopListening();
}

void loop() {
  ping();
  checkRadio();
  delay(100);
}
