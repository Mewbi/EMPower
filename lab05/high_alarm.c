#include <stdio.h>
#include <wiringPi.h>

#define pino_PWM0 18

int main() {                            // este programa deve ser rodado com 'sudo'
   int dc, ciclos, ligado, desligado, entre;
   dc = 64;
   wiringPiSetupGpio();                 // usa a numeracao da GPIO
   pinMode(pino_PWM0, PWM_OUTPUT);      // configura a GPIO18 com o PWM por hardware

   ligado = 180000;
   desligado = 180000;
   entre = 130000;
   // Ajustando a frequencia do PWM em 10kHz com 128 passos de duty cycle
   // frequencia PWM = 19,2 MHz / (divisor * range)
   // 10000 = 19200000 / (divisor * 128) => divisor = 15
   pwmSetMode(PWM_MODE_MS);             // usando frequencia fixa
   pwmSetRange(129);                    // passos do duty cycle (max=4096)
   pwmSetClock(569);                     // fornece uma frequencia de 10kHz (max=4096)
   printf("Iniciando...\n");
   for(int j = 0; j < 2; j++){
      for(int i = 0; i < 3; i++){
         pwmWrite(pino_PWM0, dc);
         usleep(ligado);
         pwmWrite(pino_PWM0, 0);
         usleep(desligado);
      }
      usleep(entre);
      for(int i = 0; i < 2; i++){
         pwmWrite(pino_PWM0, dc);
         usleep(ligado);
         pwmWrite(pino_PWM0, 0);
         usleep(desligado);
      }
      usleep((ligado + desligado) * 1 + entre + (ligado + desligado) * 2);
   }
   printf("Fim.\n");
   return 0;                            // a saida PWM permanece ligada apos o termino do programa
}
