/*A class for listing attributes of different
tags that might be connected to the main hub*/

#include <Arduino.h>

class Transmitter{
  private:
    int id;
  public:
    Transmitter(int id);
    
    int getId();
    void setId(int newId);
};
