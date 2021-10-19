/**
 * 8 LEDs Challenge - Written by Aritro Saha 2021.10.18
 * This code is written to make 8 LEDs light on and off one
 * after another in a continuous loop using for loops and variables.
 * variables, arrays, for loop. In addition, the delay time will vary 
 * per each time that the loop() function is run, in accordance to 
 * the challenge.
**/

#include <Arduino.h>

int delayTime = 500; // delay time variable, in ms

bool speedUpTime = true; // boolean to represent whether LEDs should be speeding up or slowing down

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

  // If it has reached the limits of either fastest or slowest, start doing the opposite (faster -> slower, slower -> faster)
  if (delayTime == 500 || delayTime == 100) {
    speedUpTime = !speedUpTime;
  }

  // Add to the delay time according to the speedUpTime, if true, it will go faster, otherwise, it will go slower
  delayTime += speedUpTime ? -100 : 100; 
}
