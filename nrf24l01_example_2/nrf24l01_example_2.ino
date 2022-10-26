//include libraries
#include <SPI.h>
#include "RF24.h"

//define the buzzer pin
#define BPIN 6

//define the number of transmitters
#define NUM_TRANSMITTERS 1

//instantiate transceiver objects
transmitter Transmitter(0);

//instantiate transceiver object using pin 9 as CE and 10 as CSN
RF24 radio(9, 10);

//state the address
uint8_t address = "00001"

//create an array to store the separate transmitters' classes
int timestamps[NUM_TRANSMITTERS];

//create a boolean to control whether or not the alarm is sounding
bool alarming = false;

//log the time when the most recent ping for each tag was recieved
int logPings(){
	for(int i = 0; i < NUM_TRANSMITTERS; i++){
		if(radio.available()){
			int time = millis();
			int ping;
			radio.read(&ping, 1);
			if(tag1.getId() == ping){
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
void checkRadio(){
	if(!radio.begin()){
		Serial.print("radio not working");
	}
}
void setup() {
	Serial.begin(96000);

	checkRadio();

	radio.openReadingPipe(0, address);
	radio.startListening();
}

void loop() {
}
