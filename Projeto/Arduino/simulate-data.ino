void setup(){
    // Configura a serial: band rate de 115200
    Serial.begin(115200);
    randomSeed(analogRead(A0));
}

void loop(){
    int emgValue = random(1024);  // Gera um valor aleatório inteiro de 0 a 1023
    float battery = random(1000) / 1000.0;  // Gera um valor ponto flutuante aleatório entre 0.000 e 0.999
    bool handStatus = random(2);  // Gera um valor booleano aleatório (0 ou 1)

    // Cria a string com os valores gerados
    String output = String(battery) + "|" + String(emgValue) + "|" + String(handStatus);

    Serial.println(output);  // Imprime a string no Monitor Serial

    delay(100);  // Aguarda 100 ms
}