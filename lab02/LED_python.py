#!/usr/bin/python3

from time import sleep


#----------------------------------------[ VARS ]
leds = {
    "red": 20,
    "yellow": 16,
    "green": 21
}

base_path = "/sys/class/gpio/"
#-----------------------------------------------|

#-----------------------------------[ FUNCTIONS ]

def set_led_status(gpio, value):
    print("Set GPIO [ {} ] value [ {} ]".format(gpio, value))

    path = base_path + "gpio" + str(gpio) + "/value"
    f = open(path, "w")
    f.write(str(value))
    f.close

    return

def setup_led(gpio, mode):
    print("Enable GPIO [ {} ] in mode [ {} ]".format(gpio, mode))

    path = base_path + "export"
    f = open(path, "w")
    f.write(str(gpio))
    f.close

    sleep(3)

    path = base_path + "gpio" + str(gpio) + "/direction"
    f = open(path, "w")
    f.write(mode)
    f.close

    return

def disable_led(gpio):
    print("Disable GPIO [ {} ]".format(gpio))

    path = base_path + "unexport"
    f = open(path, "w")
    f.write(str(gpio))
    f.close

    sleep(1)

    return


#-----------------------------------------------|

#----------------------------------------[ MAIN ]
setup_led(leds["red"], "out")
setup_led(leds["green"], "out")
setup_led(leds["yellow"], "out")

for _ in range(5):

    # Red LED 2 seconds
    set_led_status(leds["red"], 1)
    sleep(2)
    set_led_status(leds["red"], 0)

    # Green LED 1 second
    set_led_status(leds["green"], 1)
    sleep(1)
    set_led_status(leds["green"], 0)

    # Yellow LED 1 second
    set_led_status(leds["yellow"], 1)
    sleep(1)
    set_led_status(leds["yellow"], 0)


disable_led(leds["red"])
disable_led(leds["green"])
disable_led(leds["yellow"])
#-----------------------------------------------|
