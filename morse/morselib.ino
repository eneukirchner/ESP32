#include "morselib.h"



Morse::Morse(int pin)
{
  m_pin = pin;
  pinMode(m_pin, OUTPUT);
}

void Morse::send(String message)
{
  int character;
  char symbol;

  int n = 0;
  while ((character = message[n++])) {
    if ((character < '0') || (character > '9'))
      break;
    int i = 0;
    while ((symbol = mcode[character - '0'][i++])) {
      digitalWrite(m_pin, HIGH);
      if (symbol == '.')
        delay(TDOT); // dot length
      else
        delay(TDOT * 3); // dash length
      digitalWrite(m_pin, LOW);
      delay(TDOT); // pause after dot / dash
    }
    delay(TDOT * 2); //  pause between characters
  }
}
