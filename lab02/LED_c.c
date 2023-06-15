#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//----------------------------------------[ VARS ]
int leds[] = {20, 21, 16};
int num_leds = sizeof(leds) / sizeof(leds[0]);

const char *base_path = "/sys/class/gpio/";
//-----------------------------------------------|

//-----------------------------------[ FUNCTIONS ]
void set_led_status(int gpio, int value) {
    printf("Set GPIO [ %d ] value [ %d ]\n", gpio, value);

    char path[128];
    snprintf(path, sizeof(path), "%sgpio%d/value", base_path, gpio);
    FILE *f = fopen(path, "w");
    fprintf(f, "%d", value);
    fclose(f);
}

void setup_led(int gpio, const char *mode) {
    printf("Enable GPIO [ %d ] in mode [ %s ]\n", gpio, mode);

    FILE *f = fopen("/sys/class/gpio/export", "w");
    fprintf(f, "%d", gpio);
    fclose(f);

    sleep(3);

    char path[128];
    snprintf(path, sizeof(path), "%sgpio%d/direction", base_path, gpio);
    f = fopen(path, "w");
    fprintf(f, "%s", mode);
    fclose(f);
}

void disable_led(int gpio) {
    printf("Disable GPIO [ %d ]\n", gpio);

    FILE *f = fopen("/sys/class/gpio/unexport", "w");
    fprintf(f, "%d", gpio);
    fclose(f);

    sleep(3);
}

//-----------------------------------------------|

//----------------------------------------[ MAIN ]
int main() {
    for (int i = 0; i < num_leds; i++)
    {
        setup_led(leds[i], "out");
    }


    for (int i = 0; i < 5; i++) {

        // Red LED 2 seconds
        set_led_status(leds[0], 1);
        sleep(2);
        set_led_status(leds[0], 0);

        // Green LED 1 second
        set_led_status(leds[1], 1);
        sleep(1);
        set_led_status(leds[1], 0);

        // Yellow LED 1 second
        set_led_status(leds[2], 1);
        sleep(1);
        set_led_status(leds[2], 0);
    }

    for (int i = 0; i < num_leds; i++)
    {
        disable_led(leds[i]);
    }

    return 0;
}
