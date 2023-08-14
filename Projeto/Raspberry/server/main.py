#!/usr/bin/env python3

import json
import time
import serial
import asyncio
import websockets
import config as cfg

data = {}

async def getSerialData():
    port = cfg.serial["port"]
    baud_rate = cfg.serial["baud_rate"]

    print("Start Serial - Port: {} - Baud Rate: {}".format(port, baud_rate))
    serialPort = serial.Serial(port, baud_rate)
    time.sleep(2)
    while True:
        if serialPort.in_waiting > 0:
            line = serialPort.readline().decode().strip()

            print("Receive: {}".format(line))

            arduino_data = line.split("|")

            if len(arduino_data) < 3:
                continue
                
            data["date"] = time.time()
            data["trigger_status"] = arduino_data[0]
            data["value"] = arduino_data[1]

            hand_status = False
            if arduino_data[2] == "1":
                hand_status = True

            data["status"] = hand_status

            await asyncio.sleep(0)

    serialPort.close()

async def handler(websocket):
    print("Accept connection")
    message = await websocket.recv()
    print("Receive: {}".format(message))
    event = json.loads(message)

    if event["ready"] != True:
        return
    
    while True:
        await websocket.send(json.dumps(data))
        print("Sended: {}".format(data))

        time.sleep(0.1) # Sleep 100 ms
        await asyncio.sleep(0)


async def startWebsocket():
    print("Start Websocket")
    async with websockets.serve(handler, "", cfg.websocket["port"]):
        await asyncio.Future()  # Run forever

async def main():
    websocketServerTask = asyncio.create_task(startWebsocket())
    getSerialDataTask = asyncio.create_task(getSerialData())
    await websocketServerTask
    await getSerialDataTask

if __name__ == "__main__":
    asyncio.run(main())
