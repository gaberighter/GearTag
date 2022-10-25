/*A class for listing attributes of different
tags that might be connected to the main hub*/

class Transmitter{
  private:
    int id;
  public:
    Transmitter(int id) {
      this->id = id;
    }

    int getId() {
      return id;
    }

    void setId(int newId) {
      id = newId;
    }
};
