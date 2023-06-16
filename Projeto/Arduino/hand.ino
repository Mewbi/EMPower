#include <Servo.h>

int led = 13; // declara led na porta 13
// Variables will change:
int Counter = 0;   // counter for the number of button presses
int State = 0;         // current state of the button
int lastState = 0;     // previous state of the button
bool estadomio = 0;
bool Statehand = 0;


Servo myservo1;  // create servo object to control a servo
Servo myservo2;  // create servo object to control a servo
Servo myservo3;  // create servo object to control a servo
Servo myservo4;  // create servo object to control a servo
Servo myservo5;  // create servo object to control a servo

int potpin = 0;  // analog pin used to connect the potentiometer
int batpin = 1;  // analog pin used to connect the battery
int val;    // variable to read the value from the analog pin
int bat;
float volt;

void setup() {
  myservo1.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(10);  // attaches the servo on pin 10 to the servo object
  myservo3.attach(11);  // attaches the servo on pin 11 to the servo object
  myservo4.attach(6);  // attaches the servo on pin 6 to the servo object
  myservo5.attach(5);  // attaches the servo on pin 5 to the servo object
      // initialize serial communication:
  Serial.begin(9600);
}

void loop() {
  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  bat = analogRead(batpin);
  volt = bat * 5.0 / 1023.0;

  Serial.print(val);
  Serial.print(",");
  Serial.print(Statehand);
  Serial.print(",");
  Serial.println(volt);
  if (val > 500)
  {
    estadomio = 0;
  }
  else
  {
    estadomio = 1;
  }
  // read the pushbutton input pin:
  State = estadomio;

  // compare the buttonState to its previous state
  if (State != lastState) {
    // if the state has changed, increment the counter
    if (State == HIGH) {
      // if the current state is HIGH then the button
      // wend from off to on:
      Counter++;
    // Delay a little bit to avoid bouncing
    delay(50);
    }
  }
  // save the current state as the last state,
  //for next time through the loop
  lastState = State;

  // turns on the LED every four button pushes by
  // checking the modulo of the button push counter.
  // the modulo function gives you the remainder of
  // the division of two numbers:
  if ((Counter % 3 == 0)) 
  {
    digitalWrite(led, LOW);
    myservo1.write(0);                  // sets the servo position
    delay(200);
    myservo2.write(0);                  // sets the servo position
    delay(200);
    myservo3.write(0);                  // sets the servo position
    delay(200);
    myservo4.write(0);                  // sets the servo position
    delay(200);
    myservo5.write(0);                  // sets the servo position
    Statehand = 0;
    delay(15);
  } 
  else if ((Counter % 3 != 0) )
  {
    digitalWrite(led, HIGH);
    myservo1.write(180);                  // sets the servo position
    delay(200);
    myservo2.write(180);                  // sets the servo position
    delay(200);
    myservo3.write(180);                  // sets the servo position
    delay(200);
    myservo4.write(180);                  // sets the servo position
    delay(200);
    myservo5.write(180);                  // sets the servo position
    Statehand = 1;
    delay(15);
  }

}
