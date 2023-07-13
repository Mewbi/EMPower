#include <stdio.h>
#include <wiringPi.h>

#define pino_PWM0 18                    // o PWM sera acionado na GPIO18

int main() {                            // este programa deve ser rodado com 'sudo'
   int dc, ciclos;
   wiringPiSetupGpio();                 // usa a numeracao da GPIO
   pinMode(pino_PWM0, PWM_OUTPUT);      // configura a GPIO18 com o PWM por hardware

   pwmSetMode(PWM_MODE_MS);             // usando frequencia fixa
   pwmSetRange(128);                    // passos do duty cycle (max=4096)
   pwmSetClock(15);                     // fornece uma frequencia de 10kHz (max=4096)
   printf("Iniciando...\n");
   pwmWrite(pino_PWM0, 40);
   usleep(10000000); // Rodando por 10 segundos
   pwmWrite(pino_PWM0, 0);
   printf("Fim.\n");
   return 0;                            // a saida PWM permanece ligada apos o termino do programa
}
