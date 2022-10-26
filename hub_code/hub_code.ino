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
RF24 hub(9, 10);

//state the address
const uint8_t address = "00001";

//create an array to store the separate transmitters' classes
int timestamps[NUM_TRANSMITTERS];

//create a boolean to control whether or not the alarm is sounding
bool alarming = false;

//log the time when the most recent ping for each tag was recieved
int logPings(){
	for(int i = 0; i < NUM_TRANSMITTERS; i++){
		if(hub.available()){
			int time = millis();
			int ping;
			hub.read(&ping, 1);
			if(tag0.getId() == ping){
				timestamps[i] = time;
			}
		}
	}
}

//check to see if a tag has not responded in a while
void checkTimes(){
	for(int i = 0; i < NUM_TRANSMITTERS; i++){
		if(timestamps[i] < (millis() - 1000)){
			alarming = true;
		}
	}
}

//beep the buzzer once
void beep(){
	digitalWrite(BPIN, 180);
	delay(100);
	digitalWrite(BPIN, 0);
}

//debugging funcitons
void checkhub(){
	if(!hub.begin()){
		Serial.print("hub not working");
	}
}
void setup() {
	Serial.begin(96000);

	checkhub();

	hub.openReadingPipe(0, address);
	hub.startListening();
}

void loop() {
  if(alarming){
    beep();
  }
  logPings();
  checkTimes();
}
