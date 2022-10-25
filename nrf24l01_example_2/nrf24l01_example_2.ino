//include libraries
#include <SPI.h>
#include "printf.h"
#include "RF24.h"

//define the buzzer pin
#define BPIN 6

//define the number of transmitters
#define NUM_TRANSMITTERS 1

//instantiate transceiver object using pin 9 as CE and 10 as CSN
RF24 radio(9, 10);

//create an array to store the separate transmitters' classes
int transmitters[NUM_TRANSMITTERS];

//create an array to store all the recieved pings
int array pings[NUM_TRANSMITTERS];

int receivePing(){
}

bool checkIds(){
}

void setup() {
}

void loop() {
}
