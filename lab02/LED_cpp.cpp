#include <iostream>
#include <fstream>
#include <unistd.h>

//----------------------------------------[ VARS ]
int leds[] = {16, 20, 21};
int num_leds = sizeof(leds) / sizeof(leds[0]);

const std::string base_path = "/sys/class/gpio/";
//-----------------------------------------------|

//-----------------------------------[ FUNCTIONS ]
void set_led_status(int gpio, int value) {
    std::cout << "Set GPIO [ " << gpio << " ] value [ " << value << " ]" << std::endl;

    std::string path = base_path + "gpio" + std::to_string(gpio) + "/value";
    std::ofstream file(path);
    file << value;
}

void setup_led(int gpio, const std::string& mode) {
    std::cout << "Enable GPIO [ " << gpio << " ] in mode [ " << mode << " ]" << std::endl;

    std::ofstream file("/sys/class/gpio/export");
    file << gpio;

    usleep(1000000);

    std::string path = base_path + "gpio" + std::to_string(gpio) + "/direction";
    std::ofstream direction(path);
    direction << mode;
}

void disable_led(int gpio) {
    std::cout << "Disable GPIO [ " << gpio << " ]" << std::endl;

    std::ofstream file("/sys/class/gpio/unexport");
    file << gpio;

    usleep(1000000);
}

//-----------------------------------------------|

//----------------------------------------[ MAIN ]
int main() {
    for (int i = 0; i < num_leds; i++) {
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

    for (int i = 0; i < num_leds; i++) {
        disable_led(leds[i]);
    }

    return 0;
}
