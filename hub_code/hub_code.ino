//include libraries
#include <SPI.h>
#include "RF24.h"
#include "Transmitter.h"

//define the buzzer pin
#define BPIN 6

//define the number of transmitters
#define NUM_TRANSMITTERS 1

//instantiate transceiver objects
Transmitter tag0(0);

//instantiate transceiver object using pin 9 as CE and 10 as CSN
RF24 radio(7, 8);

//state the address
uint8_t address[][6] = { "hub01", "tag01", "tag02" };

//create an array to store the separate transmitters' classes
int timestamps[NUM_TRANSMITTERS];

//create a boolean to control whether or not the alarm is sounding
bool alarming = false;

//log the time when the most recent ping for each tag was recieved
int logPings(){
  uint8_t pipe;
	for(int i = 0; i < NUM_TRANSMITTERS; i++){
		if(radio.available(&pipe)){
      int t = millis();
      Serial.print("time is: ");
      Serial.println(t);
			float payload = 99.0;
      uint8_t bytes = radio.getPayloadSize();
      radio.read(&payload, bytes);

      int castedPayload = payload;
            
      Serial.print(F("Received "));
      Serial.print(bytes);  // print the size of the payload
      Serial.print(F(" bytes on pipe "));
      Serial.print(pipe);  // print the pipe number
      Serial.print(F(": "));
      Serial.println(payload);  // print the payload's value
      Serial.print("casted to: ");
      Serial.println(castedPayload);
      Serial.print("comparing to: ");
      Serial.println(tag0.getId());
			if(tag0.getId() == castedPayload){
				timestamps[tag0.getId()] = millis();
        Serial.println("set tag0 most recent time to: ");
        Serial.println(timestamps[tag0.getId()]);
			}
		}
	}
}

//check to see if a tag has not responded in a while
void checkTimes(){
  alarming = false;
	for(int i = 0; i < NUM_TRANSMITTERS; i++){
    if(millis() > 1500){
		  if(timestamps[i] < (millis() - 1500)){
			  alarming = 1;
		  }else{
        alarming = 0;
		  }
    }
	}
}

//beep the buzzer once
void beep(){
	analogWrite(BPIN, 1000);
	delay(1000);
	analogWrite(BPIN, 0);
  delay(1000);
}

//debugging funcitons
void checkRadio(){
	if(!radio.begin()){
		Serial.print("radio not working\n");
    while(true){
    }
	}else if(radio.begin()){
    Serial.print("radio working\n");
	}
}

void setup() {
	Serial.begin(9600);

	checkRadio();

	radio.openReadingPipe(0, address[0]);
	radio.startListening();
}

void loop() {
  Serial.println(alarming);
  if(alarming == 1){
    analogWrite(BPIN, 1000);
  }else if(alarming == 0){
    analogWrite(BPIN, 0);
  }
  logPings();
  checkTimes();
  delay(1000);
}
