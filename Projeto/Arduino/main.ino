int EMGPin = A0;
int EMGVal = 0;
int activeHand = 0;
int EMGTrigger = 350;
long int delayTrigger = 1000; // 1000 ms delay
long int lastReadTime = 0;

void setup() {
  Serial.begin(115200);
  lastReadTime = millis();
}

void loop() {
  
  EMGVal = analogRead(EMGPin);
  EMGVal = 400;
  float battery = random(1000) / 1000.0;  // Gera um valor ponto flutuante aleatório entre 0.000 e 0.999
  bool handStatus = random(2);  // Gera um valor booleano aleatório (0 ou 1)

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
    // Mudar status da mão
      
  }
  // Cria a string com os valores gerados
  String output = String(battery) + "|" + String(EMGVal) + "|" + String(handStatus) + "|" + String(activeHand);

  Serial.println(output);  // Imprime a string no Monitor Serial
  delay(100);
}
