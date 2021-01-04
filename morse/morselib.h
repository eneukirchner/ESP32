#ifndef MORSELIB_H
#define MORSELIB_H

const int TDOT = 300; // ms time 
const int TDASH = 3 * TDOT;

const char *mcode[] = {
    "-----", ".----", "..---", "...--", "....-", ".....",
    "-....", "--...", "---..", "----."
};

class Morse {
  public:
    Morse(int pin);
    void send(String message);
  private:
    int m_pin; 
};

#endif
