#!/bin/bash

#----------------------------------------[ VARS ]
ledRed=20
ledYellow=16
ledGreen=21
#-----------------------------------------------|

#-----------------------------------[ FUNCTIONS ]
function setupLed() {
    led=$1  # GPIO Number
    mode=$2 # Mode: in / out

    echo -en "Enable GPIO [ ${led} ] in mode [ ${mode} ]: "
    echo $led >> "/sys/class/gpio/export"
    sleep 3 # Wait 3 second to ensure export GPIO
    echo $mode >> "/sys/class/gpio/gpio${led}/direction"
    echo "Success"
}

function disableLed() {
    led=$1 # GPIO Number

    echo -en "Disable GPIO [ ${led} ]: "
    echo $led >> "/sys/class/gpio/unexport"
    sleep 3 # Wait 3 second to ensure unexport GPIO
    echo "Success"
}

function setLedStatus() {
    led=$1
    status=$2

    echo -en "Set GPIO [ ${led} ] value [ $status ]: "
    echo $status >> "/sys/class/gpio/gpio${led}/value"
    echo "Success"
}

#-----------------------------------------------|

#----------------------------------------[ MAIN ]
# Setup env
setupLed ${ledRed} "out"
setupLed ${ledYellow} "out"
setupLed ${ledGreen} "out"

for _ in $(seq 5); do

    # Red LED 2 second
    setLedStatus ${ledRed} 1
    sleep 2
    setLedStatus ${ledRed} 0

    # Green LED 1 second
    setLedStatus ${ledGreen} 1
    sleep 1
    setLedStatus ${ledGreen} 0

    # Yellow LED 1 second
    setLedStatus ${ledYellow} 1
    sleep 1
    setLedStatus ${ledYellow} 0

done

# Disable GPIO
disableLed ${ledRed}
disableLed ${ledYellow}
disableLed ${ledGreen}
#-----------------------------------------------|
