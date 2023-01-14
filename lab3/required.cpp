/**
 * @license
 * Copyright 2021 Aritro Saha, Tony Lin
 * This code is released under the MIT license.
*/

/**
 * LCD - Written by Aritro Saha & Tony Lin 2021.11.01
 * This code is written to display values to an LCD display
 * using the LiquidCrystal library.
*/

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // initialize the LCD with pin numbers

const char *messages[] = {"Age: 15", "Tony F.F: rice", "Aritro F.F: rice"};

void setup()
{
  lcd.begin(16, 2); // set up the LCD's number of columns and rows
}

void loop()
{
  /* print a message to the LCD starting at column 0, line 0
  and wait 1 second */
  lcd.setCursor(0, 0);
  lcd.print("Info of AS & TL:");
  delay(1000);

  /* print numbers 5, 4, 3, 2, 1 every second
  starting at column 0 line 1*/
  for (int n = 0; n < 3; n++)
  {
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print(messages[n]);
    delay(1000);
  }
}
