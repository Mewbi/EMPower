#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

using namespace std;

//----------------------------------------[ VARS ]
int leds[] = {20, 21, 16};
int num_leds = sizeof(leds) / sizeof(leds[0]);

const string base_path = "/sys/class/gpio/";
//-----------------------------------------------|

//-----------------------------------[ FUNCTIONS ]
void set_led_status(int gpio, int value) {
    cout << "Set GPIO [ " << gpio << " ] value [ " << value << " ]" << endl;

    string path = base_path + "gpio" + to_string(gpio) + "/value";
    fstream fs;
    fs.open(path, fstream::out);
    fs << value;
    fs.close();
}

void setup_led(int gpio, const string& mode) {
    cout << "Enable GPIO [ " << gpio << " ] in mode [ " << mode << " ]" << endl;

    fstream fs;
    fs.open("/sys/class/gpio/export", fstream::out);
    fs << gpio;
    fs.close();

    sleep(3);

    string path = base_path + "gpio" + to_string(gpio) + "/direction";
    fs.open(path, fstream::out);
    fs << mode;
    fs.close();
}

void disable_led(int gpio) {
    cout << "Disable GPIO [ " << gpio << " ]" << endl;

    fstream fs;
    fs.open("/sys/class/gpio/unexport", fstream::out);
    fs << gpio;
    fs.close();

    sleep(3);
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
