/**
 * @license
 * Copyright 2021 Aritro Saha, Tony Lin
 * This code is released under the MIT license.
*/

/* Motors - Written by Aritro Saha & Tony Lin 2021.11.03
   This code is written to do a drive program with multiple functions. */

#include <Arduino.h>

const int MotorPins[] = {5, 10, 6, 11}; // declare constants for motor pins

void move(int millis, const int (&motorValues)[4]) {
  for (int i = 0; i < 4; i++) analogWrite(MotorPins[i], motorValues[i]);
  delay(millis);
}

void setup() {
  for (int i = 0; i < 4; i++) pinMode(MotorPins[i], OUTPUT); // set pins as OUTPUTS
  move(4000, {130, 0,    130,  0});    // Forward
  move(1500, {0,   230,  230,  0});    // Turn Left
  move(3000, {100, 0,    100,  0});    // Forward
  move(1500, {230, 0,    0,    230});  // Turn Right
  move(2000, {100, 0,    100,  0});    // Reverse
  move(0,    {0,   0,    0,    0});    // Stop
}

void loop() { };
