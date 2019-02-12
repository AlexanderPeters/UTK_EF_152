#include <Servo.h>

//////////////////////////////////////////////////////////////////////////////////////////////////
// Servo lab
Servo servo;
const int potPin = A0; //measure pot position
int pos; //declare variable for servo position
int servoPin = 3; //declare the pin where the servo is connected
int servoDelay = 20; //delay to allow the servo to reach position and settle down
int potRead; //declare variable for the value read from the potentiometer

//////////////////////////////////////////////////////////////////////////////////////////////////
// Lab 5
const int button1Pin = 0;  // pushbutton 1 pin
const int button2Pin = 1;  // pushbutton 2 pin
const int ledPin =  6;    // LED pin
int button1State, button2State;  // variables to hold the pushbutton states

///////////////////////////////////////////////////////////////////////////////////////////////////
// Lab 11
const int buzzerPin = 2;    // connect the buzzer to pin 9
const int songLength = 18;  // sets the number of notes of the song

// Notes is an array of text characters corresponding to the notes
// in your song. A space represents a rest (no tone)

char notes[songLength] = {
  'c', 'd', 'f', 'd', 'a', ' ', 'a', 'g', ' ', 'c', 'd', 'f', 'd', 'g', ' ', 'g', 'f', ' '}; 

// beats[] is an array of values for each note. A "1" represents a quarter-note, 
// "2" a half-note, and "4" a quarter-note.
// Don't forget that the rests (spaces) need a length as well.

int beats[songLength] = {
  1, 1, 1, 1, 1, 1, 4, 4, 2, 1, 1, 1, 1, 1, 1, 4, 4, 2};

int tempo = 113;  // The tempo is how fast to play the song (beats per second).

///////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  // Servo Lab
  Serial.begin(9600); //Set serial baud rate to 9600 bps
  servo.attach(servoPin, 900, 1100); //declare to which pin is the servo connected
  
///////////////////////////////////////////////////////////////////////////////////////////////////
  // Lab 5
  // Set up the pushbutton pins to be an input:
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  
  // Set up the LED pin to be an output:
  pinMode(ledPin, OUTPUT); 
  
///////////////////////////////////////////////////////////////////////////////////////////////////
  // Lab 11
  pinMode(buzzerPin, OUTPUT);  // sets the  buzzer pin as an OUTPUT
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  // Servo Lab
  potRead = analogRead(potPin); //read the potentiometer
  pos = (.5)*potRead+5;  // calcuate the position from the potentiometer reading
  servo.write(pos);  //write the position on the servo
  Serial.print("sensor: ");
  Serial.print(potRead);
  delay(servoDelay);
///////////////////////////////////////////////////////////////////////////////////////////////////
  // Lab 5
  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);

  // if button1 or button 2 are pressed (but not both)
  if (((button1State == LOW) && (button2State == HIGH)) || ((button1State == HIGH) && (button2State == LOW)))
  {
    digitalWrite(ledPin, HIGH);  // turn the LED on
  }
  else
  {
    digitalWrite(ledPin, LOW);  // turn the LED off
  }
///////////////////////////////////////////////////////////////////////////////////////////////////
  // Lab 11
    int i, duration; //

  for (i = 0; i < songLength; i++) // for loop is used to index through the arrays
  {
    duration = beats[i] * tempo;  // length of note/rest in ms

    if (notes[i] == ' ')          // is this a rest? 
      delay(duration);            // then pause for a moment
    else                          // otherwise, play the note
    {
      tone(buzzerPin, frequency(notes[i]), duration);
      delay(duration);            // wait for tone to finish
    }
    delay(tempo/10);              // brief pause between notes
  }

  //while(true){
  // We only want to play the song once, so we pause forever
  //}
  // If you'd like your song to play over and over, remove the while(true)
  // statement above
}

int frequency(char note) 
{
  int i;
  const int numNotes = 8;  // number of notes we're storing
  char names[numNotes] = { 
    'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C'    };
  int frequencies[numNotes] = {
    262, 294, 330, 349, 392, 440, 494, 523    };

  // Now we'll search through the letters in the array, and if
  // we find it, we'll return the frequency for that note.

  for (i = 0; i < numNotes; i++)  // Step through the notes
  {
    if (names[i] == note)         // Is this the one?
    {
      return(frequencies[i]);     // Yes! Return the frequency and exit function.
    }
  }
  return(0);  // We looked through everything and didn't find it,
  // but we still need to return a value, so return 0.
}
