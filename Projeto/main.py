#!/usr/bin/env python3

import json
import time
import asyncio
import websockets
import random as rd

data = {}

async def generateData():
    print("Start Generate Data")

    controller = 0
    value = 0
    while True:
        if controller < 30:
            value = rd.randrange(5,10) * 10
        else:
            value = rd.random() * 10
        
        controller += 1
        if controller >= 50:
            controller = 0

        dataTimestamp = time.time()
        data["date"] = dataTimestamp
        data["value"] = value
        await asyncio.sleep(0)


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
    async with websockets.serve(handler, "", 8001):
        await asyncio.Future()  # Run forever

async def main():
    websocketServerTask = asyncio.create_task(startWebsocket())
    generateDataTask = asyncio.create_task(generateData())
    await websocketServerTask
    await generateDataTask

if __name__ == "__main__":
    asyncio.run(main())