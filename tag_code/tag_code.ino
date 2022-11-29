//include libraries
#include <SPI.h>
#include "RF24.h"

//instantiate transciever object using pin 9 as CE and 10 as CSN
RF24 radio(6, 7);

//define the id for this tag
float id = 0;

//define button pin
int button = 4;

//define the stop/start command and the state (0 = off 1 = on)
float stopStart = 90;
int state = 1;

//state the address
uint8_t address[][6] = { "hub01", "tag01", "tag02" };

//send a ping
void ping(){
  Serial.println("  pinging...");
  bool written = radio.write(&id, sizeof(float));
  //Serial.println("    pinging");
  if(written){
    //Serial.println("    recieved");
  }
}
//check the button
void checkButton(){
  if(digitalRead(button) == HIGH){
    changeState();
    if(state == 1){
      state = 0;
    }else if(state == 0){
      state = 1;
    }
  }
}

//send the stop/start command
void changeState(){
  Serial.print("  changing state from ");
  if(state == 1){
    Serial.println("on to off...");
  }else if(state == 0){
    Serial.println("off to on...");
  }
  bool written = radio.write(&stopStart, sizeof(float));
  Serial.println("    pinging");
  if(written){
    Serial.println("    recieved");
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

void printStatus(){
  Serial.print("currently ");
  if(state == 1){
    Serial.println("on");
  }else if(state == 0){
    Serial.println("off");
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(button, INPUT);
  
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  
  checkRadio();

  radio.openWritingPipe(address[0]);
  radio.stopListening();
}

void loop() {
  printStatus();
  checkButton();
  digitalWrite(3, HIGH);
  if(state == 1){
    ping();
    checkRadio();
  }
}
