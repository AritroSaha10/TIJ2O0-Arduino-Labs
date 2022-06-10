#include <Arduino.h>

// DiscoBot program - Written by Aritro Saha 2021.11.15
// Plays Crab Rave by Noisestorm while powering both the motors and LEDs all simultaneously

// Pin numbers
int ledPins[] = {13, 12, 11, 8, 7, 4, 2, 1};
int speaker_PIN = 5;

// Motor pins
int LMotor_pin1 = 3;
int LMotor_pin2 = 6;
int RMotor_pin1 = 9;
int RMotor_pin2 = 10;

// The time at which the program starts
// Used to make sure the program only runs for 60 seconds
// long instead of int since the time can reach >32K, the maximum for an int
long startingTime = 0;

// The data structure for a Note
typedef struct
{
   int noteTone;      // The tone / frequency of the note
   double beatLength; // The length of the beat
} Note;

// Length of each beat in milliseconds
// Assumes that song will be played at 125 BPM
int beatLength = 480; // In ms, https://toolstud.io/music/bpm.php?bpm=125&bpm_unit=4%2F4

// Length of note relative to 1 beat
double QUARTER_NOTE = 1;
double EIGHTH_NOTE = 0.5;
double SIXTEENTH_NOTE = 0.25;

// All possible motor commands
enum MOTOR_COMMAND
{
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT,
  STOP
};

// List containing all the motor commands to run
MOTOR_COMMAND motorCommands[] = {
    // Measure 1
    FORWARD,
    BACKWARD,
    BACKWARD,
    STOP,
    LEFT,
    RIGHT,
    STOP,

    // Measure 2
    LEFT,
    LEFT,
    RIGHT,
    RIGHT,

    // Measure 3
    FORWARD,
    BACKWARD,
    FORWARD,
    BACKWARD,
};

// All the notes for Crab Rave by Noisestorm
// Unfortunately, we can't just play an MP3 without an SD card reader and using both PWM pins (which are needed for speed control of the actual motors)
// so I had to resort to this method. I tried to format it in a way so that it mostly makes sense to anyone else reading it. In addition, given
// the mapping of frequency pitches to keyboard notes, you could likely recreate the piece of music that this uses.
Note crabraveNotes[] = {
    // Measure 1
    {349, QUARTER_NOTE},
    {349, EIGHTH_NOTE + SIXTEENTH_NOTE},
    {329, SIXTEENTH_NOTE},
    {0,   SIXTEENTH_NOTE},
    {329, EIGHTH_NOTE},
    {329, QUARTER_NOTE},
    {0,   SIXTEENTH_NOTE},

    // Measure 2
    {329, QUARTER_NOTE},
    {329, EIGHTH_NOTE + SIXTEENTH_NOTE},
    {349, SIXTEENTH_NOTE + SIXTEENTH_NOTE},
    {0,   SIXTEENTH_NOTE},
    {349, EIGHTH_NOTE},
    {349, EIGHTH_NOTE},
    {329, EIGHTH_NOTE},

    // Measure 3
    {349, QUARTER_NOTE},
    {349, EIGHTH_NOTE + SIXTEENTH_NOTE},
    {329, SIXTEENTH_NOTE},
    {0,   SIXTEENTH_NOTE},
    {329, EIGHTH_NOTE + SIXTEENTH_NOTE},
    {329, QUARTER_NOTE},

    // Measure 4
    {329, QUARTER_NOTE},
    {329, EIGHTH_NOTE + SIXTEENTH_NOTE},
    {349, SIXTEENTH_NOTE + SIXTEENTH_NOTE},
    {0,   SIXTEENTH_NOTE},
    {349, EIGHTH_NOTE},
    {349, EIGHTH_NOTE},
    {329, EIGHTH_NOTE},

    // Measure 5
    {349, QUARTER_NOTE},
    {349, EIGHTH_NOTE + SIXTEENTH_NOTE},
    {329, SIXTEENTH_NOTE},
    {0,   SIXTEENTH_NOTE},
    {329, EIGHTH_NOTE},
    {329, QUARTER_NOTE},
    {0,   SIXTEENTH_NOTE},

    // Measure 6
    {329, QUARTER_NOTE},
    {329, EIGHTH_NOTE + SIXTEENTH_NOTE},
    {349, SIXTEENTH_NOTE + SIXTEENTH_NOTE},
    {0,   SIXTEENTH_NOTE},
    {349, EIGHTH_NOTE},
    {349, EIGHTH_NOTE},
    {329, EIGHTH_NOTE},

    // Measure 7
    {349, QUARTER_NOTE},
    {349, QUARTER_NOTE},
    {349, QUARTER_NOTE},
    {349, QUARTER_NOTE},

    // Measure 8
    {220, QUARTER_NOTE},
    {220, QUARTER_NOTE},
    {220, QUARTER_NOTE},
    {220, QUARTER_NOTE},

    // Measure 9
    {220, EIGHTH_NOTE},
    {349, EIGHTH_NOTE},
    {293, EIGHTH_NOTE},
    {293, EIGHTH_NOTE},
    {220, SIXTEENTH_NOTE},
    {0,   SIXTEENTH_NOTE},
    {220, SIXTEENTH_NOTE},
    {329, EIGHTH_NOTE},
    {261, EIGHTH_NOTE},
    {261, SIXTEENTH_NOTE},

    // Measure 10
    {220, SIXTEENTH_NOTE},
    {0,   SIXTEENTH_NOTE},
    {220, SIXTEENTH_NOTE},
    {329, EIGHTH_NOTE},
    {261, EIGHTH_NOTE},
    {261, EIGHTH_NOTE},
    {196, SIXTEENTH_NOTE},
    {0,   EIGHTH_NOTE},
    {196, SIXTEENTH_NOTE},
    {246, SIXTEENTH_NOTE},
    {246, SIXTEENTH_NOTE},

    // Measure 11, 2nd repeat
    {220, EIGHTH_NOTE},
    {349, EIGHTH_NOTE},
    {293, EIGHTH_NOTE},
    {293, EIGHTH_NOTE},
    {220, SIXTEENTH_NOTE},
    {0,   SIXTEENTH_NOTE},
    {220, SIXTEENTH_NOTE},
    {329, EIGHTH_NOTE},
    {261, EIGHTH_NOTE},
    {261, SIXTEENTH_NOTE},

    // Measure 12
    {220, SIXTEENTH_NOTE},
    {0,   SIXTEENTH_NOTE},
    {220, SIXTEENTH_NOTE},
    {329, EIGHTH_NOTE},
    {261, EIGHTH_NOTE},
    {261, EIGHTH_NOTE},
    {196, SIXTEENTH_NOTE},
    {0,   EIGHTH_NOTE},
    {196, SIXTEENTH_NOTE},
    {246, SIXTEENTH_NOTE},
    {246, SIXTEENTH_NOTE},

    // Measure 13, 3rd repeat
    {220, EIGHTH_NOTE},
    {349, EIGHTH_NOTE},
    {293, EIGHTH_NOTE},
    {293, EIGHTH_NOTE},
    {220, SIXTEENTH_NOTE},
    {0,   SIXTEENTH_NOTE},
    {220, SIXTEENTH_NOTE},
    {329, EIGHTH_NOTE},
    {261, EIGHTH_NOTE},
    {261, SIXTEENTH_NOTE},

    // Measure 14
    {220, SIXTEENTH_NOTE},
    {0,   SIXTEENTH_NOTE},
    {220, SIXTEENTH_NOTE},
    {329, EIGHTH_NOTE},
    {261, EIGHTH_NOTE},
    {261, EIGHTH_NOTE},
    {196, SIXTEENTH_NOTE},
    {0,   EIGHTH_NOTE},
    {196, SIXTEENTH_NOTE},
    {246, SIXTEENTH_NOTE},
    {246, SIXTEENTH_NOTE},

    // Measure 15, 4th repeat
    {220, EIGHTH_NOTE},
    {349, EIGHTH_NOTE},
    {293, EIGHTH_NOTE},
    {293, EIGHTH_NOTE},
    {220, SIXTEENTH_NOTE},
    {0,   SIXTEENTH_NOTE},
    {220, SIXTEENTH_NOTE},
    {329, EIGHTH_NOTE},
    {261, EIGHTH_NOTE},
    {261, SIXTEENTH_NOTE},

    // Measure 16
    {220, SIXTEENTH_NOTE},
    {0,   SIXTEENTH_NOTE},
    {220, SIXTEENTH_NOTE},
    {329, EIGHTH_NOTE},
    {261, EIGHTH_NOTE},
    {261, EIGHTH_NOTE},
    {196, SIXTEENTH_NOTE},
    {0,   EIGHTH_NOTE},
    {196, SIXTEENTH_NOTE},
    {246, SIXTEENTH_NOTE},
    {246, SIXTEENTH_NOTE},

    // Measure 17, 5th repeat
    {220, EIGHTH_NOTE},
    {349, EIGHTH_NOTE},
    {293, EIGHTH_NOTE},
    {293, EIGHTH_NOTE},
    {220, SIXTEENTH_NOTE},
    {0,   SIXTEENTH_NOTE},
    {220, SIXTEENTH_NOTE},
    {329, EIGHTH_NOTE},
    {261, EIGHTH_NOTE},
    {261, SIXTEENTH_NOTE},

    // Measure 18
    {220, SIXTEENTH_NOTE},
    {0,   SIXTEENTH_NOTE},
    {220, SIXTEENTH_NOTE},
    {329, EIGHTH_NOTE},
    {261, EIGHTH_NOTE},
    {261, EIGHTH_NOTE},
    {196, SIXTEENTH_NOTE},
    {0,   EIGHTH_NOTE},
    {196, SIXTEENTH_NOTE},
    {246, SIXTEENTH_NOTE},
    {246, SIXTEENTH_NOTE},

    // Measure 19, 6th repeat
    {220, EIGHTH_NOTE},
    {349, EIGHTH_NOTE},
    {293, EIGHTH_NOTE},
    {293, EIGHTH_NOTE},
    {220, SIXTEENTH_NOTE},
    {0,   SIXTEENTH_NOTE},
    {220, SIXTEENTH_NOTE},
    {329, EIGHTH_NOTE},
    {261, EIGHTH_NOTE},
    {261, SIXTEENTH_NOTE},

    // Measure 20
    {220, SIXTEENTH_NOTE},
    {0,   SIXTEENTH_NOTE},
    {220, SIXTEENTH_NOTE},
    {329, EIGHTH_NOTE},
    {261, EIGHTH_NOTE},
    {261, EIGHTH_NOTE},
    {196, SIXTEENTH_NOTE},
    {0,   EIGHTH_NOTE},
    {196, SIXTEENTH_NOTE},
    {246, SIXTEENTH_NOTE},
    {246, SIXTEENTH_NOTE},

    // Measure 21, 7th repeat
    {220, EIGHTH_NOTE},
    {349, EIGHTH_NOTE},
    {293, EIGHTH_NOTE},
    {293, EIGHTH_NOTE},
    {220, SIXTEENTH_NOTE},
    {0,   SIXTEENTH_NOTE},
    {220, SIXTEENTH_NOTE},
    {329, EIGHTH_NOTE},
    {261, EIGHTH_NOTE},
    {261, SIXTEENTH_NOTE},

    // Measure 22
    {220, SIXTEENTH_NOTE},
    {0,   SIXTEENTH_NOTE},
    {220, SIXTEENTH_NOTE},
    {329, EIGHTH_NOTE},
    {261, EIGHTH_NOTE},
    {261, EIGHTH_NOTE},
    {196, SIXTEENTH_NOTE},
    {0,   EIGHTH_NOTE},
    {196, SIXTEENTH_NOTE},
    {246, SIXTEENTH_NOTE},
    {246, SIXTEENTH_NOTE},

    // Measure 23, 8th repeat
    {220, EIGHTH_NOTE},
    {349, EIGHTH_NOTE},
    {293, EIGHTH_NOTE},
    {293, EIGHTH_NOTE},
    {220, SIXTEENTH_NOTE},
    {0,   SIXTEENTH_NOTE},
    {220, SIXTEENTH_NOTE},
    {329, EIGHTH_NOTE},
    {261, EIGHTH_NOTE},
    {261, SIXTEENTH_NOTE},

    // Measure 24
    {220, SIXTEENTH_NOTE},
    {0,   SIXTEENTH_NOTE},
    {220, SIXTEENTH_NOTE},
    {329, EIGHTH_NOTE},
    {261, EIGHTH_NOTE},
    {261, EIGHTH_NOTE},
    {196, SIXTEENTH_NOTE},
    {0,   EIGHTH_NOTE},
    {196, SIXTEENTH_NOTE},
    {246, SIXTEENTH_NOTE},
    {246, SIXTEENTH_NOTE},
};

// The length of crabraveNotes, aka how many notes there are
int amountOfNotes = 217;

// Go forward
void forward()
{
   analogWrite(LMotor_pin1, 255);
   digitalWrite(LMotor_pin2, LOW);
   analogWrite(RMotor_pin1, 255);
   digitalWrite(RMotor_pin2, LOW);
}

// Go backward
void backward()
{
   digitalWrite(LMotor_pin1, LOW);
   analogWrite(LMotor_pin2, 255);
   digitalWrite(RMotor_pin1, LOW);
   analogWrite(RMotor_pin2, 255);
}

// Turn left
void left()
{
   analogWrite(LMotor_pin1, 255);
   digitalWrite(LMotor_pin2, LOW);
   digitalWrite(RMotor_pin1, LOW);
   analogWrite(RMotor_pin2, 255);
}

// Turn right
void right()
{
   digitalWrite(LMotor_pin1, LOW);
   analogWrite(LMotor_pin2, 255);
   analogWrite(RMotor_pin1, 255);
   digitalWrite(RMotor_pin2, LOW);
}

// Stop
void stop()
{
   digitalWrite(LMotor_pin1, LOW);
   digitalWrite(LMotor_pin2, LOW);
   digitalWrite(RMotor_pin1, LOW);
   digitalWrite(RMotor_pin2, LOW);
}

void setup()
{
   // Initialize LED pins
   for (int i = 0; i <= 7; i++)
   {
      pinMode(ledPins[i], OUTPUT);
   }

   // Initialize the speaker pin
   pinMode(speaker_PIN, OUTPUT);

   // Initialize the motor pins
   pinMode(LMotor_pin1, OUTPUT);
   pinMode(LMotor_pin2, OUTPUT);
   pinMode(RMotor_pin1, OUTPUT);
   pinMode(RMotor_pin2, OUTPUT);

   // Record the starting time
   startingTime = millis();
}

void loop()
{
   // Used for counting every iteration of the loop
   int i = 0;

   // Stop after 60s / 1m. Unfortunately, the maximum value for an integer
   // is ~32K, which will not suffice for our needs. Therefore, we must suffix
   // the number with L, which means long. A long allows for values under (2^31)-1,
   // which is more than enough for our needs.
   while (millis() - startingTime <= 60L * 1000L)
   {
      // Turn on 2 LEDs
      int randLed = rand() % 8;
      int randLed2 = (rand() + millis()) % 8;

      digitalWrite(ledPins[randLed], HIGH);
      digitalWrite(ledPins[randLed2], HIGH);

      // Get the motor command from the list
      MOTOR_COMMAND myMtrCmd = motorCommands[i % 15];

      // Match the command with the function
      if (myMtrCmd == FORWARD)
      {
         forward();
      }
      else if (myMtrCmd == BACKWARD)
      {
         backward();
      }
      else if (myMtrCmd == LEFT)
      {
         left();
      }
      else if (myMtrCmd == RIGHT)
      {
         right();
      }
      else if (myMtrCmd == STOP)
      {
         stop();
      }

      // Play the note needed
      // Make sure that it doesn't try to access an impossible note index
      int noteIdx = i % amountOfNotes;

      // Only play if frequency is real, stay silent if 0
      if (crabraveNotes[noteIdx].noteTone != 0)
      {
         tone(speaker_PIN, crabraveNotes[noteIdx].noteTone);
      }

      // Play for beat amount * how long each beat should be, divided by 2
      delay(crabraveNotes[noteIdx].beatLength * beatLength / 4 * 3);

      // Stop the motors
      stop();

      // Wait again so it completes the note completely
      delay(crabraveNotes[noteIdx].beatLength * beatLength / 4);

      // Stop playing the note
      noTone(speaker_PIN);

      // Turn off both LEDs
      digitalWrite(ledPins[randLed], LOW);
      digitalWrite(ledPins[randLed2], LOW);

      // Tiny delay to give illusion of taking finger off key
      delay(25);

      // Go to next i
      i++;
   }

   // Stop all motors
   stop();

   // Hold, don't proceed any further
   while (true)
   {
   }
}
