#include "Transmitter.h"

Transmitter::Transmitter(uint8_t id){
  this->id = id;
}

uint8_t Transmitter::getId(){
  return id;
}

void Transmitter::setId(uint8_t newId){
  id = newId;
}
