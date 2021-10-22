/* 
 * US Sensor - Written by Aritro Saha & Tony Lin 2021.10.22
 * This code is written to sense distance and sound a buzzer using
 * "tone" commands. It also plays Hot Cross Buns when an object is <50cm away
 * from the ultrasonic (US) sensor. 
*/

// declare variables for pins
int GREEN_LED_PIN = 4;
int RED_LED_PIN = 5;
int BUZZER_PIN = 6;
int TRIGGER_PIN = 3;
int ECHO_PIN = 2;

// declare variables for measuring distance using us sensor
float duration;
float distance;

void setup()
{
  // set pins 3 to 6 outputs
  for (int i = 3; i <= 6; i++)
  {
    pinMode(i, OUTPUT);
  }

  pinMode(2, INPUT); // set pin 2 as input
}

void loop()
{
  /************ Start US Measurement Section ***********/
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;
  /************** End US Measurement Section ***********/
  
  // Toggle LED + Play recognizable tone
  if (distance <= 50)
  {
    // Toggle red LED
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW);

    /************ Play Hot Cross Buns using the buzzer ************/
    // First 3 notes
    for (int i = 0; i < 2; i++)
    {
      // each delay is 250ms so it matches 4/4 time
      tone(BUZZER_PIN, 123.47);
      delay(250);
      tone(BUZZER_PIN, 110.00);
      delay(250);
      tone(BUZZER_PIN, 98.00);
      delay(500); 
    }

    // Middle section
    // G repeats 4 times
    for (int i = 0; i <= 4; i++)
    {
      // G on the piano
      tone(BUZZER_PIN, 98.00);
      // Delay is 100ms to recreate the effect of stopping for a second to breath
      delay(100);
      
      // Turn it off to recreate the effect of stop playing
      noTone(BUZZER_PIN);
      delay(25);
    }

    // A repeats 4 times
    for (int i = 0; i <= 4; i++)
    {
      // A on the piano
      tone(BUZZER_PIN, 110.00);
      delay(100);

      noTone(BUZZER_PIN);
      delay(25);
    }

    // Last 3 notes
    tone(BUZZER_PIN, 123.47);
    delay(250);
    tone(BUZZER_PIN, 110.00);
    delay(250);
    tone(BUZZER_PIN, 98.00);
    delay(500);
    /************ End playing of Hot Cross Buns using the buzzer ************/
  }

  // Play a higher frequency on the buzzer as the distance lowers 
  else if (distance < 60)
  {
    tone(BUZZER_PIN, 130.81);
  }
  else if (distance < 70)
  {
    tone(BUZZER_PIN, 123.47);
  }
  else if (distance < 80)
  {
    tone(BUZZER_PIN, 110.00);
  }
  else if (distance < 90)
  {
    tone(BUZZER_PIN, 98.00); 
  }

  // Distance is further than 90cm
  else 
  {
    noTone(BUZZER_PIN);
  }

  // Make sure the green pin is on if the distance is larger than 50cm
  if (distance > 50)
  {
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, LOW);
  }
  
  delay(10); // small delay to save system resources
}
