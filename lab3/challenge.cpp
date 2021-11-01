/* Pushbuttons - Written by Aritro Saha & Tony Lin 2021.11.01
   This code is written to display the state of a pushbutton
   digitalRead */

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(0, 1, 2, 3, 4, 5); // initialize the LCD with pin numbers

int button1Pin = 12;                  //set pin where button 1 is wired
int button2Pin = 13;                  //set pin where button 2 is wired

int button1State; //create variable for the state of button 1
int button2State; //create var for state of button 2

void setup()
{
  lcd.begin(16, 2); // set up the LCD's number of columns and rows
}

void loop()
{
  button1State = digitalRead(button1Pin); //read state of pushbutton 1
  button2State = digitalRead(button2Pin); //read state of pushbutton 2

  if (button1State == LOW && button2State == LOW)
  {
    // both pressed
    lcd.clear();
    lcd.print("BOTH PRESSED!   ");
  } 
  else 
  {
    if (button1State == LOW) //button is pressed
    {
      lcd.setCursor(0, 0);
      lcd.print("PB1 pressed    ");
    }
    else //button is not pressed
    {
      lcd.setCursor(0, 0);
      lcd.print("PB1 not pressed");
    }

    if (button2State == LOW) //button is pressed
    {
      lcd.setCursor(0, 1);
      lcd.print("PB2 pressed    ");
    }
    else //button is not pressed
    {
      lcd.setCursor(0, 1);
      lcd.print("PB2 not pressed");
    }
  }

  delay(100); //delay to allow screen to update
}
