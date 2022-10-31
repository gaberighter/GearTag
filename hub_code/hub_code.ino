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
const uint8_t* address = "00001";

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
	analogWrite(BPIN, 1000);
	delay(1000);
	analogWrite(BPIN, 0);
  delay(1000);
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

	radio.openReadingPipe(0, address);
	radio.startListening();
}

void loop() {
  if(alarming){
    beep();
  }
  logPings();
  checkTimes();
}
