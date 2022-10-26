#include "Transmitter.h"

Transmitter::Transmitter(int id){
  this->id = id;
}

int Transmitter::getId(){
  return id;
}

void Transmitter::setId(int newId){
  id = newId;
}
