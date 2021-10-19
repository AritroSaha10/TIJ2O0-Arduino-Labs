/**
 * 8 LEDs - Written by Aritro Saha 2021.10.18
 * This code is written to make 8 LEDs light on and off one
 * after another in a continuous loop using for loops and variables.
 * variables, arrays, for loop
**/

#include <Arduino.h>

int delayTime = 200;                      // delay time variable

void setup()
{
  // set all LED pins as outputs
  for (int i = 1; i <= 8; i++)
  {
    pinMode(i, OUTPUT);
  }
}

void loop()
{
  // --- Original Code ---
  // turn LEDs on then off one at a time with delayTime delay
  for (int i = 1; i <= 8; i++)
  {
    digitalWrite(i, HIGH);
    delay(delayTime);
    digitalWrite(i, LOW);
  }

  // wait for some time before going to the next cycle
  delay(2000);

  // -- Test your Understanding Pt. A ---
  // turn LEDs on until they are all on
  for (int i = 1; i <= 8; i++)
  {
    digitalWrite(i, HIGH);
    delay(delayTime);
  }

  // turn LEDs off one at a time 
  for (int i = 8; i >= 1; i--)
  {
    digitalWrite(i, HIGH);
    delay(delayTime);
  }

  // --- Test your Understanding Pt. B ---
  // turn LEDs on in the sequence of 1, 5, 2, 6, 3, 7, 4, 8
  for (int i = 1; i <= 8; i++)
  {
    // if i is odd, turn on the i th LED, otherwise, turn on the i + 3 LED
    digitalWrite(i % 2 ? i : (i + 3), HIGH);
    delay(500); // 500 ms delay
  }

  // turn LEDs off in the reverse sequence
  for (int i = 8; i >= 1; i--)
  {
    // if i is odd, turn off the i th LED, otherwise, turn off the i + 3 LED
    digitalWrite(i % 2 ? i : (i + 3), LOW);
    delay(500);
  }
}
