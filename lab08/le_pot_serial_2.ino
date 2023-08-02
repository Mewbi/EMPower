const int analogInPin = A0;            // o potenciômetro esta ligado ao pino A0
int iniciaColeta = 0;
char charRecebido;                     // cria uma variavel para armazenar o caractere recebido
int intervalo = 100;

void setup(){
   // Configura a serial: baud rate de 115200, 8-bit, sem paridade, 1 stop bit
   Serial.begin(115200, SERIAL_8N1);
}

void loop(){
    String output;
    if (Serial.available()){            // verifica se recebeu algum comando
      charRecebido = Serial.read();    // le o caractere recebido
      switch ( charRecebido ){
          case 'i':                    // inicia coleta
            iniciaColeta = 1;
            break;
             
          case 'p':                    // para a coleta
            iniciaColeta = 0;
            break;

          case 't':                    // Envia intervalo
            output = "i|" + String(intervalo);
            Serial.println(output);
            break;

          case 'a':                    // Aumenta intervalo
            intervalo = intervalo + 10;
            output = "i|" + String(intervalo);
            Serial.println(output);
            break;

          case 'd':                    // Diminui intervalo
            intervalo = intervalo - 10;
            output = "i|" + String(intervalo);
            Serial.println(output);
            break;

          default:                     // outro comando, ignora...
             break;
      }
   }
   if ( iniciaColeta == 1 ){
      int valor = analogRead(analogInPin); // le valor no pino A0 usando conversor ADC de 10-bit
      output = "v|" + String(valor);
      Serial.println(output);           
   }
   delay(intervalo);                          
}

