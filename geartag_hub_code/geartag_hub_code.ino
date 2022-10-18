//code for the main hub of geartag

//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(9, 8);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";

void setup() {
  //open the serial channel for debugging purposes
  Serial.begin(9600);

  //initialize the transceiver
  radio.begin();

  //set the address
  radio.openReadingPipe(0, address);

  //set the module as a reciever
  radio.startListening();

  //initialize the alarm pins
  
}

void loop() {
  //read data if available in buffer
  if(radio.available()){
      //empty variable for the 
      char ping[4] = {0};
      radio.read(&ping, sizeof(text));
      Serial.println(ping);
      if(strcmp(ping, "here") == 0){
	  //start the alarm
      }
    }
  }
}
