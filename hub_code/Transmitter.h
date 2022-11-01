/*A class for listing attributes of different
tags that might be connected to the main hub*/

#include <Arduino.h>

class Transmitter{
  private:
    uint8_t id;
  public:
    Transmitter(uint8_t id);
    
    uint8_t getId();
    void setId(uint8_t newId);
};
