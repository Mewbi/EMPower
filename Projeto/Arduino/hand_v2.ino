#include <Servo.h>

Servo myservo1;  // create servo object to control a servo
Servo myservo2;  // create servo object to control a servo
Servo myservo3;  // create servo object to control a servo
Servo myservo4;  // create servo object to control a servo
Servo myservo5;  // create servo object to control a servo

void setup() {
  myservo1.attach(11);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(10);  // attaches the servo on pin 10 to the servo object
  myservo3.attach(9);  // attaches the servo on pin 11 to the servo object
  myservo4.attach(6);  // attaches the servo on pin 6 to the servo object
  myservo5.attach(5);  // attaches the servo on pin 5 to the servo object
      // initialize serial communication:
  Serial.begin(9600);
}

void loop() {

    myservo1.write(180);                  // sets the servo position
    delay(800);
    myservo2.write(10);                  // sets the servo position
    delay(800);
    myservo3.write(0);                  // sets the servo position
    delay(800);
    myservo4.write(180);                  // sets the servo position
    delay(800);
    myservo5.write(60);                  // sets the servo position
    delay(1000);

    myservo5.write(180);                  // sets the servo position
    delay(800);
    myservo4.write(0);                  // sets the servo position
    delay(800);
    myservo3.write(180);                  // sets the servo position
    delay(800);
    myservo2.write(180);                  // sets the servo position
    delay(800);
    myservo1.write(0);                  // sets the servo position
    delay(1000);

}
