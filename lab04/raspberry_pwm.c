#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>


# include < fcntl .h >
# include < unistd .h >
# include < termios .h > // biblioteca para comunicacao serial

int main(){
	int pino_PWM = 23;                         // pwm por software na GPIO23
	int brilho;
	int range = 255;                           // periodo do PWM = 255us*range
	wiringPiSetupGpio();                       // usar a numeracao GPIO, nao WPi
	pinMode(pino_PWM,OUTPUT);	           // configura GPIO23 como saida
	softPwmCreate(pino_PWM, 1, range);         // inicializa PWM por software
	while (1) {
	
		  softPwmWrite (pino_PWM, brilho); // altera o duty cycle do PWM
		  delay (10) ;                     // aguarda 10ms
	}
}

