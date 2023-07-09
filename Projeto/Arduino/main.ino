#include <Servo.h>

// Sensor vars
int EMGPin = A0;
int EMGVal = 0;
int EMGTrigger = 350;

// Hand vars
int activeHand = 0;
bool handStatus = false;

Servo servo1;  // Finger 1
Servo servo2;  // Finger 2
Servo servo3;  // Finger 3
Servo servo4;  // Finger 4
Servo servo5;  // Finger 5

int openValues[] = {0, 0, 0, 0, 0};
int closeValues[] = {180, 180, 180, 180, 180};

// Control vars
long int delayTrigger = 1000; // 1000 ms delay
long int lastReadTime = 0;

void setup() {
  Serial.begin(115200);
  lastReadTime = millis();
  servo1.attach(9);
  servo2.attach(10);
  servo3.attach(11);
  servo4.attach(6);
  servo5.attach(5);
}

void loop() {
  
  EMGVal = analogRead(EMGPin);

  // TODO: Get battery level
  float battery = random(1000) / 1000.0;  // Gera um valor ponto flutuante aleatório entre 0.000 e 0.999

  //Serial.println(millis());
  if (EMGVal >= EMGTrigger) {
    long int actualReadTime = millis();
    if (actualReadTime - lastReadTime >= delayTrigger) {
      activeHand += 1;
      lastReadTime = actualReadTime;
    }
  }

  if (activeHand >= 2) {
    activeHand = 0;
    handStatus = changeHandStatus(handStatus);
  }

  // Format string
  String output = String(battery) + "|" + String(EMGVal) + "|" + String(handStatus) + "|" + String(activeHand);

  Serial.println(output);  // Send to Serial
  delay(100);
}

bool changeHandStatus(bool actualStatus) {
    
    if (actualStatus) {
        // Closing hand
        servo1.write(closeValues[0]);
        delay(100);
        servo2.write(closeValues[1]);
        delay(100);
        servo3.write(closeValues[2]);
        delay(100);
        servo4.write(closeValues[3]);
        delay(100);
        servo5.write(closeValues[4]);

        actualStatus = false;

    } else {
        // Opening hand
        servo1.write(openValues[0]);
        delay(100);
        servo2.write(openValues[1]);
        delay(100);
        servo3.write(openValues[2]);
        delay(100);
        servo4.write(openValues[3]);
        delay(100);
        servo5.write(openValues[4]);
        
        actualStatus = true;
    }

    return actualStatus;
}
