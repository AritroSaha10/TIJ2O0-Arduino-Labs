/**
 * @license
 * Copyright 2021 Aritro Saha
 * This code is released under the MIT license.
*/

/**
 * 8 LEDs Challenge - Written by Aritro Saha 2021.10.19
 * This code is written to make 8 LEDs light on and off one
 * after another in a continuous loop using for loops and variables.
 * variables, arrays, for loop. In addition, the delay time will vary 
 * per each time that the loop() function is run, in accordance to 
 * the challenge.
**/

#include <Arduino.h>

int delayTime = 500; // delay time variable, in ms

// boolean to represent whether LEDs should be speeding up or slowing down
// initially set to false since it will be toggled on when the loop() func runs for the first time
bool speedUpTime = false;

// The order of the LED pins that will be turned on / off
int ledPins[] = {1, 5, 2, 6, 3, 7, 4, 8};

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
  for (int i = 0; i <= 7; i++)
  {
    digitalWrite(ledPins[i], HIGH);
    delay(delayTime);
  }

  // turn LEDs off in the reverse sequence
  for (int i = 7; i >= 0; i--)
  {
    digitalWrite(ledPins[i], LOW);
    delay(delayTime); 
  }

  // TODO: Fix code
  // If it has reached the limits of either fastest or slowest,
  // start doing the opposite (faster -> slower, slower -> faster)
  if (delayTime == 500 || delayTime == 100)
  {
    speedUpTime = true;
  }

  if (delayTime == 100) {
    speedUpTime = false;
  }

  // Add to the delay time according to the speedUpTime,
  // if true, it will go faster, otherwise, it will go slower
  if (speedUpTime) {
    delayTime -= 100;
  } else {
    delayTime += 100;
  }
}
