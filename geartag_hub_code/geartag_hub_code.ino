//code for the main hub of geartag

//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(9, 8);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";

//pin which connects the arduino to the buzzer
const int buzzerPin = 6;

//the number of times the alarm will beep if the tag is not found
const int beeps = 2;

void setup() {
  //open the serial channel for debugging purposes
  Serial.begin(9600);

  //initialize the transceiver
  radio.begin();

  //set the address
  radio.openReadingPipe(0, address);

  //set the module as a reciever
  radio.startListening();

  //initialize the alarm pin
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  //read data if available in buffer
  if(!radio.available()){
  //the buzzer goes off beeps number of times
    for(int i = 0; i < beeps; i++){
      tone(buzzerPin, 1000);
      delay(500);
      noTone(buzzerPin);
    }
  }
  delay(1000);
}
