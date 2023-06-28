#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>

int main () {
	int file, count, valor;
	if (( file = open ("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY )) <0) {
		perror("Falha ao abrir o arquivo.\n") ;
		return -1;
	}
	struct termios options ;
	tcgetattr(file , &options ) ;
	options.c_cflag = B115200 | CS8 | CREAD | CLOCAL ;
	options.c_iflag = IGNPAR | ICRNL ;
	tcflush(file , TCIFLUSH ) ;
	tcsetattr(file , TCSANOW , &options ) ;

	int pino_PWM = 23; // pwm por software na GPIO23
	int brilho;
	int range = 255; // periodo do PWM = 255 us * range
	wiringPiSetupGpio(); // usar a numeracao GPIO , nao WPi

	pinMode(pino_PWM, OUTPUT); // configura GPIO23 como saida
	softPwmCreate(pino_PWM, 1, range);

	unsigned char receive [100];

	while (1) {
		if (( count = read(file, (void*) receive , 100) ) <0) {
			perror("Falha ao ler da entrada .\n") ;
			delay(100);
			continue;
		}

		if (count != 0){
			receive[count] = 0;
			int n = atoi(receive);
			printf("Foram lidos [%d] caracteres: %d \n", count , n);
			softPwmWrite(pino_PWM, n);
		}

	}
}
